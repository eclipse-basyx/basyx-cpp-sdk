/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/opcua/common/Utilities.h>

namespace basyx
{
    namespace opcua
    {
        namespace shared
        {

            constexpr char Namespaces::BASYX_NS_URI[];
            constexpr char Namespaces::OPCUA_NS_URI[];

            namespace string
            {
                std::vector<std::string> split(const std::string & t_path, char t_delimiter)
                {
                    std::vector<std::string> ret;
                    std::string token;
                    std::stringstream ss(t_path);
                    while (std::getline(ss, token, t_delimiter)) {
                        ret.push_back(token);
                    }
                    return ret;
                }

                std::vector<std::string> splitBySlash(const std::string & t_path)
                {
                    return split(t_path, '/');
                }

                std::vector<std::string> splitByColon(const std::string & t_path)
                {
                    return split(t_path, ':');
                }

                bool startsWith(const std::string & t_text, const std::string & t_pattern)
                {
                    if (t_text.length() < t_pattern.length())
                    {
                        return false;
                    }
                    else {
                        return std::equal(t_pattern.begin(), t_pattern.end(), t_text.begin());
                    }
                }

                bool endsWith(const std::string & t_text, const std::string & t_pattern)
                {
                    if (t_pattern.size() > t_text.size())
                    {
                        return false;
                    }
                    else
                    {
                        return std::equal(t_pattern.rbegin(), t_pattern.rend(), t_text.rbegin());
                    }
                }

                void replaceAll(std::string & t_text, const std::string & t_pattern, const std::string & t_replacePattern)
                {
                    size_t position = 0;
                    while ((position = t_text.find(t_pattern, position)) != std::string::npos)
                    {
                        t_text.replace(position, t_pattern.length(), t_replacePattern);
                        position += t_replacePattern.length();
                    }
                }

                void replaceAllWithWhiteSpace(std::string & t_text, const std::string & t_pattern)
                {
                    replaceAll(t_text, t_pattern, "");
                }

                UA_LocalizedText LocalizedText(const std::string & t_locale, const std::string & t_text)
                {
                    UA_LocalizedText ret;

                    ret.locale = UA_STRING(const_cast<char*>(t_locale.c_str()));
                    ret.locale = UA_STRING(const_cast<char*>(t_text.c_str()));

                    return ret;

                }

                std::string getInstanceName(const std::string & t_browseText)
                {
                    auto texToProcess = t_browseText;
                    size_t start(0);

                    while ((start = texToProcess.find(":", start)) != std::string::npos)
                    {
                        texToProcess.replace(start, 2, ":");
                        start += 1;
                    }
                    auto splittedString = splitByColon(t_browseText);
                    return splittedString.back();
                }

                std::string createPropertyName(const std::string & t_propertyName, const std::string & t_instanceName)
                {
                    return t_propertyName + ":" + t_instanceName;
                }

                bool contains(const std::string & t_text, const std::string & t_pattern)
                {
                    return (t_text.find(t_pattern) != std::string::npos);
                }

                void chop(std::string & t_text)
                {
                    if (!t_text.empty())
                        t_text.erase(t_text.length() - 1, 1);
                }

                std::string UAStringToStdString(UA_String* t_uaString)
                {
                    return std::string(reinterpret_cast<char*>(t_uaString->data), t_uaString->length);
                }

                std::string UAStringToStdString(const UA_String& t_uaString)
                {
                    return std::string(reinterpret_cast<char*>(t_uaString.data), t_uaString.length);
                }

                UA_String UAStringFromStdString(const std::string& t_stdString)
                {
                    UA_String str = UA_STRING(const_cast<char*>(t_stdString.c_str()));
                    return str;
                }
            }

            namespace diag
            {
                std::string getErrorString(UA_StatusCode t_scode)
                {
                    return std::string(UA_StatusCode_name(t_scode));
                }

                bool isStatusBad(UA_StatusCode t_status)
                {
                    return (UA_STATUSCODE_GOOD != t_status);
                }
            }
        }
    }
}