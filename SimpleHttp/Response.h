#pragma once
#include<string>
#include "FileManager.h"

struct {
public:
	std::string HTML = "text/html";
	std::string CSS = "text/css";
	std::string JS = "text/js";
	std::string byDefault = "text/plain";
	std::string getResponseType(std::string ext) {
		if (ext == "html")
			return HTML;
		if (ext == "css")
			return CSS;
		if (ext == "js")
			return JS;
		return byDefault;

	}
} ResponseType;

struct  {
	int OK = 200;
	int NOTFOUND = 404;
	int ERRORM = 500;
	int REDIRECTED = 300;
	std::string OK_STR = "OK";
	std::string NOTFOUND_STR = "NOTFOUND";
	std::string ERROR_STR = "ERR";
	std::string REDIRECTED_STR = "REDIRECT";
	std::string getMSG(int code) {
		switch (code) {
		case 200:
			return OK_STR;
			break;
		case 404:
			return NOTFOUND_STR;
			break;
		case 500:
			return ERROR_STR;
			break;
		case 300:
			return REDIRECTED_STR;
			break;

		}
	}
	
} StatusCode;

class Response {
private:
	std::string type;
	int status_code;
	std::string response_header;
	std::string response_content;
	int content_length;
	std::string response_message;
	std::string generate_header();
	FileManager *fileManager;

public: 
	Response(); 
	std::string fetchFile(std::string FileName);
	std::string getContentType(std::string fileExtension);
	std::string getResponse(std::string path);

};