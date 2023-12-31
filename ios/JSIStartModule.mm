#import "JSIStartModule.h"

#import <React/RCTBridge+Private.h>
#import <React/RCTUtils.h>
#import <ReactCommon/RCTTurboModule.h>
#import <jsi/jsi.h>

#import "JSIStartHostObject.h"

@implementation JSIStartModule

RCT_EXPORT_MODULE(JSIStart)

RCT_EXPORT_BLOCKING_SYNCHRONOUS_METHOD(install)
{
  NSLog(@"Installing JSI bindings for react-native-jsi-start...");
  RCTBridge* bridge = [RCTBridge currentBridge];
  RCTCxxBridge* cxxBridge = (RCTCxxBridge*)bridge;
  if (cxxBridge == nil) {
    return @false;
  }

  using namespace facebook;

  auto jsiRuntime = (jsi::Runtime*) cxxBridge.runtime;
  if (jsiRuntime == nil) {
    return @false;
  }
  auto& runtime = *jsiRuntime;
  auto callInvoker = bridge.jsCallInvoker;

  auto workerQueue = std::make_shared<margelo::DispatchQueue::dispatch_queue>("JSIStart Thread");
  auto hostObject = std::make_shared<margelo::MGJSIStartHostObject>(callInvoker, workerQueue);
  auto object = jsi::Object::createFromHostObject(runtime, hostObject);
  runtime.global().setProperty(runtime, "__JSIStartProxy", std::move(object));

  NSLog(@"Successfully installed JSI bindings for react-native-jsi-start!");
  return @true;
}

@end
