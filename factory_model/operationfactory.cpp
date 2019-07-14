#include "operationfactory.h"
#include "operationadd.h"
#include "operationsub.h"
#include "operationdvi.h"
#include "operationmul.h"
#include <string.h>
#include <iostream>

using namespace std;

Operation* OperationFactory::createOperate(const string opt)
{
    Operation *oper = nullptr;
    string swi = opt;
    char calc = 0;
    strcpy(&calc,swi.c_str());
    switch(calc)
    {
        case '+':
            oper = new OperationAdd;
            break;
        case '-':
            oper = new OperationSub;
            break;
        case '*':
            oper = new OperationMul;
            break;
        case '/':
            oper = new OperationDvi;
            break;
        default:
            cout<<"你所进行的计算我们暂时还没有:"<<endl;
    }
    return oper;
}