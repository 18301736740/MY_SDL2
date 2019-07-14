#ifndef _OPERATIONFACTORY_H_
#define _OPERATIONFACTORY_H_
#include "operation.h"
#include <string>

using namespace std;

int add(int a,int b)
{
    return a+b;
}

class OperationFactory
{
    public:
        Operation* createOperate (const string opt);
    protected:
    
    private:
};

extern "C" OperationFactory* GetIns()
{
    return new OperationFactory;
}

#endif