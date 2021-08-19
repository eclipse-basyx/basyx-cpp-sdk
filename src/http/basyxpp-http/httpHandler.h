#ifndef BASYX_CREST_HTTPHANDLER_H
#define BASYX_CREST_HTTPHANDLER_H

#include <basyxpp-http/httplib/httplib.h>

#include <basyx/submodel.h>

#include <util/string_view/string_view.hpp>

#include <string>
#include <unordered_map>
#include <mutex>

namespace basyx {
namespace CREST {

enum ERROR_CODES {
	ERR_OK = 1,
	ERR_NOP = 0,
	ERR_PORT_UNAVAILABLE = -1,
	ERR_ALREADY_EXISTS = -2,
	ERR_DOES_NOT_EXIST = -3,
};

#define TXT_PLAIN "text/plain"
#define TXT_JSON "application/json"

class httpHandler {
public:
	using pathList_t = std::vector<util::string_view>;
private:
	std::string ip;
	uint16_t port;
	httplib::Server server;

	std::unordered_map<std::string, basyx::Submodel*> submodels;
	std::mutex submodelMutex;

	void handleRequests();

	//pathList_t getBasyxPathElements(std::string path, basyx::Submodel &submodel);
	//basyx::Submodel * getSubmodelByPath(std::string path);
public:
	//pathList_t splitString(std::string, std::string delimiter);
	pathList_t splitPath(util::string_view path, char delimiter);
	//object *getBasyxObjectByVectorizedPath(std::vector<std::string> *vec,
	//      object *obj);

	//std::shared_ptr<basyx::object> getBasyxObjectByVectorizedPath(std::vector<std::string> *vec, std::shared_ptr<basyx::object> objectPointer);

	//SubmodelElement * getSubmodelElementByPathList(const pathList_t2 & pathList, Submodel & sm);

	SubmodelElement * getSubmodelElementByPathList(pathList_t & pathList, Submodel & sm);
public:
	httpHandler(std::string ip, uint16_t port);
	~httpHandler() = default;
public:
	Submodel * getSubmodel(util::string_view idShort);

	bool submodelExists(Submodel & submodel);
	bool submodelExists(util::string_view idShort);

	ERROR_CODES addSubmodelToServer(Submodel & submodel);
	ERROR_CODES removeSubmodelFromServer(Submodel & submodel);

	ERROR_CODES listen();

	void run();
	void stop();
};

}
}



#endif // BASYX_CREST_HTTPHANDLER_H
