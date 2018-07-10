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

void Initialize_dataBlock()  //初始化数据块
{
	for (int i = 0; i<BLOCKNUM; i++)
	{
		dataBlock temp;
		temp.next = -1;
		temp.used = 0;
		for (int j = 0; j<BLOCKSIZE + 1; j++)
		{
			temp.content[j] = '\0';//临时变量内容置为0
		}
		myFileSystem.dataArea.push_back(temp);//在vector尾部加入数据
											  //cout<<"每块大小"<<sizeof(temp)<<endl;
	}
	//cout<<"数据块数目"<<myFileSystem.dataArea.size()<<endl;
	//cout<<"初始化数据域成功！"<<endl;
	return;
}


void  Initialize_Index_List()  //初始化成组链
{
	next_free_list_index = 0;
	super_stack_number = 0;
	while (!myFileSystem.superStack.empty())//如果超级栈不空，将栈内内容全都pop出去
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
	//cout<<"初始化成组链成功！"<<endl;
	return;
}


void Initialize_User_Info()   // 初始化用户信息
{
	myFileSystem.user_info[UCount].name = "root";
	myFileSystem.user_info[UCount++].password = "123456";
}


void Initialize_Vector_Director()   //初始化目录信息
{
	myFileSystem.vector_folder.clear();
	folder first;
	first.last_director = -1;
	first.id = 0;
	first.name = "home";
	first.owner = "empty";
	first.time = gettime();
	myFileSystem.vector_folder.push_back(first);
	//cout<<"初始化目录信息成功!"<<endl;
}




void Initialize_path()   //初始化根路径
{
	while (1)
	{
		cout << "请设置本文件系统的根目录，默认为： " << path << endl;
		cout << "是否更改？Y/N" << endl;
		char input;

		while (1)
		{
			cin >> input;
			if (input == 'Y' || input == 'y')
			{
				cout << "请输入新的根目录" << endl;
				string temp;
				cin >> temp;
				if (temp[1] == ':' && temp[2] == '\\' && ((temp[0] >= 'c' && temp[0] <= 'g') || ((temp[0] >= 'C' && temp[0] <= 'G'))))
				{
					cout << "更改根目录成功！" << endl;
					path = temp;
					print();
					return;
				}
				else
				{
					cout << "输入的根目录名不符合规范!" << endl;
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
					cout << "输入指令有误，请输入Y/N" << endl;
				}
			}
		}
		print();
	}


}


void Initialize_Memory()  // 初始化内存
{
	memory_index = 0;
	for (int i = 0; i<SYSOPENFILE; i++)
	{
		for (int j = 0; j<BLOCKSIZE; j++)
		{
			memory[i][j] = '\0';
		}
	}
	//cout<<"初始化内存成功!"<<endl;
}


bool Initialize()  // 初始化
{
	Initialize_path();        // 初始化根路径
	try
	{
		Initialize_Vector_Director();   // 初始化文件夹信息

		current_director_index = 0;
		open_FV.clear();
		myFileSystem.vector_file.clear();

		Initialize_dataBlock();		 // 初始化数据块
		Initialize_Index_List();		// 初始化成组链
		Initialize_User_Info();			// 初始化用户信息
		language = 0;
		if (language) cout << "初始化成功" << endl;
		else  cout << "Initialization success" << endl;
	}
	catch (const std::exception&)
	{
		if (language) cout << "初始化失败" << endl;
		else  cout << "Initialization failure" << endl;
	}
	print();
	return true;
}



