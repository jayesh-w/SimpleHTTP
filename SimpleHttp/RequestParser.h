#pragma once
#include "IRequestParser.h"
#include <string>
#include <vector>

class RequestParser : public IParseRequest {
private:
	std::vector<std::string> split_str(std::string const& str, const char delim);
	void setRequestType(std::string);
	void setRequestPath(std::string);
	void setRequestHTMLVersion(std::string);
	void setRequestHost(std::string);
	void setRequestUserAgent(std::string);
	void setRequestAccept(std::string);
public:
	RequestParser(std::string);
	std::string getPath();
	std::string getRequestType();
	

};