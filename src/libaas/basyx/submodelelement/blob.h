#pragma once

#include <basyx/langstringset.h>
#include <basyx/modeltype.h>
#include <basyx/submodelelement/dataelement.h>

#include <basyx/util/string_view/string_view.hpp>

#include <basyx/serialization/serializable.h>

#include <string>

namespace basyx {

class Blob : public DataElement,
             private ModelType<ModelTypes::Blob>,
             private serialization::Serializable<Blob> {
public:
    using blobType_t = std::vector<uint8_t>;
private:
    std::string mimeType;
    blobType_t blobValue;
public:
    Blob(util::string_view idShort, util::string_view mimeType)
        : DataElement(idShort)
        , mimeType(mimeType.to_string()) {};

    Blob(util::string_view idShort, util::string_view mimeType, blobType_t blob)
        : DataElement(idShort)
        , mimeType(mimeType.to_string())
        , blobValue(std::move(blob)) {};

    Blob(const Blob&) = default;
    Blob& operator=(const Blob&) = default;

    Blob(Blob&&) = default;
    Blob& operator=(Blob&&) = default;

    ~Blob() = default;
public:
    using ModelType::get_model_type;
public:
    const std::string& getMimeType() const;
    void setMimeType(util::string_view mimeType);

    const blobType_t& getBlob() const;
    blobType_t& getBlob();
    void setBlob(blobType_t blob);
public:
    static Blob fromLocalFile(util::string_view idShort, util::string_view mimeType, util::string_view filepath);
};

}
