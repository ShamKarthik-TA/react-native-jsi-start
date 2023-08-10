// Copyright 2022 Margelo
#include "JSIStartHostObject.h"
#include <ReactCommon/TurboModuleUtils.h>
#include <jsi/jsi.h>
#include <vector>
#include <memory>
#include <openssl/bn.h>
#include <cstdio>

namespace margelo
{

    namespace jsi = facebook::jsi;

    // BN_CTX *JSIStartHostObject::bn_ctx = BN_CTX_new();

    JSIStartHostObject::JSIStartHostObject(std::shared_ptr<react::CallInvoker> jsCallInvoker,
                                                 std::shared_ptr<DispatchQueue::dispatch_queue> workerQueue) : MGSmartHostObject(jsCallInvoker, workerQueue)
    {
       

    this->fields.push_back(HOST_LAMBDA("helloworld", {
            // std::string helloworld = "helloworld";

            // std::shared_ptr res = std::make_shared(helloworld);

            // return jsi::Object::createFromHostObject(runtime, res);
            return jsi::Value(runtime, (int)(25));
        }));

    }

    return runtime.global().getPropertyAsFunction(runtime, "__createBN").call(runtime, obj);

} // namespace margelo
