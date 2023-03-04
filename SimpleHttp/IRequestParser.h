#pragma once
#include <string>
class IParseRequest {
protected:
	std::string request_type;
	std::string request_path;
	std::string html_version;
	std::string host;
	std::string user_agent;
	std::string accept;

public:
	virtual std::string getPath() = 0;
	virtual std::string getRequestType() = 0;

};
