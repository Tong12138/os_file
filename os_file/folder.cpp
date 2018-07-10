#include"stdafx.h"
void mkdir(string director_name)    // 创建目录
{

	if (IsFileInCurrentDirector(director_name) != -1)
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

	int pos = IsDirectorInCurrentDirector(director_name);
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
	temp.last_director = current_director_index;
	temp.owner = current_user.name;
	temp.id = myFileSystem.vector_folder.size();
	temp.time = gettime();
	myFileSystem.vector_folder.push_back(temp);
	/*
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].DV.begin();
	while(p != myFileSystem.vector_director[current_director_index].DV.end())
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
	myFileSystem.vector_folder[current_director_index].DV.push_back(temp.id);
	if (language) cout << "创建目录 " << director_name << " 成功" << endl;
	else  cout << "Create a folder " << director_name << " success" << endl;
	return;
}

bool ntdir(string director_name)
{
	vector<int>::iterator p = myFileSystem.vector_folder[current_director_index].DV.begin();
	while (p != myFileSystem.vector_folder[current_director_index].DV.end())
	{
		int index = *p;
		if (myFileSystem.vector_folder[index].name == director_name) // 检查目录名
		{
			if (myFileSystem.vector_folder[index].owner == current_user.name || myFileSystem.vector_folder[index].owner == "empty")//检查权限
			{
				current_director_index = index;
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
	int index = myFileSystem.vector_folder[current_director_index].last_director;
	if (index != -1)
	{
		current_director_index = index;
	}
	else
	{
		if (language) cout << "您已经在根目录中，不能再向上" << endl;
		else  cout << "You are already in the root directory and cannot go up" << endl;
	}
}