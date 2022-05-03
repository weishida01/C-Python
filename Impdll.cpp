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
	//1��������������� ��ʼ��
	//Py_SetPythonHome((wchar_t*)L"D:/Anaconda3/envs/pytorch");   //����python������
	Py_SetPythonHome(L"D:/Anaconda3");   //����python������
	Py_Initialize();                       //��ʼ��Python����
	if (!Py_IsInitialized())
	{
		cout << "��ʼ��ʧ�ܣ�" << endl;
		return 0;
	}
	cout << "Python��ʼ���ɹ�" << endl;

	//3������python�����ļ�
	PyObject * pModule = PyImport_ImportModule("infer");  //����py�ļ� 
	if (!pModule)
	{
		cout << "���õ�Python�����ļ�û�ҵ�" << endl;
		return 0;
	}
	cout << "�ɹ����õ�Python�����ļ�!" << endl;

	//4������python�����еĺ���
	PyObject * pFunc = NULL;                                                        // �������뺯�� 
	pFunc = PyObject_GetAttrString(pModule, "pp");                //���õĺ�����Ϊ pp
	PyObject * pRet = PyObject_CallObject(pFunc, NULL);        //���ú��� �õ�����ֵ

	int res = 0;
	PyArg_Parse(pRet, "i", &res);                                                //ת����������

	//5���ս�python����
	Py_Finalize();                 //����ʼ��������ʱ����

	return res;

}