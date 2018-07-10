#include"stdafx.h"
void mkdir(string director_name)    // ����Ŀ¼
{

	if (IsFileInCurrentDirector(director_name) != -1)
	{
		if (language) {
			cout << "��Ŀ¼���Ѵ�����Ϊ " << director_name << " ���ļ�" << endl;
			cout << "�ļ��д���ʧ��" << endl;
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
			cout << "��ǰĿ¼���Ѱ�����Ϊ " << director_name << " ���ļ���" << endl;
			cout << "����ʧ��!" << endl;
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
	cout<<"����Ŀ¼"<<director_name<<"�ɹ�"<<endl;
	return;
	}
	}
	*/
	myFileSystem.vector_folder[current_director_index].DV.push_back(temp.id);
	if (language) cout << "����Ŀ¼ " << director_name << " �ɹ�" << endl;
	else  cout << "Create a folder " << director_name << " success" << endl;
	return;
}

bool ntdir(string director_name)
{
	vector<int>::iterator p = myFileSystem.vector_folder[current_director_index].DV.begin();
	while (p != myFileSystem.vector_folder[current_director_index].DV.end())
	{
		int index = *p;
		if (myFileSystem.vector_folder[index].name == director_name) // ���Ŀ¼��
		{
			if (myFileSystem.vector_folder[index].owner == current_user.name || myFileSystem.vector_folder[index].owner == "empty")//���Ȩ��
			{
				current_director_index = index;
				return true;
			}
			else
			{
				if (language) cout << "��û�и��ļ��еĲ���Ȩ��" << endl;
				else  cout << "You do not have access to this folder" << endl;
				return false;
			}
		}
		p++;
	}

	if (language)cout << "��Ҫǰ����Ŀ¼������" << endl;
	else cout << "The directory you want to go to does not exist" << endl;
	return false;
}

void ltdir()  // ǰ����һ��Ŀ¼
{
	int index = myFileSystem.vector_folder[current_director_index].last_director;
	if (index != -1)
	{
		current_director_index = index;
	}
	else
	{
		if (language) cout << "���Ѿ��ڸ�Ŀ¼�У�����������" << endl;
		else  cout << "You are already in the root directory and cannot go up" << endl;
	}
}