#include <string>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

//static const char *twoDecoderAPK[] = {"tver","alja","youtube","netflix","senwei"};
static const std::vector<std::string> twoDecoderAPK = 
{
    "tver",
    "alja",
    "youtube",
    "netflix",
    "senwei",
    "apk"
};

class StringC
{
	private:
		
	public:
		void stringConstructor()const;
		void stringFeature()const;
		void stringFind()const;
        bool IsTwoAPKFlow(const char *name)const;
		
	protected:
	
};

bool StringC::IsTwoAPKFlow(const char *name)const
{
    string apk(name);
    for(auto && i : twoDecoderAPK)
    {
        if(apk.find(i) != string::npos)
//*****************************************
//        const char * c_i = i.c_str();
//        if(strstr(name,c_i) != NULL)
//*****************************************
//        if(strstr(name,i) != NULL)
            return true;
    }
    return false;
}


/*
* size_type find( const basic_string &str, size_type index );            // 返回str在字符串中第一次出现的位置（从index开始查找），如果没找到则返回string::npos
* size_type find( const char *str, size_type index );                    // 同上
* size_type find( const char *str, size_type index, size_type length );  // 返回str在字符串中第一次出现的位置（从index开始查找，长度为length），如果没找到就返回string::npos
* size_type find( char ch, size_type index );                            // 返回字符ch在字符串中第一次出现的位置（从index开始查找），如果没找到就返回string::npos
*
* find_first_of() 函数可实现在源串中搜索某字符串的功能，该函数的返回值是被搜索字符串的第 1 个字符第 1 次出现的下标（位置）。若查找失败，则返回 npos。
* find_last_of()  函数同样可实现在源串中搜索某字符串的功能。与 find_first_of() 函数所不同的是，该函数的返回值是被搜索字符串的最后 1 个字符的下标（位置）。若查找失败，则返回 npos。
* size_type find_first_not_of (value_type_Ch, size_type_Off = 0) const; size_type find_first_of (const value_type* _Ptr, size_type _Off = 0) const;
* size_type find_first_of (const value_type* _Ptr, size_type_Off, size_type_Count) const;
* size_type find_first_of (const basic_string & _Str, size_type_Off = 0) const;
* size_type find_last_of (value_type _Ch, size_type_Off = npos) const;
* size_type find_last_of (const value_type* _Ptr, size_type_Off = npos) const;
* size_type find_last_of (const value_type* _Ptr, size_type _Off, size_type _Count) const;
* size_type find_last_of (const basic_string& _Str, size_type_Off = npos) const;
*
* find_first_not_of() 函数可实现在源字符串中搜索与指定字符（串）不相等的第 1 个字符；find_last_not_of() 函数可实现在源字符串中搜索与指定字符（串）不相等的最后 1 个字符。
* size_type find_first_not_of (value_type _Ch, size_type_Off = 0) const;
* size_type find_first_not_of (const value_type * _Ptr, size_type_Off = 0) const;
* size_type find_first_not_of (const value_type* _Ptr, size_type_Off, size_type_Count) const;
* size_type find_first_not_of (const basic_string & _Str, size_type_Off = 0) const;
* 注意：查找字符串a是否包含子串b,不是用 strA.find(strB) > 0 而是 strA.find(strB) != string:npos
* rfind() 函数的原型和find()函数的原型类似，参数情况也类似。只不过 rfind() 函数适用于实现逆向查找。
*/

void StringC::stringFind()const
{
	string s = "study hard and make progress everyday.";
	cout<<"the word is at index(rfind) "<<s.rfind("make",10)<<endl;
	cout<<"the word is at index(rfind) "<<s.rfind("make")<<endl;
	cout<<"the word is at index(find) "<<s.find("make",10)<<endl;
	cout<<"find_first_of index "<<s.find_first_of("make")<<endl;
	cout<<"find_last_of index " <<s.find_last_of("make")<<endl;
	cout<<"find_first_of index "<<s.find_first_not_of("make")<<endl;
	cout<<"find_first_of index "<<s.find_first_not_of("make")<<endl;
	return;
}

/*
* int capacity()const;          //返回当前容量（即string中不必增加内存即可存放的元素个数）
* int max_size()const;          //返回string对象中可存放的最大字符串的长度
* int size()const;              //返回当前字符串的大小
* int length()const;            //返回当前字符串的长度
* bool empty()const;            //当前字符串是否为空
* void resize(int len,char c);  //把字符串当前大小置为len，多去少补，多出的字符c填充不足的部分
*/

void StringC::stringFeature()const
{
	string str;
	if(str.empty())
		cout<<"str is null"<<endl;
	else
		cout<<"str is not null"<<endl;

	str = str + "abcdef";
	if(str.empty())
		cout<<"str is null"<<endl;
	else
	{
		cout<<"str size"<<str.size()<<endl;
		cout<<"str length"<<str.length()<<endl;
		cout<<"str max_size"<<str.max_size()<<endl;
		cout<<"str capacity"<<str.capacity()<<endl;
		str.resize(20,'\0');
		cout<<"str resize 20"<<str<<endl;
	}

	return;
}


/*
*string strs                     //生成空字符串
*string s(str)                   //生成字符串str的复制品
*string s(str, stridx)           //将字符串str中始于stridx的部分作为构造函数的初值
*string s(str, strbegin, strlen) //将字符串str中始于strbegin、长度为strlen的部分作为字符串初值
*string s(cstr)                  //以C_string类型cstr作为字符串s的初值
*string s(cstr,char_len)         //以C_string类型cstr的前char_len个字符串作为字符串s的初值
*string s(num, c)                //生成一个字符串，包含num个c字符
*string s(strs, beg, end)        //以区间[beg, end]内的字符作为字符串s的初值
*/
void StringC::stringConstructor()const
{
	string str;
	//str = "苦心人天不负，卧薪尝胆三千越甲可吞吴";
	//char *c_str = "有志者事竟成，破釜沉舟百二秦关终属楚";
	str = "hello world，my name is gavin.";
	char *c_str = "life is very much like a millor";

	string s(str);
	string c_s(c_str);

	cout<< s <<endl;
	cout<< c_s <<endl;

	string s0(str, 3, 5);
	string c_s0(str.begin(),str.end()-5);
	cout<< s0 <<endl;
	cout<<c_s0 <<endl;


//------------------------------
   // string str ("12345678");
   // char ch[ ] = "abcdefgh";
   // string a; //定义一个空字符串
   // string str_1 (str); //构造函数，全部复制
   // string str_2 (str, 2, 5); //构造函数，从字符串str的第2个元素开始，复制5个元素，赋值给str_2
   // string str_3 (ch, 5); //将字符串ch的前5个元素赋值给str_3
   // string str_4 (5,'X'); //将 5 个 'X' 组成的字符串 "XXXXX" 赋值给 str_4
   // string str_5 (str.begin(), str.end()); //复制字符串 str 的所有元素，并赋值给 str_5
   // cout << str << endl;
   // cout << a << endl ;
   // cout << str_1 << endl;
   // cout << str_2 << endl;
   // cout << str_3 << endl;
   // cout << str_4 << endl;
   // cout << str_5 << endl;

	return;
}

int main(int argc, char* argv[])
{
    char *name = "com.tcl.net.apk";
	//string 类构造函数demo
	StringC stc;
	//stc.stringConstructor();

	//string 类特性函数
	stc.stringFeature();

	// string 查找函数
	stc.stringFind();

    cout <<"istwo = "<< stc.IsTwoAPKFlow(name) << endl;
	return 0;
} 
