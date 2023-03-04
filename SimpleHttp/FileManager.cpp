
#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>


std::vector<std::string> FileManager::split_str(std::string const& str, const char delim) {
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

std::string FileManager::ParseFilePaths(std::filesystem::path p1) {
	std::string path = p1.string();
	std::string corrected_path = "/";
	std::vector<std::string> splitted_path = split_str(path, '\\');
	std::string forwardSlash = "/";
	for (int i = 1; i < splitted_path.size() - 1; i++)
		corrected_path = corrected_path + splitted_path[i] + forwardSlash;
	corrected_path = corrected_path + splitted_path[splitted_path.size() - 1];
	return corrected_path;
		
}

FileManager::FileManager(std::string currect_working_dir) {
	this->fileLength = 0;
	// generate all the filepath and store it in the map
	for (std::filesystem::recursive_directory_iterator i("."), end; i != end; ++i) {
		//std::cout << ParseFilePaths(i->path()) << std::endl;
		this->filemapper[ParseFilePaths(i->path())] = i->path();
	}

}

std::string FileManager::getFileContent(std::string fileName) {
	std::string fileContent = "", temp;
	std::ifstream myFileStream;
	myFileStream.open(filemapper[fileName]);
	if (myFileStream.is_open()) {
		while (std::getline(myFileStream, temp)) {
			fileContent = fileContent + temp + "\n";
		}
		myFileStream.close();
	}
	this->fileLength = fileContent.size();
	return fileContent;
}

int FileManager::getFileLength() {
	return this->fileLength;
}

bool FileManager::checkFileExist(std::string fileName) {
	if (filemapper.find(fileName) == filemapper.end()) {
		// file Not found 
		return false;
	}
	return true;
}

std::string FileManager::getFileExtesion(std::string filename) {
	std::vector<std::string> file = split_str(filename, '.');
	return file[file.size() - 1];
}

