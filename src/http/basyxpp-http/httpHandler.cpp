#include "httpHandler.h"

#include <basyx/serialization/json/serializer.h>

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>


#include <iostream>

using namespace basyx::CREST;
using namespace httplib;
using namespace basyx;


const std::string regex_idShort = "([a-zA-Z][a-zA-Z0-9_]+)";
const std::string regex_idShortPath = "([a-zA-Z][a-zA-Z0-9_/]+)";

template<typename T>
inline util::string_view view_from_match(const T & t) {
	return util::string_view( &(*t.first), t.length() );
};

void httpHandler::handleRequests() 
{
	// Retrieves all Submodels
	server.Get("/submodels", [](const Request& req, Response& res) {
		res.set_content("TODO: Implement view of hosted submodels!", TXT_PLAIN);
		spdlog::info("GET all submodels");
	});

	// Retrieves the entire Submodel
	server.Get("/submodels/" + regex_idShort + "/submodel/?" , [this](
		const Request& req, Response& res)
	{
		auto idShort = view_from_match(req.matches[1]);
		spdlog::info("GET submodel: {}", idShort);

		auto sm = getSubmodel(idShort);

		if (!sm) {
			spdlog::warn("Submodel {} not found!", idShort);
			res.set_content("Submodel not found!", TXT_PLAIN);
			return;
		}

		auto json = basyx::serialization::json::serialize(*sm);
		res.set_content(json.dump(4), TXT_JSON);
	});

	// Retrieves the minimized version of a Submodel, i.e. only the values of SubmodelElements are serialized and returned
	server.Get("/submodels/" + regex_idShort + "/submodel/values/?", [this](
		const Request& req, Response& res)
	{
		auto idShort = view_from_match(req.matches[1]);
		spdlog::info("GET submodel values: {}", idShort);
	});

	// Retrieves all Submodel-Elements from the Submodel
	server.Get("/submodels/" + regex_idShort + "/submodel/submodelElements/?", [this](
		const Request& req, Response& res) 
	{
		auto idShort = view_from_match(req.matches[1]);
		spdlog::info("GET submodel elements: {}", idShort);

		Submodel * s = getSubmodel(idShort);

		if (!s) {
			spdlog::warn("Submodel {} not found!", idShort);
			res.set_content("Submodel not found!", TXT_PLAIN);
			return;
		}

		auto & submodelElements = s->getSubmodelElements();

		auto json = basyx::serialization::json::json_t::array();

		for (const auto & element : submodelElements) {
			json.emplace_back(basyx::serialization::json::serialize(*element));
		}

		//auto json = basyx::serialization::json::serialize(submodelElements);
		res.set_content(json.dump(4), TXT_JSON);
	});

	// Retrieves a specific Submodel-Element from the Submodel
	server.Get("/submodels/" + regex_idShort + "/submodel/submodelElements/" + regex_idShortPath, [this](
		const Request& req, Response& res)
	{
		auto idShort = view_from_match(req.matches[1]);
		auto idShortPath = view_from_match(req.matches[2]);
		
		spdlog::info("GET submodelElements: {}/{}", idShort, idShortPath);

		auto sm = getSubmodel(idShort);

		if (!sm) {
			spdlog::warn("Submodel {} not found!", idShort);
			res.set_content("Submodel not found!", TXT_PLAIN);
			return;
		}

		auto pathList = util::algorithm::string::split(idShortPath, '/');
		auto element = getSubmodelElementByPathList(pathList, *sm);

		if(!element) {
			spdlog::warn("SubmodelElement {} not found!", idShortPath);
			res.set_content("SubmodelElement not found!", TXT_PLAIN);
			return;
		}

		auto json = basyx::serialization::json::serialize(*element);
		res.set_content(json.dump(4), TXT_JSON);	
	});

	// Retrieves the value of a specific Submodel-Element from the Submodel
	server.Get("/submodels/" + regex_idShort + "/submodel/submodelElements/" + regex_idShortPath + "/value/?", [this](
		const Request& req, Response& res)
	{
		auto idShort = view_from_match(req.matches[1]);
		auto idShortPath = view_from_match(req.matches[2]);

		spdlog::info("GET submodelElements: {}/{}", idShort, idShortPath);

		auto sm = getSubmodel(idShort);

		if (!sm) {
			spdlog::warn("Submodel {} not found!", idShort);
			res.set_content("Submodel not found!", TXT_PLAIN);
			return;
		}

		auto pathList = util::algorithm::string::split(idShortPath, '/');
		auto element = getSubmodelElementByPathList(pathList, *sm);

		if (!element) {
			spdlog::warn("SubmodelElement {} not found!", idShortPath);
			res.set_content("SubmodelElement not found!", TXT_PLAIN);
			return;
		}

		auto json = basyx::serialization::json::serialize(*element);
		res.set_content(json.dump(4), TXT_JSON);
	});

	server.Put(R"((/submodels/[-_.~+#\/\w]*))", [this](
		const Request& req, Response& res) {

		std::cout << "PUT Handler: " << req.matches[1] << std::endl;
		std::cout << req.body << std::endl;

		spdlog::warn("PUT of submodel not implemented!");
		res.set_content("PUT of submodel not implemented!", TXT_JSON);
		return;
	});

	server.Post(R"((/submodels/[-_.~+#\/\w]*))", [this](
		const Request& req, Response& res) {

		// POST für Operations:
		// Übergabeparameter (Operation Variables) als Biespiel in Postman
		// collection in "BigInterface changes" Branch des C# SDK's zu finden
		// Notiz: Ganze OperationVariables verschicken
	});
}

