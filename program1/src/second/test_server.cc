
#include "SpellcorrectServer.h"
#include "Configuration.h"
#include "Dictionary.h"

#include <iostream>

using namespace std;
using namespace mysp;


int main(int argc, char const *argv[])
{

	Dictionary::getInstance()->initDict("../../data/dat/en/dict.dat");
	Dictionary::getInstance()->initIndex("../../data/dat/en/index.dat");

	cout << (getDict().begin())->first << endl;
	Configuration conf("../../conf/server.conf");
	SpellcorrectServer server(conf);
	server.start();
	return 0;
}
