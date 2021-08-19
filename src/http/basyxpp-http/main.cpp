#include <basyxpp-http/httpHandler.h>

#include <spdlog/spdlog.h>

#include <basyx/submodel.h>

#include <basyx/submodelelement/multilanguageproperty.h>
#include <basyx/submodelelement/submodelelementcollection.h>

using namespace basyx;
using namespace basyx::CREST;

int main() 
{
	spdlog::info("C++ submodel REST server");

	// Create submodels
	Submodel sm("test", Identifier::IRDI("testSMIRDI"));
	sm.set_category("submodel test");

	Submodel sm2("testSM", Identifier::IRDI("testSMIRDI2"));

	sm.get_submodel_elements().add(Property<std::string>("testProperty", "Yay a value!"));
	sm.get_submodel_elements().add(Property<int>("intProp", 32));

	sm.get_submodel_elements().add(SubmodelElementCollection("collection",
		MultiLanguageProperty("multiLang", { {"de", "beispiel"}, {"en", "example"} })
	));

	sm2.get_submodel_elements().add(Property<std::string>("testProperty2", "Values and values! :O"));

	httpHandler handler(std::string("0.0.0.0"), 8080);
	handler.addSubmodelToServer(sm2);
	if (handler.addSubmodelToServer(sm) == ERROR_CODES::ERR_OK)
		spdlog::info("Submodel added to server");
	else
		spdlog::error("Error adding submodel to server");
	handler.run();

	return 0;
}
