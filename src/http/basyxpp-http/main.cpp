#include <basyxpp-http/httpHandler.h>

#include <spdlog/spdlog.h>

#include <basyx/submodel.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>

using namespace basyx;
using namespace basyx::CREST;

void print_elems(basyx::SubmodelElementCollection & coll)
{
	auto json = basyx::serialization::json::serialize(coll);
	spdlog::info("[Elements]\n{}", json.dump(4));
};

#define PRINT() print_elems(sm.get_submodel_elements());

int main()
{
    spdlog::info("C++ submodel REST server");

    // Create submodels
    Submodel sm("sm1", Identifier::IRI("https://admin-shell.io/cpp#sm1"));
    sm.set_category("test");
    sm.setSemanticId("0173-1#02-AAR972#002");
    sm.setAdministration({ "1.0", "v2" });

    Submodel sm2("sm2", Identifier::IRI("https://admin-shell.io/cpp#sm2"));

	PRINT();
    sm.get_submodel_elements().add(Property<std::string>("testProperty1", "Yay a value!"));
	PRINT();
    sm.get_submodel_elements().add(Property<std::string>("testProperty2", "Values and values! :O"));
	PRINT();
    sm.get_submodel_elements().add(Property<uint32_t>("intProp", 32));
	PRINT();

    sm.get_submodel_elements().add(SubmodelElementCollection("collection",
        MultiLanguageProperty("multiLang", { { "de", "beispiel" }, { "en", "example" } }),
        Property<float>("floatProp", 5.0f),
        SubmodelElementCollection("collection2",
            Property<float>("floatProp", 5.0f),
            Property<float>("floatProp2", 5.0f))));

    sm2.get_submodel_elements().add(Property<std::string>("testProperty2", "TEST"));
	PRINT();

    httpHandler handler(std::string("0.0.0.0"), 8080);
    handler.addSubmodelToServer(sm2);
    if (handler.addSubmodelToServer(sm) == ERROR_CODES::ERR_OK)
        spdlog::info("Submodel added to server");
    else
        spdlog::error("Error adding submodel to server");
    handler.run();

    return 0;
}
