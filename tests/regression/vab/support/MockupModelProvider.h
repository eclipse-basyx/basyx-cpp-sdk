/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef REGRESSION_TESTS_BACKENDS_PROTOCOLS_BASYX_MOCKUPMODELPROVIDER_H_
#define REGRESSION_TESTS_BACKENDS_PROTOCOLS_BASYX_MOCKUPMODELPROVIDER_H_

#include <string>

#include <BaSyx/vab/core/IModelProvider.h>

using namespace basyx;

class MockupModelProvider : public vab::core::IModelProvider {

public:
    enum class CalledFunction {
        NONE,
        GET,
        SET,
        CREATE,
        DELETE_SIMPLE,
        DELETE_COMPLEX,
        INVOKE
    };

    CalledFunction called;

    std::string path;
    basyx::object val;
    basyx::object clock;

    MockupModelProvider()
        : called { CalledFunction::NONE }
        , clock { 0 }
    {
    }

    virtual ~MockupModelProvider()
    {
    }

    virtual basyx::object getModelPropertyValue(const std::string& path) override
    {
        // Return dummy clock
        if (path.find("clock") != std::string::npos) {
            return clock;
        }
        // Ignore frozen
        else if (path.find("frozen") != std::string::npos) {
            val = basyx::object { nullptr };
        } else {
            called = CalledFunction::GET;
            this->path = path;
            val = basyx::object { 2 };
        };

        return val;
    }

    virtual basyx::object::error setModelPropertyValue(const std::string& path, const basyx::object newValue) override
    {
        // Set dummy clock
        if (path.find("clock") != std::string::npos) {
            clock = std::move(newValue);
        } else // ignore frozen
            if (path.find("frozen") == std::string::npos) {
            called = CalledFunction::SET;
            this->path = path;
            this->val = std::move(newValue);
        }

        return basyx::object::error::None;
    }

    /**
	 * Create/insert a value in a collection
	 */
    virtual basyx::object::error createValue(const std::string& path, const basyx::object addedValue) override
    {
        called = CalledFunction::CREATE;
        this->path = path;
        this->val = std::move(addedValue);
        return basyx::object::error::None;
    }

    virtual basyx::object::error deleteValue(const std::string& path, const basyx::object deletedValue) override
    {
        called = CalledFunction::DELETE_COMPLEX;
        this->path = path;
        this->val = std::move(deletedValue);
        return basyx::object::error::None;
    }

    virtual basyx::object::error deleteValue(const std::string& path) override
    {
        called = CalledFunction::DELETE_SIMPLE;
        this->path = path;
        return basyx::object::error::None;
    }

    virtual basyx::object invokeOperation(const std::string& path, basyx::object parameter) override
    {
        called = CalledFunction::INVOKE;
        this->path = path;
        this->val = std::move(parameter);
        return basyx::object { 3 };
    };
};

#endif /* REGRESSION_TESTS_BACKENDS_PROTOCOLS_BASYX_MOCKUPMODELPROVIDER_H_ */
