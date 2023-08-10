#include <fbjni/fbjni.h>
#include <ReactCommon/CallInvokerHolder.h>
#include <jni.h>
#include <jsi/jsi.h>
#include "JSIStartHostObject.h"

using namespace facebook;

class JSIStartCppAdapter : public jni::HybridClass<JSIStartCppAdapter> {
public:
static auto constexpr kJavaDescriptor = "Lcom/margelo/JSIStart/JSIStartModule;";

static jni::local_ref<jni::HybridClass<JSIStartCppAdapter>::jhybriddata> initHybrid(
  jni::alias_ref<jhybridobject> jThis) {
  return makeCxxInstance();
}

explicit JSIStartCppAdapter() {
}

void install(jsi::Runtime& runtime, std::shared_ptr<facebook::react::CallInvoker> jsCallInvoker) {
  auto workerQueue = std::make_shared<margelo::DispatchQueue::dispatch_queue>("JSIStart Thread");
  auto hostObject = std::make_shared<margelo::JSIStartHostObject>(jsCallInvoker, workerQueue);
  auto object = jsi::Object::createFromHostObject(runtime, hostObject);
  runtime.global().setProperty(runtime, "__JSIStartProxy", std::move(object));
}

void nativeInstall(jlong jsiPtr, jni::alias_ref<facebook::react::CallInvokerHolder::javaobject>
                   jsCallInvokerHolder) {
  auto jsCallInvoker = jsCallInvokerHolder->cthis()->getCallInvoker();
  auto runtime = reinterpret_cast<jsi::Runtime*>(jsiPtr);
  if (runtime) {
    install(*runtime, jsCallInvoker);
  }
  // if runtime was nullptr, MGJSIStart will not be installed. This should only happen while Remote Debugging (Chrome), but will be weird either way.
}

static void registerNatives() {
  registerHybrid({
      makeNativeMethod("initHybrid", JSIStartCppAdapter::initHybrid),
      makeNativeMethod("nativeInstall", JSIStartCppAdapter::nativeInstall)
    });
}

private:
friend HybridBase;
};

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *) {
  return facebook::jni::initialize(vm, [] {
    JSIStartCppAdapter::registerNatives();
  });
}
