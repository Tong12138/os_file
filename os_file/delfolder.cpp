#include"stdafx.h"
bool delete_empty_dir(string director_name, int pos)  // 删除空的文件夹
{
	vector<int>::iterator p_list = MFS.DSV[CurD].DV.begin();
	while (p_list != MFS.DSV[CurD].DV.end())
	{
		int index = *p_list;
		if (index != -1 && MFS.DSV[index].name == director_name)
		{
			//current_director.DV.erase(p_list);   // 从当前目录中删除
			*p_list = -1;   // 标示成不可用
			break;
		}
		p_list++;
	}

	if (language) cout << "删除文件夹 " << director_name << " 成功" << endl;
	else cout << "Delete folder " << director_name << " successful" << endl;
	return true;
}

bool delete_not_empty_dir(string director_name, int pos)   // 删除非空文件夹
{
	folder temp = MFS.DSV[CurD];
	CurD = MFS.DSV[pos].id;  // 当前目录暂时 进入该文件夹内

	vector<int>::iterator p = MFS.DSV[CurD].FV.begin();          // 删除子目录下所有文件
	while (p != MFS.DSV[CurD].FV.end())
	{
		int index = *p;
		delfile(MFS.FSV[index].filename);
		p++;
	}

	vector<int>::iterator dir_p = MFS.DSV[CurD].DV.begin();
	while (dir_p != MFS.DSV[CurD].DV.end())
	{
		delete_not_empty_dir(MFS.DSV[*dir_p].name, *dir_p);     // 删除非空子目录
		dir_p++;
	}
	CurD = temp.id;  // 回复当前目录
	delete_empty_dir(director_name, pos);  // 删除已空的文件夹

	return true;

}



bool deldir(string director_name)  // 删除文件夹
{
	int pos = includedir(director_name);
	if (pos == -1)
	{
		if (language) {
			cout << "当前目录中不包含 " << director_name << " 文件夹" << endl;
			cout << "删除失败" << endl;
		}
		else
		{
			cout << "The current directory does not contain " << director_name << " folder" << endl;
			cout << "Delete failed" << endl;
		}
		return false;
	}

	if (MFS.DSV[pos].owner != CurU.name && MFS.DSV[pos].owner != "empty")
	{
		if (language) cout << "您没有该文件夹的操作权限!" << endl;
		else cout << "You don't have access to this folder!" << endl;
		return false;
	}

	folder temp = MFS.DSV[pos];

	if (temp.FV.empty() && temp.DV.empty())
	{
		delete_empty_dir(director_name, pos);  // 删除空文件夹
	}
	else
	{
		if (language) cout << "要删除的目录非空，是否删除其中所有文件及文件夹?Y/N" << endl;
		else cout << "Do you delete all of the files and folders you want to delete? Y/N" << endl;
		char input;
		cin >> input;
		if (input == 'Y' || input == 'y')
		{
			delete_not_empty_dir(director_name, pos);  // 删除非空文件夹
		}
		else
		{
			if (input == 'N' || input == 'n')
			{
				if (language) cout << "您已取消本次删除" << endl;
				else  cout << "You have cancelled this deletion" << endl;
				return false;
			}
			else
			{
				if (language)cout << "请输入有效指令" << endl;
				else cout << "Please enter valid instructions" << endl;
				deldir(director_name);
			}
		}
	}
	return true;
}


bool delete_empty_dir1(string director_name, int pos);

