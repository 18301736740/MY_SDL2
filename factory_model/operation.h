#ifndef _OPERATION_H_
#define _OPERATION_H_

class Operation
{
    public:
        float numberA;
        float numberB;
        virtual float getResult() = 0;
        virtual ~Operation(){}
    protected:
        
    private:
    
};

#endif