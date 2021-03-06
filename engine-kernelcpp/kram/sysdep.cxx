// $Id: sysdep.cxx 13964 2010-08-18 11:12:52Z jz $

#include "precomp.h"

#include "../kram/sosstrng.h"
#include "../kram/sysdep.h"

#if defined SYSTEM_WIN
#   include <direct.h>     // getcwd
#   include <windows.h>
#   include <tlhelp32.h>
#else
#   include <limits.h>
#   include <unistd.h>
#   include <sys/times.h>
#endif


#include "../kram/sosstrng.h"
#include "../kram/sos.h"
#include "../kram/sosalloc.h"
#include "../kram/sosdate.h"
#include "../kram/sosprof.h"

#if defined SYSTEM_WIN
#   include <io.h>                  // open(), read() etc.
#   include <share.h>
#   include <direct.h>              // mkdir
#   include <windows.h>
#else
#   include <unistd.h>              // read(), write(), close()

#   include <dlfcn.h>               // dladdr()
#endif

#include <sys/stat.h>               // S_IREAD, stat()
#include <fcntl.h>                  // O_RDONLY
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "../zschimmer/zschimmer.h"
#include "../zschimmer/file.h"

using namespace std;
namespace sos {

#ifdef SYSTEM_WIN
    string filename_of_hinstance( HINSTANCE hinstance );
#endif

//--------------------------------------------------------------------delayed_loading_dll_notify
#if defined SYSTEM_MICROSOFT

#include <Delayimp.h>

ostream& operator << ( ostream& s, const DelayLoadInfo dli )
{
    s << dli.szDll;                                          // name of dll
    s << ", ";
    if( dli.dlp.fImportByName )  s << dli.dlp.szProcName;    // name of procedure
                           else  s << dli.dlp.dwOrdinal;     // ordinal of procedure
    s << ", ";
    if( dli.hmodCur )  s << (void*)dli.hmodCur << ' ' << dli.hmodCur << "  " << file_version_info( filename_of_hinstance( dli.hmodCur ) );  // the hInstance of the library we have loaded
                 else  s << "NULL";
    return s;
}


extern "C"
FARPROC WINAPI delayed_loading_dll_notify( uint dliNotify, DelayLoadInfo* pdli )
{
    const char* notify = "?";

    switch( dliNotify ) 
    {
        case dliStartProcessing:		// used to bypass or note helper only
          //notify = "Start Processing";
          //break;
            return NULL;

        case dliNotePreLoadLibrary:     // called just before LoadLibrary, can override w/ new HMODULE return val
            notify = "LoadLibrary     ";
            break;

        case dliNotePreGetProcAddress:  // called just before GetProcAddress, can override w/ new FARPROC return value
            notify = "GetProcAddress  ";
            break;

        case dliFailLoadLib:            // failed to load library, fix it by returning a valid HMODULE
            throw_mswin_error( pdli->dwLastError, "LoadLibrary (delayed loading)", pdli->szDll );
            break;

        case dliFailGetProc:            // failed to get proc address, fix it by returning a valid FARPROC
        {
            Sos_string name;
            if( pdli->dlp.fImportByName )  name = pdli->dlp.szProcName;
                                     else  name = as_string( pdli->dlp.dwOrdinal );

            throw_mswin_error( pdli->dwLastError, "GetProcAddress (delayed loading)", c_str(name) );
        }
        break;

        case dliNoteEndProcessing:      // called after all processing is done, no
          //notify = "End Processing  ";
          //break;
            return NULL;

        default: ;
    }

    //if( sos_static_ptr() && sos_static_ptr()->_valid )    // Wenn nach Programmende eine DLL geladen wird, knallt's in iostream (Microsoft) jz 21.5.03
    {
        LOG( "delayed_loading_dll_notify " << notify << ", " << *pdli << '\n' );
    }

    return NULL;
}

extern "C" PfnDliHook __pfnDliFailureHook = delayed_loading_dll_notify;
extern "C" PfnDliHook __pfnDliNotifyHook  = delayed_loading_dll_notify;

#endif
//-----------------------------------------------------------------------------version_info
#ifdef SYSTEM_WIN

