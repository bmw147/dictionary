
#ifndef __DICT_SPLITTOOL_H__
#define __DICT_SPLITTOOL_H__

#include <vector>
#include <string>

namespace dict
{

class SplitTool{
	public:
		virtual ~SplitTool(){}
		virtual std::vector<std::string> cut(const std::string &) = 0;
};

}

#endif