bool delete_not_empty_dir1(string director_name, int pos)   // 删除非空文件夹
{
	folder temp = MFS.DSV[CurD];			//当前目录值赋给临时目录
	CurD = MFS.DSV[pos].id;					//当前目录暂时进入该文件夹内

	vector<int>::iterator p = MFS.DSV[CurD].FV.begin();          // 删除子目录下所有文件
	while (p != MFS.DSV[CurD].FV.end())
	{
		int index = *p;
		delfile(MFS.FSV[index].filename);							//删除文件
		p++;
	}
	vector<int>::iterator dir_p = MFS.DSV[CurD].DV.begin();	//定位在目录链表的头结点，赋值给p
	while (dir_p != MFS.DSV[CurD].DV.end())				//当指针没有指向链表的末尾
	{
		delete_not_empty_dir1(MFS.DSV[*dir_p].name, *dir_p);     // 删除非空子目录（递归）
		dir_p++;
	}
	CurD = temp.id;  // 回复当前目录（回到当前目录）
	delete_empty_dir1(director_name, pos);  // 删除已空的文件夹
	return true;
}




bool delete_empty_dir1(string director_name, int pos)  // 删除空的文件夹
{
	vector<int>::iterator p_list = MFS.DSV[CurD].DV.begin();	//头指针赋给p_list
	while (p_list != MFS.DSV[CurD].DV.end())					//指针没有到目录最后一个节点
	{
		int index = *p_list;
		if (index != -1 && MFS.DSV[index].name == director_name)
		{
			//current_director.DV.erase(p_list);   // 从当前目录中删除
			*p_list = -1;   // 标示成不可用
			return true;
		}
		p_list++;
	}
	return false;
}

bool initi1(string director_name, int pos)   //格式化非空文件夹
{
	folder temp = MFS.DSV[CurD];			//当前目录值赋给临时目录
	CurD = MFS.DSV[pos].id;					//当前目录暂时进入该文件夹内

	vector<int>::iterator p = MFS.DSV[CurD].FV.begin();          // 删除子目录下所有文件
	while (p != MFS.DSV[CurD].FV.end())
	{
		int index = *p;
		delfile(MFS.FSV[index].filename);							//删除文件
		p++;
	}
	vector<int>::iterator dir_p = MFS.DSV[CurD].DV.begin();	//定位在目录链表的头结点，赋值给p
	while (dir_p != MFS.DSV[CurD].DV.end())				//当指针没有指向链表的末尾
	{
		delete_not_empty_dir1(MFS.DSV[*dir_p].name, *dir_p);     // 删除非空子目录（递归）
		dir_p++;
	}
	CurD = temp.id;  // 回复当前目录（回到当前目录）
	return true;
}


bool initi(string director_name)  // 格式化文件夹
{
	int pos = includedir(director_name);
	if (pos == -1)
	{
		if (language) {
			cout << "当前目录中不包含 " << director_name << " 文件夹" << endl;
			cout << "删除失败" << endl;
		}
		else {
			cout << "The current directory does not contain " << director_name << " folder" << endl;
			cout << "Delete failed" << endl;
		}
		return false;
	}
	if (MFS.DSV[pos].owner != CurU.name && MFS.DSV[pos].owner != "empty")	//权限
	{
		if (language) cout << "您没有该文件夹的操作权限!" << endl;
		else  cout << "You don't have access to this folder!" << endl;
		return false;
	}
	folder temp = MFS.DSV[pos];			//
	if (temp.FV.empty() && temp.DV.empty())
	{
		if (language) cout << "格式化成功！" << endl;
		else  cout << "Formatted success！" << endl;
	}
	else
	{
		if (language) cout << "要格式化的目录非空，是否删除其中所有文件及文件夹?Y/N" << endl;
		else cout << "Do you delete all of the files and folders you want to format? Y/N" << endl;
		char input;
		cin >> input;
		if (input == 'Y' || input == 'y')
		{
			initi1(director_name, pos);  // 删除非空文件夹
		}
		else
		{
			if (input == 'N' || input == 'n')
			{
				if (language) cout << "您已取消本次格式化" << endl;
				else cout << "You had canceled this format" << endl;
				return false;
			}
			else
			{
				if (language) cout << "请输入有效指令" << endl;
				else  cout << "Please enter valid instructions" << endl;
				deldir(director_name);
			}
		}
	}
	return true;
}