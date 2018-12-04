
#include "DictProducer.h"
#include "Mylogger.h"
#include "Configuration.h"

#include <fstream>
#include <sstream>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

namespace dict
{

DictProducer::DictProducer()
: _splitTool(NULL){
	_dir = getConfig("enDictionaryDir");
	if (_dir.size() == 0){
		LogError("No dictionary source file");
		exit(EXIT_FAILURE);
	}
}

DictProducer::DictProducer(SplitTool * splitTool)
: _splitTool(splitTool){
	_dir = getConfig("cnDictionaryDir");
	if (_dir.size() == 0){
		LogError("No dictionary directory");
		exit(EXIT_FAILURE);
	}
}

void DictProducer::buildDict(){
	getFiles();
	std::ifstream input;
	
	std::string line, word;
	for (const auto & file : _files){
		input.open(file);
		if (input){
			LogInfo("Open dictionary file \"%s\" success", file.c_str());
			while (getline(input, line)){
				strProcess(line);

				istringstream ss(line);
				while (ss >> word){
					_dict[word]++;
				}
			}
		}else {
			LogError("Open dictionary file \"%s\"failed", file.c_str());
		}
		input.close();
	}
	LogInfo("Build dict.dat success");
}

//中文
void DictProducer::buildCnDict(){
	;
}

void DictProducer::getFiles(){
	DIR * dir = opendir(_dir.c_str());
	if (!dir){
		LogError("No such dirctory");
	}
	struct dirent * fileInfo;
	string file;
	
	while ((fileInfo = readdir(dir)) != NULL){
		if (fileInfo->d_type == DT_REG){
			file = _dir + "/" + fileInfo->d_name;
			_files.push_back(file);
			LogDebug("add \"%s\" to dictionary files", file.c_str());
		}
	}

}

void DictProducer::buildIndex(){
	size_t idx = 0;
	for (const auto & record : _dict){
		for (const auto & c : record.first){
			char s[2] = {c};
			auto it = _index.find(s);
			if (it == _index.end()){
				_index.insert(std::make_pair(string(s), set<size_t>{idx}));
			}else {
				it->second.insert(idx);
			}
		}
		++idx;
	}
	LogInfo("Create index.dat success");
}

void DictProducer::store() const{
	std::string file = getConfig("dictionaryStoreFile");
	if (file.size() == 0){
		LogError("No dictionary store file");
		exit(EXIT_FAILURE);
	}

	ofstream output(file);
	for (const auto & record : _dict){
		output << record.first << "  "
			   << record.second << '\n';
	}
	output.close();

	file = getConfig("indexStoreFile");
	if (file.size() == 0){
		LogError("No index store file");
		exit(EXIT_FAILURE);
	}

	output.open(file);
	for (const auto & record : _index){
		output << record.first << ":";
		for (const auto & i : record.second){
			output << ' ' << i;
		}
		output << '\n';
	}
	output.close();
}

void DictProducer::strProcess(string & str){
	for (auto & c : str){
		if (!isalpha(c)){
			c = ' ';
		}else{
			c = tolower(c);
		}
	}
}


}
