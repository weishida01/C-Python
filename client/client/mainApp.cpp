#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
	//    3. 调用动态链接 ImpDll
	HINSTANCE Hp = ::LoadLibrary("impdll.dll");
	if (Hp == NULL)
	{
		cout << "Error" << endl;
		system("pause");
		return 1;
	}


	int(*pF1)();
	pF1 = (int(*)())::GetProcAddress(Hp, "py");
	if (pF1 == NULL)
	{
		cout << "Error at calling" << endl;
		return 2;
	}

	pF1();

	//    8. 释放链接  ::FreeLibrary(Hp);
	::FreeLibrary(Hp);

	system("pause");
	return 0;
}
