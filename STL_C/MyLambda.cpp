#include <iostream>
#include <functional>

using namespace std;

class PanelInfo
{
    public:
        PanelInfo(int c1, float c2):a(c1),b(c2){};
        void getPanel(std::function<void(int t1, float t2)> fn);
    protected:

    private:
        int a;
        float b;

};

void PanelInfo::getPanel(std::function<void(int t1, float t2)> fn)
{
    fn(a,b);
}

class MyLambda
{
    public:
        void getPanelInfo();
        PanelInfo *pf;
        MyLambda(PanelInfo* a, int c1 = 0, float c2 = 0):pf(a){};
        void my_printf();
    protected:

    private:
        int lenth;
        float width;
};

void MyLambda::getPanelInfo()
{
    pf->getPanel([&](int b1,float b2)
        {
            lenth = b1;
            width = b2;
        });
}

void MyLambda::my_printf()
{
    cout << "lenth = " << lenth <<endl;
    cout << "width = " << width <<endl;
}

int main()
{
    PanelInfo cf(12, 23.56);

    MyLambda df(&cf);

    df.getPanelInfo();
    df.my_printf();

    return 0;
}
