#include"stdafx.h"
void mkdir(string director_name)    // 创建目录
{

	if (includefile(director_name) != -1)
	{
		if (language) {
			cout << "本目录中已存在名为 " << director_name << " 的文件" << endl;
			cout << "文件夹创建失败" << endl;
		}
		else {
			cout << "There is already a name in this directory " << director_name << " file" << endl;
			cout << "Failed file creation" << endl;
		}
		return;
	}

	int pos = includedir(director_name);
	if (pos != -1)
	{
		if (language) {
			cout << "当前目录中已包含名为 " << director_name << " 的文件夹" << endl;
			cout << "创建失败!" << endl;
		}
		else
		{
			cout << "There is already a name in this directory " << director_name << " folder" << endl;
			cout << "Failed folder creation" << endl;
		}
		return;
	}



	folder temp;
	temp.name = director_name;
	temp.father = CurD;
	temp.owner = CurU.name;
	temp.id = MFS.DSV.size();
	temp.time = gettime();
	MFS.DSV.push_back(temp);
	/*
	list<int>::iterator p = MFS.vector_director[CurD].DV.begin();
	while(p != MFS.vector_director[CurD].DV.end())
	{
	int index = *p;
	if(index == -1)
	{
	*p = temp.id;
	cout<<"创建目录"<<director_name<<"成功"<<endl;
	return;
	}
	}
	*/
	MFS.DSV[CurD].DV.push_back(temp.id);
	if (language) cout << "创建目录 " << director_name << " 成功" << endl;
	else  cout << "Create a folder " << director_name << " success" << endl;
	return;
}

bool cd(string director_name)
{
	vector<int>::iterator p = MFS.DSV[CurD].DV.begin();
	while (p != MFS.DSV[CurD].DV.end())
	{
		int index = *p;
		if (MFS.DSV[index].name == director_name) // 检查目录名
		{
			if (MFS.DSV[index].owner == CurU.name || MFS.DSV[index].owner == "empty")//检查权限
			{
				CurD = index;
				return true;
			}
			else
			{
				if (language) cout << "您没有该文件夹的操作权限" << endl;
				else  cout << "You do not have access to this folder" << endl;
				return false;
			}
		}
		p++;
	}

	if (language)cout << "您要前往的目录不存在" << endl;
	else cout << "The directory you want to go to does not exist" << endl;
	return false;
}

void ltdir()  // 前往上一级目录
{
	int index = MFS.DSV[CurD].father;
	if (index != -1)
	{
		CurD = index;
	}
	else
	{
		if (language) cout << "您已经在根目录中，不能再向上" << endl;
		else  cout << "You are already in the root directory and cannot go up" << endl;
	}
}