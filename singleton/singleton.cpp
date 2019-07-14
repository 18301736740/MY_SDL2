#include "singleton.h"
#include <iostream>

using namespace std;

Singleton* Singleton::instance = nullptr;
Singleton::Creleaseptr Singleton::res;
Singleton::Singleton()
{
    cout<<"构造函数"<<endl;
}

Singleton::~Singleton()
{
    cout<<"析构函数释放instance对象"<<endl;
}

Singleton* Singleton::getInstance()
{
    cout<<"进入getInstance"<<endl;
    if(instance == nullptr)
    {
        instance = new Singleton;
    }
    return instance;
}