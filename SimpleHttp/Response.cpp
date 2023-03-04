#include "Response.h"
#include <string>
#include "FileManager.h"

Response::Response() {
	
	fileManager = new FileManager(".");
}


//HTTP/1.1 200 OK\nContent-Type:text/html
std::string Response::generate_header() {
	std::string header = "";
	header = header + "HTTP/1.1";
	header = header + " " + std::to_string(this->status_code) + " " + StatusCode.getMSG(this->status_code) + "\n";
	header = header + "Content-Type:" + this->type + "\n";
	return header;
}

std::string Response::fetchFile(std::string FileName) {
	if (fileManager->checkFileExist(FileName)) {
		return fileManager->getFileContent(FileName);
	}
	return "err"; // here we need to implement try catch 
}

std::string Response::getContentType(std::string fileExtension) {
	return ResponseType.getResponseType(fileExtension);
}

std::string Response::getResponse(std::string path) {
	std::string response;
	std::string filecontent = this->fetchFile(path);
	if (filecontent != "err") {
		std::string fileExtension = fileManager->getFileExtesion(path);
		this->type = getContentType(fileExtension);
		this->status_code = 200;
		std::string header = generate_header();
		int fileSize = fileManager->getFileLength();
		header = header + "Content-Length: " + std::to_string(fileSize) + "\n\n";
		response = header + filecontent;
	}
	else {
		this->type = "text/html";
		this->status_code = 404;
		std::string header = generate_header();
		header = header + "\n\n";
		response = header;
	}
	return response;

}