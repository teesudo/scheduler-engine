// *** Generated by com.sos.scheduler.engine.cplusplus.generator ***

#include "_precompiled.h"

#include "com__sos__scheduler__engine__kernel__order__OrderSubsystem.h"
#include "com__sos__scheduler__engine__kernel__order__jobchain__Node.h"
#include "java__lang__Object.h"
#include "java__lang__String.h"

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace order { 

struct OrderSubsystem__class : ::zschimmer::javabridge::Class
{
    OrderSubsystem__class(const string& class_name);
   ~OrderSubsystem__class();

    ::zschimmer::javabridge::Method const _persistNodeState__Lcom_sos_scheduler_engine_kernel_order_jobchain_Node_2__method;

    static const ::zschimmer::javabridge::class_factory< OrderSubsystem__class > class_factory;
};

const ::zschimmer::javabridge::class_factory< OrderSubsystem__class > OrderSubsystem__class::class_factory ("com.sos.scheduler.engine.kernel.order.OrderSubsystem");

OrderSubsystem__class::OrderSubsystem__class(const string& class_name) :
    ::zschimmer::javabridge::Class(class_name)
    ,_persistNodeState__Lcom_sos_scheduler_engine_kernel_order_jobchain_Node_2__method(this, "persistNodeState", "(Lcom/sos/scheduler/engine/kernel/order/jobchain/Node;)V"){}

OrderSubsystem__class::~OrderSubsystem__class() {}




OrderSubsystem::OrderSubsystem(jobject jo) { if (jo) assign_(jo); }

OrderSubsystem::OrderSubsystem(const OrderSubsystem& o) { assign_(o.get_jobject()); }

#ifdef Z_HAS_MOVE_CONSTRUCTOR
    OrderSubsystem::OrderSubsystem(OrderSubsystem&& o) { set_jobject(o.get_jobject());  o.set_jobject(NULL); }
#endif

OrderSubsystem::~OrderSubsystem() { assign_(NULL); }




void OrderSubsystem::persistNodeState(const ::zschimmer::javabridge::proxy_jobject< ::javaproxy::com::sos::scheduler::engine::kernel::order::jobchain::Node >& p0) const {
    ::zschimmer::javabridge::raw_parameter_list<1> parameter_list;
    parameter_list._jvalues[0].l = p0.get_jobject();
    OrderSubsystem__class* cls = _class.get();
    cls->_persistNodeState__Lcom_sos_scheduler_engine_kernel_order_jobchain_Node_2__method.call(get_jobject(), parameter_list);
}


::zschimmer::javabridge::Class* OrderSubsystem::java_object_class_() const { return _class.get(); }

::zschimmer::javabridge::Class* OrderSubsystem::java_class_() { return OrderSubsystem__class::class_factory.clas(); }


void OrderSubsystem::Lazy_class::initialize() const {
    _value = OrderSubsystem__class::class_factory.clas();
}


}}}}}}}