    string version_info_detail( void* info, const char* field, bool with_field_name )
    {
        struct Lang_and_codepage 
        {
             WORD wLanguage;
             WORD wCodePage;
        }* trans;

        uint  len;
        BOOL  ok;
        char  buffer [100];
        char* p;

        ok = VerQueryValue( info, "\\VarFileInfo\\Translation", (void**)&trans, &len );
        if( !ok )  return "";

        sprintf( buffer, "\\StringFileInfo\\%04x%04x\\", trans->wLanguage, trans->wCodePage );
        string name = buffer;
        name += field;

        ok = VerQueryValue( info, (char*)name.c_str(), (void**)&p, &len ); 
        if( !ok )  return "";

        if( len > 0  &&  p[len-1] == 0 )  len--;

        string value ( p, len / sizeof *p );

        return with_field_name? string(field) + "=" + value
                              : value;
    }
#endif

//--------------------------------------------------------------------------file_version_info

string file_version_info( const string& filename )
{
#   ifdef SYSTEM_WIN

        BOOL ok;
        DWORD w = 0;
        int size = GetFileVersionInfoSize( (char*)filename.c_str(), &w );
        if( size > 0 )
        {
            void* info = malloc( size );

            ok = GetFileVersionInfo( (char*)filename.c_str(), NULL, size, info );
            if( !ok )  return "";

            string result = version_info_detail( info, "ProductName", true ) + " " +
                            version_info_detail( info, "ProductVersion", true ) + " " + 
                            version_info_detail( info, "OriginalFilename", true );

            free(info);

            return result;
        }
            
#   endif

    return "";
}

//------------------------------------------------------------------------filename_of_hinstance
#ifdef SYSTEM_WIN

string filename_of_hinstance( HINSTANCE hinstance )
{
    char path[ MAXPATH+1 ];

    int len = GetModuleFileName( hinstance, (LPSTR)path, sizeof path );
    if( !len )  throw_mswin_error( "GetModuleFileName" );

    return path;
}

#endif
//-----------------------------------------------------------------------------program_filename

Sos_string program_filename()
{
#   if defined SYSTEM_WIN
        return filename_of_hinstance( (HINSTANCE)0 );
#   elif 1
        return "";
#   else
        extern char** _argv;
        return _argv && _argv[0]? _argv[ 0 ] : "";
#   endif
}

//------------------------------------------------------------------------------module_filename

Sos_string module_filename()
{
#   if defined SYSTEM_WIN

        extern HINSTANCE _hinstance;
        return filename_of_hinstance( _hinstance );

#   else
#       if defined SYSTEM_HPUX || defined Z_AIX

            return "";

#        else

            Dl_info info;
            memset( &info, 0, sizeof info );

            int err = dladdr( (void*)&module_filename, &info );

            return !err && info.dli_fname? string(info.dli_fname) 
                                         : program_filename();

#       endif
#   endif
}

//----------------------------------------------------------------------------print_all_modules

void print_all_modules( ostream* s )
{
#   ifdef SYSTEM_WIN

        OSVERSIONINFO v;  memset( &v, 0, sizeof v ); v.dwOSVersionInfoSize = sizeof v;
        GetVersionEx( &v );
        if( v.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS  ||  v.dwMajorVersion >= 5 )     // Windows >= 95  oder Windows >= 2000? (Nicht NT bis 4.0)
        {
            try
            {
                HINSTANCE lib = LoadLibrary( "kernel32.dll" );
                if( lib )
                {
                    typedef HANDLE (WINAPI *Proc1)(DWORD,DWORD); 
                    typedef BOOL   (WINAPI *Proc )(HANDLE,LPMODULEENTRY32);

                    Proc1 createsnapshot = (Proc1)GetProcAddress( lib, "CreateToolhelp32Snapshot" );
                    Proc  module32first  = (Proc) GetProcAddress( lib, "Module32First" );
                    Proc  module32next   = (Proc) GetProcAddress( lib, "Module32Next" );

                    if( createsnapshot && module32first && module32next )
                    {
                        HANDLE        snapshot = createsnapshot( TH32CS_SNAPMODULE, 0 );
                        MODULEENTRY32 e;
                        char          buffer [ 2 * MAX_MODULE_NAME32 + 50 ];
                        memset( &e, 0, sizeof e );
                        e.dwSize = sizeof e;

                        BOOL ok = module32first( snapshot, &e );

                        while(1) {
                            e.szModule[ sizeof e.szModule - 1 ] = '\0';
                            sprintf( buffer, "%-12s HMODULE=%8X ", e.szModule, e.hModule );
                            *s << buffer << setw(40) << left << e.szExePath << setw(0) << "  " << file_version_info( e.szExePath ) << '\n';
                            ok = module32next( snapshot, &e );
                            if( !ok )  break;
                        }

                        CloseHandle( snapshot );
                    }

                    FreeLibrary( lib );
                }
            }
            catch( const Xc& x ) { *s << "print_all_modules: " << x << '\n'; }
        }
    
#   endif
}

//----------------------------------------------------------------------------directory_of_path
// Liefert alles außer dem Datennamen und Schrägstrich

Sos_string directory_of_path( const Sos_string& path )
{
    const char* p0 = c_str( path );
    const char* p  = p0 + length( path );

    if( p > p0 )
    {
#       if defined SYSTEM_WIN
            if( length(path) >= 2  &&  p0[1] == ':' )  p0 += 2;
            while( p > p0  &&  p[-1] != '/'  &&  p[-1] != '\\'  &&  p[-1] != ':' )  p--;
            if( p > p0+1  &&  ( p[-1] == '/' || p[-1] == '\\' ) )  p--;
#        else
            while( p > p0  &&  p[-1] != '/' )  p--;
            if( p > p0+1  &&  p[-1] == '/' )  p--;
#       endif
    }

    return path.substr( 0, p - c_str(path) );
}

//-----------------------------------------------------------------------------filename_of_path
// Liefert den Dateinamen von "pfad/dateiname"

string filename_of_path( const string& path )
{
    const char* p0 = path.c_str();
    const char* p  = p0 + path.length();

#   if defined SYSTEM_WIN
        while( p > p0  &&  p[-1] != ':'  &&  p[-1] != '/'  &&  p[-1] != '\\' )  p--;
#    else
        while( p > p0  &&  p[-1] != '/' )  p--;
#   endif

    return p;
}

//-----------------------------------------------------------------------------basename_of_path
// Liefert den Basisnamen  "pfad/basisname.ext"

Sos_string basename_of_path( const Sos_string& path )
{
    const char* p0 = c_str( path );
    const char* p2 = p0 + length( path );
    const char* p1;

#   if defined SYSTEM_WIN
        while( p2 > p0  &&  p2[-1] != '.'  &&  p2[-1] != '/'  &&  p2[-1] != '\\' )  p2--;
        while( p2 > p0  &&  p2[-1] == '.' )  p2--;
        p1 = p2;
        while( p1 > p0  &&  p1[-1] != '/'  &&  p1[-1] != '\\' )  p1--;
#   else
        while( p2 > p0  &&  p2[-1] != '.'  &&  p2[-1] != '/' )  p2--;
        while( p2 > p0  &&  p2[-1] == '.' )  p2--;
        p1 = p2;
        while( p1 > p0  &&  p1[-1] != '/' )  p1--;
#   endif

    return as_string( p1, p2 - p1 );
}

//----------------------------------------------------------------------------extension_of_path
// Liefert die Extension "pfad/basisname.ext"

Sos_string extension_of_path( const Sos_string& path )
{
    const char* p0 = c_str( path );
    const char* p2 = p0 + length( path );

    while( p2 > p0  &&  p2[-1] == ' '  )  p2--;
    const char* p1 = p2;

#   if defined SYSTEM_WIN
        while( p1 > p0  &&  p1[-1] != '.'  &&  p1[-1] != '/'  &&  p1[-1] != '\\' )  p1--;
#    else
        while( p1 > p0  &&  p1[-1] != '.'  &&  p1[-1] != '/' )  p1--;
#   endif

    if( p1[-1] != '.' )  p1 = p2;
    return as_string( p1, p2 - p1 );
}

//----------------------------------------------------------------------make_absolute_filename

string make_absolute_filename( const string& dir, const string& filename )
{
    if( is_absolute_filename( filename )  ||  dir.empty()  ||  filename.empty() )  return filename;

    string fn = dir;
    if( fn == "." )
    {
        char* working_dir = getcwd(NULL,0);
        fn = working_dir? working_dir : "";
        free( working_dir );
        if( fn.empty() )  return filename;
    }
    
    char last = fn[ fn.length() - 1 ];
    
    if( last != '/'  &&  last != '\\' ) 
    {
        if( strchr( fn.c_str(), '\\' ) )  fn += '\\';
                                    else  fn += '/';
    }

    return fn + filename;
}

//----------------------------------------------------------------------------------sos_mkstemp

int sos_mkstemp( const string& name )
{
    int file;

#   ifdef SYSTEM_WIN

        char tmp_filename [1024+1];

        string path = zschimmer::file::get_temp_path();
        int ret = GetTempFileName( path.c_str(), name.c_str(), 0, tmp_filename );
        if( ret == 0 )
        {
            string p = path + "\\" + name + "????.tmp";
            throw_mswin_error( "GetTempFileName", p.c_str() );
        }

        LOG( "sos_mkstemp create " << tmp_filename << '\n' );

        int oflag = O_TEMPORARY | _O_SHORT_LIVED | O_SEQUENTIAL;
        int pmode = S_IREAD | S_IWRITE;

        file = ::sopen( tmp_filename, oflag | O_CREAT | O_RDWR | O_APPEND | O_BINARY, _SH_DENYRW, pmode );
        if( file == -1 )  throw_errno( errno, "open" );

#    else

        string filename;

        if( strchr( name.c_str(), '/' ) )  filename = name;
                                     else  filename = zschimmer::file::get_temp_path() + "/" + name;

        filename += ".XXXXXX";

        file = mkstemp( (char*)filename.c_str() );        // <D6>ffnet die Datei, aber ohne O_APPEND
        LOG( "sos_mkstemp create " << filename << '\n' );

        int ret = unlink( filename.c_str() );                    // Namen sofort wieder l<F6>schen
        if( ret == -1 )  throw_errno( errno, "unlink", filename.c_str() );

#   endif

    return file;
}

//------------------------------------------------------------------------------call_for_linker
// Damit *o eingebunden wird

void call_for_linker( const void* )
{
}

//-------------------------------------------------------------------------------_check_pointer

void _check_pointer( const void* ptr, uint length, const char* info )
{
    if( ptr == NULL )  return;
    if( length == 0 )  return;

#   if defined SYSTEM_WIN32
#       define CODE_OK
        if( IsBadWritePtr( (void*)ptr, length ) )  goto FEHLER;
#   endif

    return;


#   ifdef CODE_OK
      FEHLER:
        throw_xc( "SOS-INVALID-POINTER" );
#   endif
}

//-------------------------------------------------------------------------------------sos_time

time_t sos_time( time_t *timer )
{
    time_t          tim          = time( timer );
    if( timer )  *timer = tim;
    return tim;
}

//-----------------------------------------------------------------------------operator << int64
#if defined SYSTEM_INT64

ostream& operator << ( ostream& s, const int64& i )
{
    char buffer [ 50 ];
    sprintf( buffer, "%" PRINTF_LONG_LONG "d", i );
    s << buffer;
    return s;
}

ostream& operator << ( ostream& s, const uint64& i )
{
    char buffer [ 50 ];
    sprintf( buffer, "%" PRINTF_LONG_LONG "u", i );
    s << buffer;
    return s;
}

#endif

}
