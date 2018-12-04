
#ifndef __DICT_DICTPRODUCCER_H__
#define __DICT_DICTPRODUCCER_H__

#include "SplitTool.h"

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

namespace dict
{

class Configuration;

class DictProducer{
	public:
		DictProducer();
		DictProducer(SplitTool * splitTool);
		void buildDict();
		void buildCnDict();
		void buildIndex();
		void store() const;

	private:
		void getFiles();
		void push_dict(const std::string &);	
		void strProcess(std::string & );		//大写转小写

	private:
		std::string _dir;
		std::vector<std::string> _files;
		SplitTool * _splitTool;
		std::unordered_map<std::string, size_t> _dict;
		std::unordered_map<std::string, std::set<size_t>> _index;
};

}

#endif
