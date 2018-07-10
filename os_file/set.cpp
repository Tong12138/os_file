#include"stdafx.h"
#include <stdlib.h>
#include <stdio.h>

fileSystem myFileSystem;
int memory_index;
char memory[SYSOPENFILE][BLOCKSIZE];
int current_director_index;
int next_free_list_index;
int super_stack_number;
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
		myFileSystem.dataArea.push_back(temp);//��vectorβ����������
											  //cout<<"ÿ���С"<<sizeof(temp)<<endl;
	}
	//cout<<"���ݿ���Ŀ"<<myFileSystem.dataArea.size()<<endl;
	//cout<<"��ʼ��������ɹ���"<<endl;
	return;
}


void  Initialize_Index_List()  //��ʼ��������
{
	next_free_list_index = 0;
	super_stack_number = 0;
	while (!myFileSystem.superStack.empty())//�������ջ���գ���ջ������ȫ��pop��ȥ
	{
		myFileSystem.superStack.pop();
	}
	for (int i = 0; i<GROUPNUM; i++)
	{
		for (int j = GROUPSIZE - 1; j >= 0; j--)
		{
			myFileSystem.free_list[i][j] = i * GROUPSIZE + GROUPSIZE - j - 1;
			//cout<<i<<","<<j<<myFileSystem.free_list[i][j]<<endl;
		}
	}
	//cout<<"��ʼ���������ɹ���"<<endl;
	return;
}


void Initialize_User_Info()   // ��ʼ���û���Ϣ
{
	myFileSystem.user_info[UCount].name = "root";
	myFileSystem.user_info[UCount++].password = "123456";
}


void Initialize_Vector_Director()   //��ʼ��Ŀ¼��Ϣ
{
	myFileSystem.vector_folder.clear();
	folder first;
	first.last_director = -1;
	first.id = 0;
	first.name = "home";
	first.owner = "empty";
	first.time = gettime();
	myFileSystem.vector_folder.push_back(first);
	//cout<<"��ʼ��Ŀ¼��Ϣ�ɹ�!"<<endl;
}




void Initialize_path()   //��ʼ����·��
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
	Initialize_path();        // ��ʼ����·��
	try
	{
		Initialize_Vector_Director();   // ��ʼ���ļ�����Ϣ

		current_director_index = 0;
		open_FV.clear();
		myFileSystem.vector_file.clear();

		Initialize_dataBlock();		 // ��ʼ�����ݿ�
		Initialize_Index_List();		// ��ʼ��������
		Initialize_User_Info();			// ��ʼ���û���Ϣ
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



