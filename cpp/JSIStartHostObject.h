// Copyright 2022 Margelo
#ifndef CPP_JSIStartHOSTOBJECT_H_
#define CPP_JSIStartHOSTOBJECT_H_

#include <jsi/jsi.h>
#include <ReactCommon/CallInvoker.h>
#include <memory>
#include <openssl/ossl_typ.h>
#include "MGDispatchQueue.h"
#include "JSIStartHostObject.h"
#include "MGSmartHostObject.h"

namespace margelo
{

    namespace jsi = facebook::jsi;
    namespace react = facebook::react;

    class JSI_EXPORT JSIStartHostObject : public MGSmartHostObject
    {
    public:
        explicit JSIStartHostObject(std::shared_ptr<react::CallInvoker> jsCallInvoker,
                                       std::shared_ptr<DispatchQueue::dispatch_queue> workerQueue);

        virtual ~JSIStartHostObject()
        {
        }

        // static BN_CTX *bn_ctx;
    };

} // namespace margelo

#endif // CPP_JSIStartHOSTOBJECT_H_
