#include <iostream>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
#include <string.h>
#include <stack>
#include <queue>
#include <map>

//#define First
//#define STLQ

using namespace std;

typedef struct my_node {
	int a;
	char cmd[3];
}node;

class StlC
{
	public:
		void stlTraverse();
		void stlStruct();
		void stlSet();
		void stlStack();
		void stlQueue();
		void stlMap();
	protected:

	private:
	
};

static bool des(const int& a, const int& b)
{
	return a > b;	
}

static bool lec(const node& spe, const node& spc)
{
	return spe.a < spc.a;
}

struct Info
{
	string name;
	double score;

#ifdef First // 两种使set
	bool operator < (const Info& a)const // 升序,priority_queue排序的方式,运算符重载<
	{
		return a.score > this->score;
	}
};

void StlC::stlSet()
{
	set<Info> s;
#else
};

class cmp
{
	public:
		bool operator () (const Info& a, const Info& b)const // 降序,重写仿函数
		{
			return a.score > b.score;
		}
};

void StlC::stlSet()
{
	set<Info,cmp> s;
#endif
	Info inf;

	inf.name = "abc";
	inf.score = 123.3;
	s.insert(inf);

	inf.name = "DEF";
	inf.score = -23.53;
	s.insert(inf);

	inf.name = "xyz";
	inf.score = 73.3;
	s.insert(inf);

	for(set<Info>::iterator it = s.begin(); it != s.end(); ++it)
	{
		cout << it->name << ":" << it->score << endl;
	}

	for(set<Info>::reverse_iterator it = s.rbegin(); it != s.rend(); ++it)
	{
		cout << (*it).name << ":"<< (*it).score << endl;
	}
}

void StlC::stlMap()
{
	map<int, string> mapStudent;

    //第一种插入方式
	mapStudent.insert(pair<int, string>(000, "student_zero"));

    //第二种插入方式
	mapStudent.insert(map<int, string>::value_type(001, "student_one"));

    //第三种插入方式
	mapStudent[123] = "student_first";
	mapStudent[456] = "student_second";

    //创建Insert_Pair,检测是否成功插入
	pair<map<int, string>::iterator, bool> Insert_Pair;
	
	Insert_Pair = mapStudent.insert(map<int, string>::value_type (001, "student_two"));

    //因为都是001,所以没有成功插入
	if(!Insert_Pair.second)
    	cout << "Error insert new element" << endl;	
}

#ifdef STLQ
void StlC::stlQueue()
{
	queue<Info> qe;
#endif

#ifdef First
void StlC::stlQueue()
{
	priority_queue<Info> qe;
#else
void StlC::stlQueue()
{
	priority_queue<Info, vector<Info>, cmp> qe;
#endif
	Info inf;

	inf.name = "abc";
	inf.score = 123.3;
	qe.push(inf);

	inf.name = "DEF";
	inf.score = -23.53;
	qe.push(inf);

	inf.name = "xyz";
	inf.score = 73.3;
	qe.push(inf);	

	cout << qe.size() << endl;

	while(!qe.empty())
	{
#ifdef STLQ
		cout << qe.front().name << ":" << qe.front().score << endl;
#else
		cout << qe.top().name << ":" << qe.top().score << endl;
#endif
		qe.pop();
	}
}

void StlC::stlStack()
{
	stack<Info> st;
	Info inf;

	inf.name = "abc";
	inf.score = 123.3;
	st.push(inf);

	inf.name = "DEF";
	inf.score = -23.53;
	st.push(inf);

	inf.name = "xyz";
	inf.score = 73.3;
	st.push(inf);

	cout << st.size() << endl;

	while(!st.empty())
	{
		cout << st.top().name << ":" << st.top().score << endl;
		st.pop();
	}
}

// a b c d e f g h i j k l m n o p q r s t u v w x y z
void StlC::stlStruct()
{
	vector<node> v(6);
	
	v[0].a = 5;
	strcpy(v[0].cmd, "mno");

	v[1].a = 6;
	strcpy(v[1].cmd, "pqr");

	v[2].a = 4;
	strcpy(v[2].cmd, "jkl");

	v[3].a = 2;
	strcpy(v[3].cmd, "def");

	v[4].a = 3;
	strcpy(v[4].cmd, "ghi");
	
	v[5].a = 1;
	strcpy(v[5].cmd, "abc");

    sort(v.begin(), v.end(), lec);

    for(node& i : v)
    	cout << i.cmd << " ";
    cout << endl;

    node nd;
    nd.a = 7;
    strcpy(nd.cmd, "stu");
    
    v.push_back(nd);

    for(auto& i : v)
    	cout << i.cmd << " ";
    cout << endl;
}

void StlC::stlTraverse()
{
	vector<int> v {5, 7, 9, 6, 2, 3, 1};

	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;

    // 求和 numeric
	cout << accumulate(v.begin(), v.end(), 0) << endl;

	// 数组转置 algorithm
	reverse(v.begin(), v.end());
	
	for(auto&& i : v)
		cout << i << " ";
	cout << endl;

	// 动态数组
	v.push_back(66); // 向vector数组尾部插入66 相当于v[0] = 66
	v.push_back(88); // 尾部插入88  相当于v[1] = 88
	v.insert(v.begin(), 99); //在第一个元素之前插入99
	v.insert(v.end(), 16); // 在最后一个元素之后插入16
	v.insert(v.begin()+1, 18); //在第二个元素之前插入18
	v.insert(v.end()-1, 19); // 在倒数第二个元素之后插入19

	v.erase(v.begin()); // 删除用法 同insert 表示删除第一个元素
	//v.erase(v.begin(), v.begin()+5); // 删除开头第1-5的元素

	for(vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		cout << *it << " ";
	cout << endl;

	// 升序排序 algorithm
	sort(v.begin(), v.end());

	for(auto&& i : v)
		cout << i << " ";
	cout << endl;

	// 降序排序 algorithm
	sort(v.begin(), v.end(), des);

	for(auto&& i : v)
		cout << i << " ";
	cout << endl;	

}

int main(int argc, char* argv[])
{
	StlC stl;
	// 迭代器遍历vector容器
	stl.stlTraverse();

	// vector元素为结构体类型时的升序排列
	stl.stlStruct();

	// set集合的排序使用
	stl.stlSet();

	// stack栈的使用
	stl.stlStack();

	// queue队列的使用
	stl.stlQueue();

	// Map键值对的使用
	stl.stlMap();
	return 0;
}