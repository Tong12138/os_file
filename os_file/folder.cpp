#include"stdafx.h"
void mkdir(string director_name)    // ����Ŀ¼
{

	if (includefile(director_name) != -1)
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

	int pos = includedir(director_name);
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
	cout<<"����Ŀ¼"<<director_name<<"�ɹ�"<<endl;
	return;
	}
	}
	*/
	MFS.DSV[CurD].DV.push_back(temp.id);
	if (language) cout << "����Ŀ¼ " << director_name << " �ɹ�" << endl;
	else  cout << "Create a folder " << director_name << " success" << endl;
	return;
}

bool cd(string director_name)
{
	vector<int>::iterator p = MFS.DSV[CurD].DV.begin();
	while (p != MFS.DSV[CurD].DV.end())
	{
		int index = *p;
		if (MFS.DSV[index].name == director_name) // ���Ŀ¼��
		{
			if (MFS.DSV[index].owner == CurU.name || MFS.DSV[index].owner == "empty")//���Ȩ��
			{
				CurD = index;
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
	int index = MFS.DSV[CurD].father;
	if (index != -1)
	{
		CurD = index;
	}
	else
	{
		if (language) cout << "���Ѿ��ڸ�Ŀ¼�У�����������" << endl;
		else  cout << "You are already in the root directory and cannot go up" << endl;
	}
}