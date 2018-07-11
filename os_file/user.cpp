#include "stdafx.h"
#include<fstream>

user CurU;

bool CheckUser(string name, string password) // 检查该用户是否是初始化的用户
{
	for (int i = 0; i<USERNUM; i++)
	{
		if (MFS.userinfo[i].name == name && MFS.userinfo[i].password == password)
		{
			return true;
		}

	}
	return false;
}//denglu

bool SignIn()    //登录模块
{

	int chance = 5;
	string name;
	string password;
	while (chance > 0)
	{
		if (language) cout << "请输入用户名:";
		else cout << "USERNAME:";
		cin >> name;
		if (language)cout << "请输入密码：";
		else cout << "PASSWORD:";
		cin >> password;
		if (CheckUser(name, password))
		{
			CurU.name = name;
			CurU.password = password;
			return true;
		}
		else
		{
			if (language)cout << "用户名或密码错误，您还有 " << --chance << " 次机会" << endl;
			else cout << "User name or password error, you have " << --chance << " more chances" << endl;
			print();
		}
	}
	return false;


}//denglu




 /* 保存格式
 1. vector_director的个数
 2.vector_director的内容
 3.FSV的个数
 4.FSV的内容
 5.userinfo内容
 6.vacant内容  编号有小到大
 7.super_stack内容
 8.data_area内容
 */



 /*保存格式
 1.int id
 2.char* name
 3.char* owner
 4.int father
 5.int director数目
 6.int DV
 7.int file数目
 8.int FV
 */
bool SaveVectorDirector(FILE* fd)  //保存目录信息
{
	vector<folder>::iterator p = MFS.DSV.begin();//返回一个迭代器，指向第一个元素

	while (p != MFS.DSV.end())
	{
		int director_num = (*p).DV.size();
		int file_num = (*p).FV.size();

		fprintf(fd, "%d\n%s\n%s\n%d\n%d\n%s\n", (*p).id, (*p).name.c_str(), (*p).owner.c_str(), (*p).father, director_num, (*p).time.c_str());

		vector<int>::iterator p_list = (*p).DV.begin();  // 写入DV
		while (p_list != (*p).DV.end())
		{
			fprintf(fd, "%d\n", (*p_list));
			p_list++;
		}

		fprintf(fd, "%d\n", file_num);
		p_list = (*p).FV.begin();          // 写入FV
		while (p_list != (*p).FV.end())
		{
			fprintf(fd, "%d\n", (*p_list));
			p_list++;
		}

		p++;
	}
	//cout<<"保存目录信息成功"<<endl;
	return true;
}



/*保存格式
1.int id
2.char* filename
3.int blockpos
4.char* owner
5.int filelength
6.int beginning_in_memory
*/
bool SaveVectorFile(FILE* fd)  // 保存文件信息
{
	vector<file>::iterator p = MFS.FSV.begin();
	while (p != MFS.FSV.end())
	{
		fprintf(fd, "%d\n%s\n%d\n%s\n%d\n%d\n%s\n", (*p).id, (*p).filename.c_str(), (*p).blockpos, (*p).owner.c_str(), (*p).filelength, (*p).memorypos, (*p).time.c_str());
		p++;
	}
	//cout<<"保存文件信息成功"<<endl;
	return true;
}

bool SaveUserInfo(FILE* fd)  // 保存用户信息
{

	for (int i = 0; i<UCount; i++)
	{
		user temp = MFS.userinfo[i];
		fprintf(fd, "%s\n%s\n", temp.name.c_str(), temp.password.c_str());
	}
	//cout<<"保存用户信息成功"<<endl;
	return true;
}



bool SaveFreeList(FILE* fd)  //保存成组链
{
	for (int i = 0; i<GROUPNUM; i++)
	{
		for (int j = 0; j<GROUPSIZE; j++)
		{
			fprintf(fd, "%d\n", MFS.vacant[i][j]);
		}
	}
	//cout<<"保存成组链成功"<<endl;
	return true;
}



/*
1. int NextFreeG;   // 下一组要使用的组数  0~GROUPNUM-1
2. int StackNum;     // 超级栈中可以使用的块数
3. int 栈中内容 逆序
*/

bool SaveSuperStack(FILE* fd)  // 保存超级栈
{
	stack<int> temp;
	fprintf(fd, "%d\n%d\n", NextFreeG, StackNum);
	while (!MFS.superStack.empty())   // 将内容保存到另一个栈中，逆序保存，这样加载的时候顺序才对
	{
		int top = MFS.superStack.top();
		temp.push(top);
		MFS.superStack.pop();
	}
	while (!temp.empty())
	{
		fprintf(fd, "%d\n", temp.top());
		temp.pop();
	}
	//cout<<"保存超级栈成功"<<endl;
	return true;
}



//保存格式  int is_null  int next  int used  char* content
bool SaveDataArea(FILE* fd) //保存数据域内容
{
	for (int i = 0; i<BLOCKNUM; i++)
	{
		int is_null = 1;    // 做个标记，1表示内容是空，0表示非空
		dataBlock temp = MFS.dataArea[i];
		if (temp.content[0] != '\0')       // 如果非空，做上标记
		{
			is_null = 0;
		}
		fprintf(fd, "%d\n%d\n%d\n", is_null, temp.next, temp.used);
		if (is_null == 0)    //非空的把内容存入
		{
			fprintf(fd, "%s\n", temp.content);
		}
	}
	//cout<<"保存数据域内容成功"<<endl;
	return true;
}

bool SignOut()
{
	FILE* out;
	if (fopen_s(&out, guide.c_str(), "w+") != 0) {

	}
	fprintf(out, "%s\n", path.c_str());
	fclose(out);
	FILE* fd;
	try
	{
		if (fopen_s(&fd, path.c_str(), "w+") != 0)
		{
			if (language) cout << "打开文件 " << path << " 失败，无法保存" << endl;
			else  cout << "Open the file " << path << " failure, unable to save" << endl;
			return false;
		}
		fprintf(fd, "%d\n\n", language);
		fprintf(fd, "%d\n\n", UCount);
		int director_num = MFS.DSV.size();
		int file_num = MFS.FSV.size();
		fprintf(fd, "%d\n", director_num);
		SaveVectorDirector(fd);      //写入vector_director内容
		fprintf(fd, "\n%d\n", file_num);
		SaveVectorFile(fd);
		fprintf(fd, "\n");
		SaveUserInfo(fd);
		fprintf(fd, "\n");
		SaveFreeList(fd);
		fprintf(fd, "\n");
		SaveSuperStack(fd);
		fprintf(fd, "\n");
		SaveDataArea(fd);
		//language = 0;
		//fprintf(fd, "%d\n", language);
	}
	catch (const std::exception&)
	{
		if (language) {
			cout << "保存失败" << endl;
		}
		else cout << "save up failed" << endl;
	}
	if (language) {
		cout << "文件系统保存成功!" << endl;
	}
	else cout << "save up success" << endl;
	print();
	fclose(fd);

	return true;
}

