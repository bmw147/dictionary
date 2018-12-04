
#include "Configuration.h"
#include "Mylogger.h"

#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>
#include <fstream>

namespace mysp
{

Configuration::Configuration(const string & file){
	init(file);
}

void Configuration::init(const string & file){
	std::ifstream input(file);

	if (!input){
		LogError("Open config file \"%s\" failed", file.c_str());
		exit(EXIT_FAILURE);
	}else{
		LogInfo("Open config file \"%s\" success", file.c_str());
	}

	std::string line;
	std::vector<string> vec;
	while (getline(input, line)){
		boost::split(vec, line, boost::is_any_of(" \t,:"), boost::token_compress_on);
		_conf.emplace(vec[0], vec[1]);
	}

	input.close();
}

string Configuration::getConfig(const string & word) const{
   auto cit = _conf.find(word);
   if (cit == _conf.end()){
   	return string();
   }
   
   return cit->second; 
}

}
