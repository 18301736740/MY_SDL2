#include <iostream>
#include <dlfcn.h>

#include "operation.h"
#include "operationfactory.h"

using namespace std;

int main(int argc,char *argv[])
{
    Operation *oper = nullptr;
    
    OperationFactory *(*pTestDLObj)(void);
    dlerror();
 
    void *lib_dl = dlopen("./libtest.so",RTLD_LAZY | RTLD_GLOBAL | RTLD_NODELETE);
    if(NULL == lib_dl)
    {
        printf("load library libtdlc.so error.\nErrmsg:%s\n",dlerror());
        return -1;
    }
    pTestDLObj = (OperationFactory *(*)(void))dlsym(lib_dl,"GetIns");
    const char *dlmsg = dlerror();
    if(NULL != dlmsg)
    {
        printf("get class testdl error\nErrmsg:%s\n",dlmsg);
        dlclose(lib_dl);
        return -1;
    }
    
    OperationFactory  *fac = (*pTestDLObj)();
    oper = fac->createOperate("+");
    oper->numberA = 6;
    oper->numberB = 5;
    cout<<"结果是:"<<oper->getResult()<<endl;
    delete oper;
    oper = nullptr;
    
    int a;
    a = add(12,12);
    
    cout<<"a = "<<a<<endl;
    return 0;
}