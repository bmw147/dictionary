
#include "Configuration.h"
#include "Mylogger.h"
#include "DictProducer.h"
#include <iostream>
using std::cout;
using std::endl;

int main(void){
	cout << dict::getConfig("dictionarySourceFile") << endl;
	dict::DictProducer dict;
	dict.buildDict();
	dict.buildIndex();
	dict.store();

	return 0;
}
