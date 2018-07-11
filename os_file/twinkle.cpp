#include "stdafx.h"

bool ParsePath(string path)  // ��·����������
{
	int begin = 0;
	unsigned int ending = 0;
	string accessed;  // �Ѿ�����·��
	bool flag = true;  // ��ʾ�Ƿ��ǵ�һ��Ŀ¼
	while (ending < strlen(path.c_str()))
	{
		if (path[ending] == '\\')
		{
			string director = path.substr(begin, ending - begin);
			if (flag)
			{
				if (director != "home")             // ��Ŀ¼������home
				{
					if (language) {
						cout << "�����·������ȷ��" << endl;
						cout << "���������·�����磺home\\one\\two" << endl;
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
				if (!cd(director))  //����һĿ¼
				{
					if (language)cout << "�޷����� " << accessed << " ·���µ� " << director << " �ļ���" << endl;
					else cout << "Cannot reach " << accessed << " under the path of " << director << " folder" << endl;
					return false;
				}
				accessed += director;
			}

			begin = ending + 1;
			//cout<<"�õ���Ŀ¼��"<<director<<endl;

		}
		ending++;
	}
	string director = path.substr(begin, ending - begin);
	if (!cd(director))
	{
		if (language)cout << "�޷����� " << accessed << " ·���µ� " << director << " �ļ���" << endl;
		else cout << "Cannot reach " << accessed << " under the path of " << director << " folder" << endl;
		return false;
	}
	if (language)cout << "��ת�� " << path << " �ɹ���" << endl;
	else cout << "Jump to " << path << " Success!" << endl;
	return true;
}


void CopyDirector(int pos, int limit)   //����pos����Ŀ¼   
										//limit��Ϊ�˷�ֹ �½���Ŀ¼���ظ��½� �������Ҫ�½���Ŀ¼�������ڻ����
										//limit�Ͳ������½���
{
	//��pos��Ŀ¼�����������ļ���ȫ���½�������father

	folder current = MFS.DSV[pos];
	folder temp;
	temp.id = MFS.DSV.size();

	temp.name = current.name;
	temp.owner = current.owner;
	temp.time = gettime();
	temp.father = CurD;   //����father

	vector<int>::iterator p = current.FV.begin();  //�ļ���������ͬ  
	while (p != current.FV.end())
	{
		temp.FV.push_back(*p);
		p++;
	}

	MFS.DSV[CurD].DV.push_back(temp.id);  // �ڵ�ǰĿ¼�м����µ�Ŀ¼
	MFS.DSV.push_back(temp);//��Ŀ¼��Ϣ�м����µ�Ŀ¼
	CurD = temp.id;	//���µ�ǰĿ¼

	p = current.DV.begin();  // �ڵ�ǰĿ¼����Ŀ¼�м�������
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
	int strore_director = CurD;  //�ݴ�
	CurD = 0;
	int pos = includefile(name);
	if (pos == -1)
	{
		pos = includedir(name);
		if (pos == -1)
		{
			if (language) {
				cout << "��ǰĿ¼û�� " << name << " ���ļ����ļ���" << endl;
				cout << "����ʧ�ܣ�" << endl;
			}
			else {
				cout << "The current directory is not " << name << " files or folders" << endl;
				cout << "Duplicate failure!" << endl;
			}
			return false;
		}
		else// ���Ƶ����ļ���
		{
			if (MFS.DSV[pos].owner != CurU.name && MFS.DSV[pos].owner != "empty")//��֤Ȩ��
			{
				if (language) {
					cout << "��û�в��� " << name << " �ļ��е�Ȩ��" << endl;
					cout << "����ʧ��!" << endl;
				}
				else
				{
					cout << "You're not have working " << name << " folder permissions" << endl;
					cout << "Duplicate failure!" << endl;
				}
				return false;
			}

			if (!ParsePath(path))  //��ת��Ҫ���Ƶ���Ŀ¼��
			{
				if (language)cout << "����ʧ�ܣ�" << endl;
				else cout << "Duplicate failure!" << endl;
				return false;
			}
			CopyDirector(pos, MFS.DSV.size());


		}
	}
	else  // ���Ƶ����ļ�
	{
		if (MFS.FSV[pos].owner != CurU.name && MFS.FSV[pos].owner != "empty")//��֤Ȩ��
		{
			if (language) {
				cout << "��û�в��� " << name << " �ļ��е�Ȩ��" << endl;
				cout << "����ʧ��!" << endl;
			}
			else
			{
				cout << "You're not have working " << name << " folder permissions" << endl;
				cout << "Duplicate failure!" << endl;
			}
			return false;
		}

		if (!ParsePath(path))    //��ת��Ҫ���Ƶ���Ŀ¼��
		{
			if (language)cout << "����ʧ�ܣ�" << endl;
			else cout << "Duplicate failure!" << endl;
			return false;
		}
		MFS.DSV[CurD].FV.push_back(pos);     //�ڸ�Ŀ¼����Ӷ�Ӧ�ļ�����������
	}

	if (language)cout << "���Ƴɹ���" << endl;
	else cout << "Duplicate success!" << endl;
	CurD = strore_director;  //�ָ���ǰĿ¼
	return true;
}


bool IsNameInCurrecdector(string name)  // �ж�һ�������Ƿ��ڵ�ǰĿ¼�г��� ���� �ļ���Ŀ¼
{
	int pos = includefile(name);
	if (pos == -1)   // ���ֲ����ļ���
	{
		pos = includedir(name);
		if (pos == -1)     //���ֲ���Ŀ¼��
		{
			return false;   // ���ֲ��ڵ�ǰĿ¼
		}
	}
	return true;
}


bool rename(string old_name, string new_name)  // ������
{
	if (IsNameInCurrecdector(new_name) == true)
	{
		if (language) {
			cout << "�������ڵ�ǰĿ¼���Ѵ��ڣ��޷���������" << endl;
			cout << "������ʧ�ܣ�" << endl;
		}
		else
		{
			cout << "The new name already exists in the current directory and cannot be renamed" << endl;
			cout << "Renaming failure��" << endl;
		}
		return false;
	}

	int pos = includefile(old_name);
	if (pos != -1)  // ���Ҫ�����������ļ�
	{
		MFS.FSV[pos].filename = new_name;
		if (language) cout << "�������ɹ���" << endl;
		else  cout << "Rename success��" << endl;
		return true;
	}
	else
	{
		pos = includedir(old_name);
		if (pos != -1)  // �����������ļ���
		{
			MFS.DSV[pos].name = new_name;
			if (language) cout << "�������ɹ���" << endl;
			else  cout << "Rename success��" << endl;
			return true;
		}
		else
		{
			if (language) {
				cout << "��Ҫ���������ļ����ļ��в�����" << endl;
				cout << "������ʧ�ܣ�" << endl;
			}
			else {
				cout << "The file or folder you want to rename does not exist" << endl;
				cout << "Renaming failure��" << endl;
			}

			return false;
		}
	}
}