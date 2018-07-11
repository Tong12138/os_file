#include"stdafx.h"
#include <stdlib.h>
#include <stdio.h>

fileSystem MFS;
int memory_index;
char memory[SYSOPENFILE][BLOCKSIZE];
int CurD;
int NextFreeG;
int StackNum;
int UCount = 0;
string path;

void Initialize_dataBlock()  //��ʼ�����ݿ�
{
	for (int i = 0; i<BLOCKNUM; i++)
	{
		dataBlock temp;
		temp.next = -1;
		temp.used = 0;
		for (int j = 0; j<BLOCKSIZE + 1; j++)
		{
			temp.content[j] = '\0';//��ʱ����������Ϊ0
		}
		MFS.dataArea.push_back(temp);//��vectorβ����������
											  //cout<<"ÿ���С"<<sizeof(temp)<<endl;
	}
	//cout<<"���ݿ���Ŀ"<<MFS.dataArea.size()<<endl;
	//cout<<"��ʼ��������ɹ���"<<endl;
	return;
}


void  Initialize_Index_List()  //��ʼ��������
{
	NextFreeG = 0;
	StackNum = 0;
	while (!MFS.superStack.empty())//�������ջ���գ���ջ������ȫ��pop��ȥ
	{
		MFS.superStack.pop();
	}
	for (int i = 0; i<GROUPNUM; i++)
	{
		for (int j = GROUPSIZE - 1; j >= 0; j--)
		{
			MFS.vacant[i][j] = i * GROUPSIZE + GROUPSIZE - j - 1;
			//cout<<i<<","<<j<<MFS.vacant[i][j]<<endl;
		}
	}
	//cout<<"��ʼ���������ɹ���"<<endl;
	return;
}


void Initialize_userinfo()   // ��ʼ���û���Ϣ
{
	MFS.userinfo[UCount].name = "root";
	MFS.userinfo[UCount++].password = "123456";
}


void Initialize_Vector_Director()   //��ʼ��Ŀ¼��Ϣ
{
	MFS.DSV.clear();
	folder first;
	first.father = -1;
	first.id = 0;
	first.name = "home";
	first.owner = "empty";
	first.time = gettime();
	MFS.DSV.push_back(first);
	//cout<<"��ʼ��Ŀ¼��Ϣ�ɹ�!"<<endl;
}




void Initializerp()   //��ʼ����·��
{
	while (1)
	{
		cout << "�����ñ��ļ�ϵͳ�ĸ�Ŀ¼��Ĭ��Ϊ�� " << path << endl;
		cout << "�Ƿ���ģ�Y/N" << endl;
		char input;

		while (1)
		{
			cin >> input;
			if (input == 'Y' || input == 'y')
			{
				cout << "�������µĸ�Ŀ¼" << endl;
				string temp;
				cin >> temp;
				if (temp[1] == ':' && temp[2] == '\\' && ((temp[0] >= 'c' && temp[0] <= 'g') || ((temp[0] >= 'C' && temp[0] <= 'G'))))
				{
					cout << "���ĸ�Ŀ¼�ɹ���" << endl;
					path = temp;
					print();
					return;
				}
				else
				{
					cout << "����ĸ�Ŀ¼�������Ϲ淶!" << endl;
					break;
				}
			}
			else
			{
				if (input == 'N' || input == 'n')
				{
					print();
					return;
				}
				else
				{
					cout << "����ָ������������Y/N" << endl;
				}
			}
		}
		print();
	}


}


void Initialize_Memory()  // ��ʼ���ڴ�
{
	memory_index = 0;
	for (int i = 0; i<SYSOPENFILE; i++)
	{
		for (int j = 0; j<BLOCKSIZE; j++)
		{
			memory[i][j] = '\0';
		}
	}
	//cout<<"��ʼ���ڴ�ɹ�!"<<endl;
}


bool Initialize()  // ��ʼ��
{
	Initializerp();        // ��ʼ����·��
	try
	{
		Initialize_Vector_Director();   // ��ʼ���ļ�����Ϣ

		CurD = 0;
		open_FV.clear();
		MFS.FSV.clear();

		Initialize_dataBlock();		 // ��ʼ�����ݿ�
		Initialize_Index_List();		// ��ʼ��������
		Initialize_userinfo();			// ��ʼ���û���Ϣ
		language = 0;
		if (language) cout << "��ʼ���ɹ�" << endl;
		else  cout << "Initialization success" << endl;
	}
	catch (const std::exception&)
	{
		if (language) cout << "��ʼ��ʧ��" << endl;
		else  cout << "Initialization failure" << endl;
	}
	print();
	return true;
}



