// *** Generated by com.sos.scheduler.engine.cplusplus.generator ***

#include "_precompiled.h"

#include "com__sos__scheduler__engine__kernel__cppproxy__Sink_nodeC.h"
#include "com__sos__scheduler__engine__kernel__cppproxy__Order_queueC.h"
#include "java__lang__Object.h"
#include "java__lang__String.h"

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

struct Sink_nodeC__class : ::zschimmer::javabridge::Class
{
    Sink_nodeC__class(const string& class_name);
   ~Sink_nodeC__class();


    static const ::zschimmer::javabridge::class_factory< Sink_nodeC__class > class_factory;
};

const ::zschimmer::javabridge::class_factory< Sink_nodeC__class > Sink_nodeC__class::class_factory ("com.sos.scheduler.engine.kernel.cppproxy.Sink_nodeC");

Sink_nodeC__class::Sink_nodeC__class(const string& class_name) :
    ::zschimmer::javabridge::Class(class_name)
{}

Sink_nodeC__class::~Sink_nodeC__class() {}




Sink_nodeC::Sink_nodeC(jobject jo) { if (jo) assign_(jo); }

Sink_nodeC::Sink_nodeC(const Sink_nodeC& o) { assign_(o.get_jobject()); }

#ifdef Z_HAS_MOVE_CONSTRUCTOR
    Sink_nodeC::Sink_nodeC(Sink_nodeC&& o) { set_jobject(o.get_jobject());  o.set_jobject(NULL); }
#endif

Sink_nodeC::~Sink_nodeC() { assign_(NULL); }





::zschimmer::javabridge::Class* Sink_nodeC::java_object_class_() const { return _class.get(); }

::zschimmer::javabridge::Class* Sink_nodeC::java_class_() { return Sink_nodeC__class::class_factory.clas(); }


void Sink_nodeC::Lazy_class::initialize() const {
    _value = Sink_nodeC__class::class_factory.clas();
}


}}}}}}}
