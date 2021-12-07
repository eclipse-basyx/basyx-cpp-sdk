/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef NODE_DESCRIPTION_H
#define NODE_DESCRIPTION_H

#include <string>

class NodeDescription
{
public:
	NodeDescription():m_description(std::make_tuple("en-US", std::string())) {}

    ~NodeDescription() = default;

    NodeDescription(const std::string& t_langCode,
                    const std::string& t_text):
                    m_description{std::make_tuple(t_langCode, t_text)}{}

    const std::string& getLangCode() const{
        return std::get<0>(m_description);
    }

    const std::string& getText() const {
        return std::get<1>(m_description);
    }

    std::string toString(){
        return "("+ getLangCode()+")" + getText();
    }
    
private:
    std::tuple<std::string, std::string> m_description;
};

#endif