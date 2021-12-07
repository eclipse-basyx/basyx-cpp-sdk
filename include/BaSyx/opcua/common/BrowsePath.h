/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BROWSE_PATH_H
#define BROWSE_PATH_H

#include <vector>
#include <BaSyx/opcua/common/BrowseName.h>
#include <BaSyx/opcua/common/Utilities.h>

namespace basyx
{
    namespace opcua
    {
        class BrowsePath : private std::vector<BrowseName>
        {
        public:
            using std::vector<BrowseName>::vector;
            /* Forward to the derrived */
            using vector::emplace_back;
            using vector::push_back;
            using vector::size;
            using vector::begin;
            using vector::end;
            using vector::erase;
            using vector::front;
            using vector::operator=;
            using vector::operator[];

            BrowsePath() = default;

            virtual ~BrowsePath() = default;

            BrowsePath(BrowsePath&& t_other) noexcept : vector(std::move(t_other)) {}

            BrowsePath(const BrowsePath& t_other) :vector(t_other) {}

            BrowsePath& operator=(BrowsePath&& t_other) noexcept
            {
                if (this != &t_other)
                {
                    vector(std::move(t_other));
                }
                return *this;
            }

            BrowsePath& operator=(const BrowsePath& t_other)
            {
                if (this != &t_other)
                {
                    vector(t_other);
                }
                return *this;
            }

            template<typename ...Args>
            BrowsePath(Args&& ... paths) : vector({paths ...}){}

            BrowsePath(const std::string& t_browsePathString)
            {
                auto browsePathVect = std::move(opcua::shared::string::splitBySlash(t_browsePathString));

                std::for_each(browsePathVect.begin(), browsePathVect.end(), [&](const std::string& browsePathString) {
                    emplace_back(std::move(BrowseName(browsePathString)));
                });

            }

            static BrowsePath build(uint16_t t_namespace, const std::string& t_rawPath)
            {
                BrowsePath retBrowsePath;

                auto rawPathVect = std::move(opcua::shared::string::splitBySlash(t_rawPath));

                std::for_each(rawPathVect.begin(), rawPathVect.end(), [&](const std::string& rawPathString)
                {
                    retBrowsePath.emplace_back(std::move(BrowseName(t_namespace, std::move(rawPathString))));
                });

                return retBrowsePath;
            }

            BrowsePath getParentPath()
            {
                BrowsePath ret;

                if (this->empty()) {
                    return ret;
                }
                if (this->size() == 1) {
                    return *this;
                }
                else {
                    size_t browsePathIndex(1);
                    for (BrowseName& browseName : *this) {
                        if (browsePathIndex == this->size()) {
                            return ret;
                        }
                        ret.emplace_back(browseName);
                        browsePathIndex++;
                    }
                }
                return ret;
            }

            BrowseName getRootElement()
            {
                return this->front();
            }

            BrowseName getLeafElement()
            {
                return this->back();
            }

            const BrowsePath& operator +(const BrowsePath& t_browsePath)
            {
                this->insert(
                    this->end(),
                    std::make_move_iterator(t_browsePath.begin()),
                    std::make_move_iterator(t_browsePath.end())
                );
                return *this;
            }

            bool operator ==(const BrowsePath& t_browsePath)
            {
                size_t idx(0);
                for (auto browseName : t_browsePath)
                {
                    if (!(this->at(idx) == browseName)) {
                        return false;
                    }
                    idx++;
                }
                return true;
            }

            std::string getNamespaceRemovedString()
            {
                std::string ret;
                for (BrowseName& browseName : *this) {
                    ret += browseName.getText() + "/";
                };
                return ret;
            }

            std::string toString()
            {
                std::string ret;
                for (BrowseName& browseName : *this) {
                    ret += browseName.toString() + "/";
                };
                return ret;
            }

            static BrowsePath fromString(const std::string& t_path)
            {
                BrowsePath ret;
                std::vector<std::string> paths{
                    shared::string::splitBySlash(t_path)
                };

                std::for_each(paths.begin(), paths.end(), [&ret, &t_path](const std::string& _path) {

                    std::vector<std::string> browse_name_pair{
                        shared::string::splitByColon(_path)
                    };
                    if (browse_name_pair.size() < 2) {
                        throw std::invalid_argument(std::string(std::string(t_path) +
                            " @ " +
                            std::string(_path)).c_str());
                    }
                    BrowseName pair{
                        /* Casting assuming the namepsace index
                         will never execeed MAX(uint16_t)     */
                        static_cast<uint16_t>(std::stoi(browse_name_pair.at(0))),
                        browse_name_pair.at(1)
                    };
                    ret.emplace_back(pair);
                });

                return ret;
            }
        };

    }
}

#endif