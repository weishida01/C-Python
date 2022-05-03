#include <windows.h>
#include<Python.h>
#include<iostream>
#include <stdlib.h>
using namespace std;

BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	return TRUE;
}


extern "C" __declspec(dllexport) int py()
{
	//1、引入解释器环境 初始化
	//Py_SetPythonHome((wchar_t*)L"D:/Anaconda3/envs/pytorch");   //导入python解释器
	Py_SetPythonHome(L"D:/Anaconda3");   //导入python解释器
	Py_Initialize();                       //初始化Python环境
	if (!Py_IsInitialized())
	{
		cout << "初始化失败！" << endl;
		return 0;
	}
	cout << "Python初始化成功" << endl;

	//3、引入python代码文件
	PyObject * pModule = PyImport_ImportModule("infer");  //导入py文件 
	if (!pModule)
	{
		cout << "调用的Python代码文件没找到" << endl;
		return 0;
	}
	cout << "成功调用的Python代码文件!" << endl;

	//4、引入python代码中的函数
	PyObject * pFunc = NULL;                                                        // 定义引入函数 
	pFunc = PyObject_GetAttrString(pModule, "pp");                //调用的函数名为 pp
	PyObject * pRet = PyObject_CallObject(pFunc, NULL);        //调用函数 得到返回值

	int res = 0;
	PyArg_Parse(pRet, "i", &res);                                                //转换返回类型

	//5、终结python环境
	Py_Finalize();                 //反初始化，结束时调用

	return res;

}