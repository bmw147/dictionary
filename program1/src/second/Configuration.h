
#ifndef __MYSP_CONFIGURATION_H__
#define __MYSP_CONFIGURATION_H__

#include <unordered_map>
#include <string>
using namespace std;

namespace mysp
{

class Configuration{
	public:
		Configuration(const string &);
		string getConfig(const string &) const;

	private:
		void init(const string &);

	private:
		unordered_map<string, string> _conf;
};

}

#endif