SubmodelElement * httpHandler::getSubmodelElementByPathList(httpHandler::pathList_t & pathList, Submodel & sm)
{
	if (pathList.empty())
		return nullptr;

	auto path = pathList.cbegin();

	// Get first element from submodel
	auto element = sm.getSubmodelElements().get(*path);
	if (element == nullptr)
		return nullptr;

	for(path++;path != pathList.end(); ++path)
	{
		if (element->get_model_type() != ModelTypes::SubmodelElementCollection)
			return nullptr;

		auto collection = static_cast<SubmodelElementCollection*>(element);
		element = collection->get(*path);

		if (element == nullptr)
			return nullptr;
	}

	return element;
};

httpHandler::httpHandler(std::string ip, uint16_t port) : ip(ip), port(port) {}

Submodel * httpHandler::getSubmodel(util::string_view idShort) {
	submodelMutex.lock();
	auto iter = submodels.find(idShort.to_string());
	submodelMutex.unlock();
	if (iter != submodels.end())
		return iter->second;
	return nullptr;
}

bool httpHandler::submodelExists(Submodel &submodel) {
	return submodelExists(submodel.getIdShort());
}

bool httpHandler::submodelExists(util::string_view idShort) {
	if (getSubmodel(idShort) != nullptr)
		return true;
	return false;
}

ERROR_CODES httpHandler::addSubmodelToServer(Submodel &submodel) {
	bool ret = submodelExists(submodel);
	if (ret)
		return ERROR_CODES::ERR_ALREADY_EXISTS;

	submodelMutex.lock();
	auto result = submodels.emplace(submodel.getIdShort().to_string(), &submodel);
	submodelMutex.unlock();
	if (result.second)
		return ERROR_CODES::ERR_OK;
	else
		return ERROR_CODES::ERR_ALREADY_EXISTS;
}

ERROR_CODES httpHandler::removeSubmodelFromServer(Submodel & submodel) 
{
	if (!submodelExists(submodel))
		return ERROR_CODES::ERR_DOES_NOT_EXIST;

	submodelMutex.lock();
	auto iter = submodels.find(submodel.getIdShort().to_string());
	submodels.erase(iter);
	submodelMutex.unlock();
	return ERROR_CODES::ERR_OK;
}

ERROR_CODES httpHandler::listen() {
	spdlog::info("Starting server on {}:{}", ip, port);
	bool ret = server.bind_to_port(ip.c_str(), port);
	if (!ret)
		return ERROR_CODES::ERR_PORT_UNAVAILABLE;
	server.listen_after_bind();
	return ERROR_CODES::ERR_OK;
}

void httpHandler::run() {
	handleRequests();
	listen();
}

void httpHandler::stop() {
	server.stop();
}
