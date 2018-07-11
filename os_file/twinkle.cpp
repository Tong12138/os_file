#include "stdafx.h"

bool ParsePath(string path)  // 把路径解析出来
{
	int begin = 0;
	unsigned int ending = 0;
	string accessed;  // 已经过的路径
	bool flag = true;  // 表示是否是第一个目录
	while (ending < strlen(path.c_str()))
	{
		if (path[ending] == '\\')
		{
			string director = path.substr(begin, ending - begin);
			if (flag)
			{
				if (director != "home")             // 首目录必须是home
				{
					if (language) {
						cout << "输入的路径不正确！" << endl;
						cout << "请输入绝对路径！如：home\\one\\two" << endl;
					}
					else
					{
						cout << "The input path is incorrect!" << endl;
						cout << "Please enter an absolute path! Such as: home\\one\\two" << endl;
					}
					return false;
				}
				accessed += director;
				flag = false;
			}
			else
			{
				if (!cd(director))  //到下一目录
				{
					if (language)cout << "无法到达 " << accessed << " 路径下的 " << director << " 文件夹" << endl;
					else cout << "Cannot reach " << accessed << " under the path of " << director << " folder" << endl;
					return false;
				}
				accessed += director;
			}

			begin = ending + 1;
			//cout<<"得到的目录是"<<director<<endl;

		}
		ending++;
	}
	string director = path.substr(begin, ending - begin);
	if (!cd(director))
	{
		if (language)cout << "无法到达 " << accessed << " 路径下的 " << director << " 文件夹" << endl;
		else cout << "Cannot reach " << accessed << " under the path of " << director << " folder" << endl;
		return false;
	}
	if (language)cout << "跳转到 " << path << " 成功！" << endl;
	else cout << "Jump to " << path << " Success!" << endl;
	return true;
}


void CopyDirector(int pos, int limit)   //复制pos处的目录   
										//limit是为了防止 新建的目录被重复新建 如果发现要新建的目录索引大于或等于
										//limit就不用再新建了
{
	//把pos处目录包含的所有文件夹全部新建，更新father

	folder current = MFS.DSV[pos];
	folder temp;
	temp.id = MFS.DSV.size();

	temp.name = current.name;
	temp.owner = current.owner;
	temp.time = gettime();
	temp.father = CurD;   //更新father

	vector<int>::iterator p = current.FV.begin();  //文件的索引相同  
	while (p != current.FV.end())
	{
		temp.FV.push_back(*p);
		p++;
	}

	MFS.DSV[CurD].DV.push_back(temp.id);  // 在当前目录中加入新的目录
	MFS.DSV.push_back(temp);//在目录信息中加入新的目录
	CurD = temp.id;	//更新当前目录

	p = current.DV.begin();  // 在当前目录的子目录中继续复制
	while (p != current.DV.end())
	{
		if (*p != -1 && *p < limit)
		{
			CopyDirector(*p, limit);
		}
		p++;
	}

}

bool copy(string name, string path)
{
	int strore_director = CurD;  //暂存
	CurD = 0;
	int pos = includefile(name);
	if (pos == -1)
	{
		pos = includedir(name);
		if (pos == -1)
		{
			if (language) {
				cout << "当前目录没有 " << name << " 的文件或文件夹" << endl;
				cout << "复制失败！" << endl;
			}
			else {
				cout << "The current directory is not " << name << " files or folders" << endl;
				cout << "Duplicate failure!" << endl;
			}
			return false;
		}
		else// 复制的是文件夹
		{
			if (MFS.DSV[pos].owner != CurU.name && MFS.DSV[pos].owner != "empty")//验证权限
			{
				if (language) {
					cout << "您没有操作 " << name << " 文件夹的权限" << endl;
					cout << "复制失败!" << endl;
				}
				else
				{
					cout << "You're not have working " << name << " folder permissions" << endl;
					cout << "Duplicate failure!" << endl;
				}
				return false;
			}

			if (!ParsePath(path))  //跳转到要复制到的目录中
			{
				if (language)cout << "复制失败！" << endl;
				else cout << "Duplicate failure!" << endl;
				return false;
			}
			CopyDirector(pos, MFS.DSV.size());


		}
	}
	else  // 复制的是文件
	{
		if (MFS.FSV[pos].owner != CurU.name && MFS.FSV[pos].owner != "empty")//验证权限
		{
			if (language) {
				cout << "您没有操作 " << name << " 文件夹的权限" << endl;
				cout << "复制失败!" << endl;
			}
			else
			{
				cout << "You're not have working " << name << " folder permissions" << endl;
				cout << "Duplicate failure!" << endl;
			}
			return false;
		}

		if (!ParsePath(path))    //跳转到要复制到的目录中
		{
			if (language)cout << "复制失败！" << endl;
			else cout << "Duplicate failure!" << endl;
			return false;
		}
		MFS.DSV[CurD].FV.push_back(pos);     //在该目录下添加对应文件的索引即可
	}

	if (language)cout << "复制成功！" << endl;
	else cout << "Duplicate success!" << endl;
	CurD = strore_director;  //恢复当前目录
	return true;
}


bool IsNameInCurrecdector(string name)  // 判断一个名字是否在当前目录中出现 包括 文件和目录
{
	int pos = includefile(name);
	if (pos == -1)   // 名字不在文件中
	{
		pos = includedir(name);
		if (pos == -1)     //名字不在目录中
		{
			return false;   // 名字不在当前目录
		}
	}
	return true;
}


bool rename(string old_name, string new_name)  // 重命名
{
	if (IsNameInCurrecdector(new_name) == true)
	{
		if (language) {
			cout << "新名字在当前目录中已存在，无法重新命名" << endl;
			cout << "重命名失败！" << endl;
		}
		else
		{
			cout << "The new name already exists in the current directory and cannot be renamed" << endl;
			cout << "Renaming failure！" << endl;
		}
		return false;
	}

	int pos = includefile(old_name);
	if (pos != -1)  // 如果要重命名的是文件
	{
		MFS.FSV[pos].filename = new_name;
		if (language) cout << "重命名成功！" << endl;
		else  cout << "Rename success！" << endl;
		return true;
	}
	else
	{
		pos = includedir(old_name);
		if (pos != -1)  // 重命名的是文件夹
		{
			MFS.DSV[pos].name = new_name;
			if (language) cout << "重命名成功！" << endl;
			else  cout << "Rename success！" << endl;
			return true;
		}
		else
		{
			if (language) {
				cout << "你要重命名的文件或文件夹不存在" << endl;
				cout << "重命名失败！" << endl;
			}
			else {
				cout << "The file or folder you want to rename does not exist" << endl;
				cout << "Renaming failure！" << endl;
			}

			return false;
		}
	}
}