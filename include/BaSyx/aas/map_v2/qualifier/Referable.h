/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef BASYX_SUBMODEL_MAP_V2_QUALIFIER_REFERABLE_H
#define BASYX_SUBMODEL_MAP_V2_QUALIFIER_REFERABLE_H

#include <BaSyx/aas/api_v2/qualifier/IReferable.h>
#include <BaSyx/aas/map_v2/common/LangStringSet.h>

#include <BaSyx/vab/ElementMap.h>

namespace basyx {
namespace aas {
namespace map {


class Referable
  : public virtual api::IReferable
  , public virtual vab::ElementMap
{
public:
	struct Path {
		static constexpr char IdShort[] = "idShort";
		static constexpr char Category[] = "category";
		static constexpr char Description[] = "description";
		static constexpr char Parent[] = "parent";
	};

private:
	map::LangStringSet description;
	IReferable * parent = nullptr;

public:
	virtual ~Referable() = default;

	// Constructors
	Referable(const std::string & idShort, Referable * parent = nullptr);
	//Referable(const IReferable & other);

	Referable(basyx::object, Referable * parent = nullptr);

	// Inherited via IReferable
	virtual const std::string & getIdShort() const override;
	virtual const std::string * const getCategory() const override;
	virtual LangStringSet & getDescription() override;
	virtual const LangStringSet & getDescription() const override;

	virtual void setParent(IReferable * parent) override;
	virtual IReferable * getParent() const override;

	void setIdShort(const std::string & shortID);
	void setCategory(const std::string & category) override;

	void setDescription(const LangStringSet &);

	bool hasParent() const noexcept;
	bool hasDescription() const noexcept;
	bool hasCategory() const noexcept;

	virtual KeyElements getKeyElementType() const override { return KeyElements::Unknown; };
	virtual simple::Reference getReference() const override;
	virtual simple::Key getKey(bool local = true) const override;
};


}
}
}

#endif /* BASYX_SUBMODEL_MAP_V2_QUALIFIER_REFERABLE_H */
