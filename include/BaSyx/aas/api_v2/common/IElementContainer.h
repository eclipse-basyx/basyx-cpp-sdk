/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_API_V2_COMMON_IELEMENTCONTAINER_H
#define BASYX_SUBMODEL_API_V2_COMMON_IELEMENTCONTAINER_H

#include <BaSyx/aas/api_v2/submodelelement/ISubmodelElement.h>
#include <BaSyx/aas/api_v2/qualifier/IReferable.h>

#include <BaSyx/util/util.h>

#include <memory>

namespace basyx {
namespace aas {
namespace api {


template<class IElementType>
class IElementContainer
{
public:
	using elementPtr_t = std::unique_ptr<IElementType>;
public:
	virtual ~IElementContainer() = 0;

	virtual IElementType * const getElement(const std::string & idShort) const = 0;
	virtual IElementType * const getElement(std::size_t n) const = 0;

	virtual IReferable * getParent() const = 0;
	virtual void addElement(elementPtr_t element) = 0;

	virtual std::size_t size() const = 0;

	template<typename SubElement_t, typename... Args>
	SubElement_t * createElement(Args && ... args) 
	{
		auto ptr = util::make_unique<SubElement_t>(std::forward<Args>(args)...);
		auto ret = ptr.get();
		ptr->setParent(this->getParent());
		this->addElement(std::move(ptr));
		return ret;
	};

};

template<class IElementType>
inline IElementContainer<IElementType>::~IElementContainer() = default;

}
}
}

#endif /* BASYX_SUBMODEL_API_V2_COMMON_IELEMENTCONTAINER_H */
