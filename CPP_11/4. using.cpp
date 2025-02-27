#include <iostream>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// using

typedef vector<int>::iterator Veclt;

typedef __int64 id;
using id2 = int; // id2가 int 형이다?

// 1) 직관성
typedef void (*MyFunc)();
using MyFunc2 = void(*)();

// 2) 템플릿
template<typename T>
using List = std::list<T>;

template<typename T>
struct List2
{
	typedef std::list<T> type;
};

int main()
{
	id playerId = 0;

	List<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);

	List2<int>::type li2;

	return 0;
}