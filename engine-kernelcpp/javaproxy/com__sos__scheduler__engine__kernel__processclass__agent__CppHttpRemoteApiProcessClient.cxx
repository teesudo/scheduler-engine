// *** Generated by com.sos.scheduler.engine.cplusplus.generator ***

#include "_precompiled.h"

#include "com__sos__scheduler__engine__kernel__processclass__agent__CppHttpRemoteApiProcessClient.h"
#include "java__lang__Object.h"
#include "java__lang__String.h"

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace processclass { namespace agent { 

struct CppHttpRemoteApiProcessClient__class : ::zschimmer::javabridge::Class
{
    CppHttpRemoteApiProcessClient__class(const string& class_name);
   ~CppHttpRemoteApiProcessClient__class();

    ::zschimmer::javabridge::Method const _closeRemoteTask__Z__method;
    ::zschimmer::javabridge::Method const _killRemoteTask__I__method;
    ::zschimmer::javabridge::Method const _toString____method;

    static const ::zschimmer::javabridge::class_factory< CppHttpRemoteApiProcessClient__class > class_factory;
};

const ::zschimmer::javabridge::class_factory< CppHttpRemoteApiProcessClient__class > CppHttpRemoteApiProcessClient__class::class_factory ("com.sos.scheduler.engine.kernel.processclass.agent.CppHttpRemoteApiProcessClient");

CppHttpRemoteApiProcessClient__class::CppHttpRemoteApiProcessClient__class(const string& class_name) :
    ::zschimmer::javabridge::Class(class_name)
    ,_closeRemoteTask__Z__method(this, "closeRemoteTask", "(Z)V")
    ,_killRemoteTask__I__method(this, "killRemoteTask", "(I)Z")
    ,_toString____method(this, "toString", "()Ljava/lang/String;"){}

CppHttpRemoteApiProcessClient__class::~CppHttpRemoteApiProcessClient__class() {}




CppHttpRemoteApiProcessClient::CppHttpRemoteApiProcessClient(jobject jo) { if (jo) assign_(jo); }

CppHttpRemoteApiProcessClient::CppHttpRemoteApiProcessClient(const CppHttpRemoteApiProcessClient& o) { assign_(o.get_jobject()); }

#ifdef Z_HAS_MOVE_CONSTRUCTOR
    CppHttpRemoteApiProcessClient::CppHttpRemoteApiProcessClient(CppHttpRemoteApiProcessClient&& o) { set_jobject(o.get_jobject());  o.set_jobject(NULL); }
#endif

CppHttpRemoteApiProcessClient::~CppHttpRemoteApiProcessClient() { assign_(NULL); }




void CppHttpRemoteApiProcessClient::closeRemoteTask(jboolean p0) const {
    ::zschimmer::javabridge::raw_parameter_list<1> parameter_list;
    parameter_list._jvalues[0].z = p0;
    CppHttpRemoteApiProcessClient__class* cls = _class.get();
    cls->_closeRemoteTask__Z__method.call(get_jobject(), parameter_list);
}

bool CppHttpRemoteApiProcessClient::killRemoteTask(jint p0) const {
    ::zschimmer::javabridge::raw_parameter_list<1> parameter_list;
    parameter_list._jvalues[0].i = p0;
    CppHttpRemoteApiProcessClient__class* cls = _class.get();
    return 0 != cls->_killRemoteTask__I__method.bool_call(get_jobject(), parameter_list);
}

::javaproxy::java::lang::String CppHttpRemoteApiProcessClient::toString() const {
    ::zschimmer::javabridge::raw_parameter_list<0> parameter_list;
    CppHttpRemoteApiProcessClient__class* cls = _class.get();
    ::javaproxy::java::lang::String result;
    result.steal_local_ref(cls->_toString____method.jobject_call(get_jobject(), parameter_list));
    return result;
}


::zschimmer::javabridge::Class* CppHttpRemoteApiProcessClient::java_object_class_() const { return _class.get(); }

::zschimmer::javabridge::Class* CppHttpRemoteApiProcessClient::java_class_() { return CppHttpRemoteApiProcessClient__class::class_factory.clas(); }


void CppHttpRemoteApiProcessClient::Lazy_class::initialize() const {
    _value = CppHttpRemoteApiProcessClient__class::class_factory.clas();
}


}}}}}}}}
