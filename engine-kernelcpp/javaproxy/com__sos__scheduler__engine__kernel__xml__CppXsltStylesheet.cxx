// *** Generated by com.sos.scheduler.engine.cplusplus.generator ***

#include "_precompiled.h"

#include "com__sos__scheduler__engine__kernel__xml__CppXsltStylesheet.h"
#include "java__lang__Object.h"
#include "java__lang__String.h"
#include "java__util__HashMap.h"
#include "org__w3c__dom__Document.h"

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace xml { 

struct CppXsltStylesheet__class : ::zschimmer::javabridge::Class
{
    CppXsltStylesheet__class(const string& class_name);
   ~CppXsltStylesheet__class();

    ::zschimmer::javabridge::Method const __constructor__Lorg_w3c_dom_Document_2__method;
    ::zschimmer::javabridge::Method const _apply__Lorg_w3c_dom_Document_2Ljava_util_HashMap_2__method;

    static const ::zschimmer::javabridge::class_factory< CppXsltStylesheet__class > class_factory;
};

const ::zschimmer::javabridge::class_factory< CppXsltStylesheet__class > CppXsltStylesheet__class::class_factory ("com.sos.scheduler.engine.kernel.xml.CppXsltStylesheet");

CppXsltStylesheet__class::CppXsltStylesheet__class(const string& class_name) :
    ::zschimmer::javabridge::Class(class_name)
    ,__constructor__Lorg_w3c_dom_Document_2__method(this, "<init>", "(Lorg/w3c/dom/Document;)V")
    ,_apply__Lorg_w3c_dom_Document_2Ljava_util_HashMap_2__method(this, "apply", "(Lorg/w3c/dom/Document;Ljava/util/HashMap;)Lorg/w3c/dom/Document;"){}

CppXsltStylesheet__class::~CppXsltStylesheet__class() {}



CppXsltStylesheet CppXsltStylesheet::new_instance(const ::zschimmer::javabridge::proxy_jobject< ::javaproxy::org::w3c::dom::Document >& p0) {
    CppXsltStylesheet result;
    result.java_object_allocate_();
    ::zschimmer::javabridge::raw_parameter_list<1> parameter_list;
    parameter_list._jvalues[0].l = p0.get_jobject();
    CppXsltStylesheet__class* cls = result._class.get();
    cls->__constructor__Lorg_w3c_dom_Document_2__method.call(result.get_jobject(), parameter_list);
    return result;
}


CppXsltStylesheet::CppXsltStylesheet(jobject jo) { if (jo) assign_(jo); }

CppXsltStylesheet::CppXsltStylesheet(const CppXsltStylesheet& o) { assign_(o.get_jobject()); }

#ifdef Z_HAS_MOVE_CONSTRUCTOR
    CppXsltStylesheet::CppXsltStylesheet(CppXsltStylesheet&& o) { set_jobject(o.get_jobject());  o.set_jobject(NULL); }
#endif

CppXsltStylesheet::~CppXsltStylesheet() { assign_(NULL); }




::javaproxy::org::w3c::dom::Document CppXsltStylesheet::apply(const ::zschimmer::javabridge::proxy_jobject< ::javaproxy::org::w3c::dom::Document >& p0, const ::zschimmer::javabridge::proxy_jobject< ::javaproxy::java::util::HashMap >& p1) const {
    ::zschimmer::javabridge::raw_parameter_list<2> parameter_list;
    parameter_list._jvalues[0].l = p0.get_jobject();
    parameter_list._jvalues[1].l = p1.get_jobject();
    CppXsltStylesheet__class* cls = _class.get();
    ::javaproxy::org::w3c::dom::Document result;
    result.steal_local_ref(cls->_apply__Lorg_w3c_dom_Document_2Ljava_util_HashMap_2__method.jobject_call(get_jobject(), parameter_list));
    return result;
}


::zschimmer::javabridge::Class* CppXsltStylesheet::java_object_class_() const { return _class.get(); }

::zschimmer::javabridge::Class* CppXsltStylesheet::java_class_() { return CppXsltStylesheet__class::class_factory.clas(); }


void CppXsltStylesheet::Lazy_class::initialize() const {
    _value = CppXsltStylesheet__class::class_factory.clas();
}


}}}}}}}
