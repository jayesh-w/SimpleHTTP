#include "RequestParser.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>


	std::vector<std::string> RequestParser::split_str(std::string const& str, const char delim) {
		std::vector <std::string> out;
		// create a stream from the string  
		std::stringstream s(str);

		std::string s2;
		while (std::getline(s, s2, delim))
		{
			out.push_back(s2); // store the string in s2  
		}
		return out;
	}

	void RequestParser::setRequestType(std::string req) {
		// req looks like this GET PATH HTML
		std::vector<std::string> temp_split = split_str(req, ' ');
		this->request_type = temp_split[0];
	}

	void RequestParser::setRequestPath(std::string req){
		// req looks like this GET PATH HTML 
		// here we need more filtering because of query parameters
		std::vector<std::string> temp_split = split_str(req, ' ');
		this->request_path = temp_split[1];
	}

	void RequestParser::setRequestHTMLVersion(std::string req){
		std::vector<std::string> temp_split = split_str(req, ' ');
		this->html_version = temp_split[2];
	}

	void RequestParser::setRequestHost(std::string req){
		std::vector<std::string> temp_split = split_str(req, ' ');
		this->host = temp_split[1];
	}

	void RequestParser::setRequestUserAgent(std::string req){
		std::vector<std::string> temp_split = split_str(req, ': ');
		this->user_agent = temp_split[1];
	}

	void RequestParser::setRequestAccept(std::string req){
		std::vector<std::string> temp_split = split_str(req, ': ');
		this->accept = temp_split[1];
	}
	
	RequestParser::RequestParser(std::string request) {
		// TODO: the Request String we need to break down and set all the variables
		std::vector<std::string> temp_request = split_str(request, '\n');
		int RequestDetails = 0, RequestHost = 1, RequestUserAgent = 8, RequestAccept=9;
		setRequestType(temp_request[RequestDetails]);
		setRequestPath(temp_request[RequestDetails]);
		setRequestHTMLVersion(temp_request[RequestDetails]);
		/*setRequestHost(temp_request[RequestHost]);
		setRequestUserAgent(temp_request[RequestUserAgent]);
		setRequestAccept(temp_request[RequestAccept]);*/
		
		
	}
	std::string RequestParser::getPath() {
		// TODO: Return the Path
		return this->request_path;
	}
	std::string RequestParser::getRequestType() {
		// TODO : Return the RequestType :: GET, POST, PUT, PATCH ... etc
		return this->request_type;
	}
