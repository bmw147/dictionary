
#include "MyTask.h"
#include "BitMap.h"
#include "Dictionary.h"

#include <json/json.h>

namespace mysp
{

MyTask::MyTask(const string & queryWord, const TcpConnectionPtr & conn)
: _queryWord(queryWord)
, _conn(conn){
}

void MyTask::excute(){
	auto dict = getDict();
	auto index = getIndexTable();

	BitMap candidata(dict.size());

	for (char c : _queryWord){
		char s[2] = {c};
		auto container = index[s];
		for (int idx : container){
			candidata.setMap(idx);
		}
	}

	for (size_t idx = 0; idx != candidata.size(); ++idx){
		if (candidata.isSet(idx)){
			int dist = distance(dict[idx].first);
			if (dist <= 3){
				_resultQue.push(MyResult(
							dict[idx].first,
							dict[idx].second,
							dist));
			}
		}
	}

	response();
}

void MyTask::response(){
	Json::Value item;

	for (size_t i = 0; i != 6; ++i){
		if (_resultQue.size()){
			item[to_string(i)] = _resultQue.top()._word;
			_resultQue.pop();
		}else{
			break;
		}
	}

	string sendItem = item.toStyledString();

	_conn->sendInLoop(sendItem);
}

int MyTask::distance(const string & rhs){
	const auto size1 = _queryWord.size(), size2 = rhs.size();
	if (size1 == 0)
		return size2;
	if (size2 == 0)
		return size1;

	//ed[i][j]表示 word1[0]~word1[i-1]与word2[0]~word2[j-1]之间的最小编辑距离
	vector<vector<int>> ed(size1 + 1, vector<int>(size2 + 1, 0));

	// 初始化任意字符与空字符之间的编辑距离
	for (size_t i = 0; i != size1; ++i)
	{
		ed[i][0] = i;
	}
	for (size_t i = 0; i != size2; ++i)
	{
		ed[0][i] = i;
	}

	for (size_t i = 1; i != size1 + 1; ++i)
	{
		for (size_t j = 1; j != size2 + 1; ++j)
		{
			if (_queryWord[i - 1] == rhs[j - 1])
				ed[i][j] = ed[i - 1][j - 1];
			else
				// 将3种编辑结尾的方法都尝试，取最小的结果
				ed[i][j] = min(min(ed[i][j - 1] + 1, ed[i - 1][j] + 1), ed[i - 1][j - 1] + 1);
		}
	}
	return ed[size1][size2];
}

}
