#include <iostream>
#include <array>
#include <tuple>

using namespace std;

class ArrayC
{
	public:
		void arrayTraverse()const;
		void arraySize()const;
		void arrayAccess()const;
		void arraySwapFill()const;
		void arrayTuple()const;
	protected:

	private:
	
};

void ArrayC::arrayTuple()const
{
	array<int, 3> arr {66, 67, 68};

	tuple_element<0, decltype(arr)>::type myele;

	myele = get<2>(arr);
	get<2>(arr) = get<0>(arr);
	get<0>(arr) = myele;

	for(auto&& i : arr)
		cout<<i<<" ";
	cout<<endl;
}

void ArrayC::arraySwapFill()const
{
	array<int, 6> arr {9, 8, 7, 6, 5, 3};
	array<int, 6> arr1 {3, 5, 6, 7, 8, 9};

	arr.swap(arr1);

	for(auto&& i : arr)
		cout<<i<<" ";
	cout<<endl;
	
	arr.fill(6);

	for(auto&& i : arr)
		cout<<i<<" ";
	cout<<endl;
	
	return;
}

void ArrayC::arrayAccess()const
{
	array<int, 5> arr {4, 5, 6, 7, 8};

	cout<<"arr 1 "<<arr[1]<<endl;
	cout<<"arr 2 "<<arr.at(2)<<endl;
	cout<<"arr 0 "<<arr.front()<<endl;
	cout<<"arr 4 "<<arr.back()<<endl;
	cout<<"&arr "<<arr.data()<<endl;
}

void ArrayC::arraySize()const
{
	array<int, 5> arr {3, 4, 5, 6, 7};
	
	if(arr.empty())
		cout<<"arr is empty"<<endl;
	else
	{
		cout<<"arr is not empty"<<endl;
		cout<<"arr size "<<arr.size()<<endl;
		cout<<"arr max_size "<<arr.max_size()<<endl;
		cout<<"arr sizeof "<<sizeof(arr)<<endl;
	}
}

void ArrayC::arrayTraverse()const
{
	array<int, 5> arr {1, 2, 3, 4, 5};

	for(auto& i : arr)
		i = i + 1;

	for(auto&& i : arr)
		cout<<i<<" ";
	cout<<endl;

}

int main(int argc, char* argv[])
{
	// 遍历函数
	ArrayC AC;
	AC.arrayTraverse();

	// 大小函数
	AC.arraySize();
	
	// 访问函数
	AC.arrayAccess();

	// 覆盖交换函数
	AC.arraySwapFill();

	// 重写元函数
	AC.arrayTuple();
	
	return 0;
}