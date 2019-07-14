#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <iostream>

using namespace std;

class Singleton
{
    public:        
        static Singleton* getInstance();

    protected:
    
    private:
        class Creleaseptr
        {
            public:
                ~Creleaseptr()
                {
                    if(Singleton::instance)
                    {
                        delete Singleton::instance;
                        Singleton::instance = nullptr;
                    }
                }
        };
        static Creleaseptr res;
        static Singleton *instance;
        Singleton();
        ~Singleton();
};

#endif