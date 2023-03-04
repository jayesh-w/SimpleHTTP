#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <filesystem>




class FileManager {
private:
	std::map<std::filesystem::path, std::filesystem::path> filemapper;
	std::string current_working_dir;
	int fileLength;
public:
	FileManager(std::string current_working_dir = ".");
	// here filename is the path from the request
	std::string getFileContent(std::string fileName);
	int getFileLength();
	bool checkFileExist(std::string fileName);
	std::vector<std::string> split_str(std::string const& str, const char delim);

	std::string ParseFilePaths(std::filesystem::path);
	std::string getFileExtesion(std::string path);

 };