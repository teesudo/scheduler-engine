// *** Generated by com.sos.scheduler.engine.cplusplus.generator ***

#include "spooler.h"
#include "../zschimmer/java.h"
#include "../zschimmer/Has_proxy.h"
#include "../zschimmer/javaproxy.h"
#include "../zschimmer/lazy.h"

using namespace ::zschimmer;
using namespace ::zschimmer::javabridge;

namespace zschimmer { namespace javabridge { 

    template<> const class_factory<Proxy_class> has_proxy< ::sos::scheduler::Job >::proxy_class_factory("com.sos.scheduler.engine.kernel.cppproxy.JobCImpl");

}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL default_1process_1class_1path(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::default_process_class_path()");
        return env.jstring_from_string(o_->default_process_class_path());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL description(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::description()");
        return env.jstring_from_string(o_->description());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static void JNICALL enqueue_1taskPersistentState__Lcom_sos_scheduler_engine_data_job_TaskPersistentState_2(JNIEnv* jenv, jobject, jlong cppReference, jobject p0)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::enqueue_taskPersistentState()");
        (o_->enqueue_taskPersistentState(::javaproxy::com::sos::scheduler::engine::data::job::TaskPersistentState(p0)));
    }
    catch(const exception& x) {
        env.set_java_exception(x);
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL file(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::file()");
        return env.jstring_from_string(o_->file());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL file_1based_1error_1string(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::file_based_error_string()");
        return env.jstring_from_string(o_->file_based_error_string());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jint JNICALL file_1based_1state(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::file_based_state()");
        return (o_->file_based_state());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jint();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jlong JNICALL file_1modification_1time_1t(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::file_modification_time_t()");
        return (o_->file_modification_time_t());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jlong();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL has_1base_1file(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::has_base_file()");
        return (o_->has_base_file());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL is_1file_1based(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::is_file_based()");
        return (o_->is_file_based());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL is_1file_1based_1reread(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::is_file_based_reread()");
        return (o_->is_file_based_reread());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL is_1in_1period(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::is_in_period()");
        return (o_->is_in_period());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL is_1permanently_1stopped(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::is_permanently_stopped()");
        return (o_->is_permanently_stopped());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL is_1task_1ready_1for_1order__J(JNIEnv* jenv, jobject, jlong cppReference, jlong p0)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::is_task_ready_for_order()");
        return (o_->is_task_ready_for_order((::sos::scheduler::Process_class*)p0));
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL is_1to_1be_1removed(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::is_to_be_removed()");
        return (o_->is_to_be_removed());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL is_1visible(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::is_visible()");
        return (o_->is_visible());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jobject JNICALL java_1tasks(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::java_tasks()");
        return (o_->java_tasks()).local_ref();
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jobject();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jobject JNICALL log(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::log()");
        return Has_proxy::jobject_of(o_->log());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jobject();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jint JNICALL max_1tasks(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::max_tasks()");
        return (o_->max_tasks());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jint();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jobject JNICALL missing_1requisites_1java(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::missing_requisites_java()");
        return java_array_from_c(o_->missing_requisites_java());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jobject();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL name(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::name()");
        return env.jstring_from_string(o_->name());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL name_1is_1fixed(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::name_is_fixed()");
        return (o_->name_is_fixed());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jlong JNICALL next_1possible_1start_1millis(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::next_possible_start_millis()");
        return (o_->next_possible_start_millis());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jlong();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jlong JNICALL next_1start_1time_1millis(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::next_start_time_millis()");
        return (o_->next_start_time_millis());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jlong();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL path(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::path()");
        return env.jstring_from_string(o_->path());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jobject JNICALL replacement_1java(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::replacement_java()");
        return (o_->replacement_java()).local_ref();
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jobject();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jint JNICALL running_1tasks_1count(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::running_tasks_count()");
        return (o_->running_tasks_count());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jint();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL script_1text(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::script_text()");
        return env.jstring_from_string(o_->script_text());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static void JNICALL set_1force_1file_1reread(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::set_force_file_reread()");
        (o_->set_force_file_reread());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static void JNICALL set_1state_1cmd__Ljava_lang_String_2(JNIEnv* jenv, jobject, jlong cppReference, jstring p0)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::set_state_cmd()");
        (o_->set_state_cmd(env.string_from_jstring(p0)));
    }
    catch(const exception& x) {
        env.set_java_exception(x);
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jobject JNICALL source_1xml_1bytes(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::source_xml_bytes()");
        return java_byte_array_from_c(o_->source_xml_bytes());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jobject();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL state_1name(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::state_name()");
        return env.jstring_from_string(o_->state_name());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL state_1text(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::state_text()");
        return env.jstring_from_string(o_->state_text());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jstring JNICALL title(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::title()");
        return env.jstring_from_string(o_->title());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jstring();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jobject JNICALL unavailable_1lock_1path_1strings(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::unavailable_lock_path_strings()");
        return java_array_from_c(o_->unavailable_lock_path_strings());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jobject();
    }
}

}}}}}}}

namespace javaproxy { namespace com { namespace sos { namespace scheduler { namespace engine { namespace kernel { namespace cppproxy { 

static jboolean JNICALL waiting_1for_1process(JNIEnv* jenv, jobject, jlong cppReference)
{
    Env env = jenv;
    try {
        ::sos::scheduler::Job* o_ = has_proxy< ::sos::scheduler::Job >::of_cpp_reference(cppReference,"::sos::scheduler::Job::waiting_for_process()");
        return (o_->waiting_for_process());
    }
    catch(const exception& x) {
        env.set_java_exception(x);
        return jboolean();
    }
}

}}}}}}}

const static JNINativeMethod native_methods[] = {
    { (char*)"default_process_class_path__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::default_1process_1class_1path },
    { (char*)"description__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::description },
    { (char*)"enqueue_taskPersistentState__native", (char*)"(JLcom/sos/scheduler/engine/data/job/TaskPersistentState;)V", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::enqueue_1taskPersistentState__Lcom_sos_scheduler_engine_data_job_TaskPersistentState_2 },
    { (char*)"file__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::file },
    { (char*)"file_based_error_string__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::file_1based_1error_1string },
    { (char*)"file_based_state__native", (char*)"(J)I", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::file_1based_1state },
    { (char*)"file_modification_time_t__native", (char*)"(J)J", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::file_1modification_1time_1t },
    { (char*)"has_base_file__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::has_1base_1file },
    { (char*)"is_file_based__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::is_1file_1based },
    { (char*)"is_file_based_reread__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::is_1file_1based_1reread },
    { (char*)"is_in_period__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::is_1in_1period },
    { (char*)"is_permanently_stopped__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::is_1permanently_1stopped },
    { (char*)"is_task_ready_for_order__native", (char*)"(JJ)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::is_1task_1ready_1for_1order__J },
    { (char*)"is_to_be_removed__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::is_1to_1be_1removed },
    { (char*)"is_visible__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::is_1visible },
    { (char*)"java_tasks__native", (char*)"(J)Ljava/util/ArrayList;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::java_1tasks },
    { (char*)"log__native", (char*)"(J)Lcom/sos/scheduler/engine/kernel/cppproxy/Prefix_logC;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::log },
    { (char*)"max_tasks__native", (char*)"(J)I", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::max_1tasks },
    { (char*)"missing_requisites_java__native", (char*)"(J)[Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::missing_1requisites_1java },
    { (char*)"name__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::name },
    { (char*)"name_is_fixed__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::name_1is_1fixed },
    { (char*)"next_possible_start_millis__native", (char*)"(J)J", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::next_1possible_1start_1millis },
    { (char*)"next_start_time_millis__native", (char*)"(J)J", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::next_1start_1time_1millis },
    { (char*)"path__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::path },
    { (char*)"replacement_java__native", (char*)"(J)Lcom/sos/scheduler/engine/kernel/filebased/FileBased;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::replacement_1java },
    { (char*)"running_tasks_count__native", (char*)"(J)I", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::running_1tasks_1count },
    { (char*)"script_text__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::script_1text },
    { (char*)"set_force_file_reread__native", (char*)"(J)V", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::set_1force_1file_1reread },
    { (char*)"set_state_cmd__native", (char*)"(JLjava/lang/String;)V", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::set_1state_1cmd__Ljava_lang_String_2 },
    { (char*)"source_xml_bytes__native", (char*)"(J)[B", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::source_1xml_1bytes },
    { (char*)"state_name__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::state_1name },
    { (char*)"state_text__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::state_1text },
    { (char*)"title__native", (char*)"(J)Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::title },
    { (char*)"unavailable_lock_path_strings__native", (char*)"(J)[Ljava/lang/String;", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::unavailable_1lock_1path_1strings },
    { (char*)"waiting_for_process__native", (char*)"(J)Z", (void*)::javaproxy::com::sos::scheduler::engine::kernel::cppproxy::waiting_1for_1process }
};

namespace zschimmer { namespace javabridge { 

    template<> void has_proxy< ::sos::scheduler::Job >::register_cpp_proxy_class_in_java() {
        Env env;
        Class* cls = has_proxy< ::sos::scheduler::Job >::proxy_class_factory.clas();
        int ret = env->RegisterNatives(*cls, native_methods, sizeof native_methods / sizeof native_methods[0]);
        if (ret < 0)  env.throw_java("RegisterNatives", "com.sos.scheduler.engine.kernel.cppproxy.JobCImpl");
    }

}}
