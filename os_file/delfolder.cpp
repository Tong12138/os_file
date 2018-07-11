#include"stdafx.h"
bool delete_empty_dir(string director_name, int pos)  // ɾ���յ��ļ���
{
	vector<int>::iterator p_list = MFS.DSV[CurD].DV.begin();
	while (p_list != MFS.DSV[CurD].DV.end())
	{
		int index = *p_list;
		if (index != -1 && MFS.DSV[index].name == director_name)
		{
			//current_director.DV.erase(p_list);   // �ӵ�ǰĿ¼��ɾ��
			*p_list = -1;   // ��ʾ�ɲ�����
			break;
		}
		p_list++;
	}

	if (language) cout << "ɾ���ļ��� " << director_name << " �ɹ�" << endl;
	else cout << "Delete folder " << director_name << " successful" << endl;
	return true;
}

bool delete_not_empty_dir(string director_name, int pos)   // ɾ���ǿ��ļ���
{
	folder temp = MFS.DSV[CurD];
	CurD = MFS.DSV[pos].id;  // ��ǰĿ¼��ʱ ������ļ�����

	vector<int>::iterator p = MFS.DSV[CurD].FV.begin();          // ɾ����Ŀ¼�������ļ�
	while (p != MFS.DSV[CurD].FV.end())
	{
		int index = *p;
		delfile(MFS.FSV[index].filename);
		p++;
	}

	vector<int>::iterator dir_p = MFS.DSV[CurD].DV.begin();
	while (dir_p != MFS.DSV[CurD].DV.end())
	{
		delete_not_empty_dir(MFS.DSV[*dir_p].name, *dir_p);     // ɾ���ǿ���Ŀ¼
		dir_p++;
	}
	CurD = temp.id;  // �ظ���ǰĿ¼
	delete_empty_dir(director_name, pos);  // ɾ���ѿյ��ļ���

	return true;

}



bool deldir(string director_name)  // ɾ���ļ���
{
	int pos = includedir(director_name);
	if (pos == -1)
	{
		if (language) {
			cout << "��ǰĿ¼�в����� " << director_name << " �ļ���" << endl;
			cout << "ɾ��ʧ��" << endl;
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
		if (language) cout << "��û�и��ļ��еĲ���Ȩ��!" << endl;
		else cout << "You don't have access to this folder!" << endl;
		return false;
	}

	folder temp = MFS.DSV[pos];

	if (temp.FV.empty() && temp.DV.empty())
	{
		delete_empty_dir(director_name, pos);  // ɾ�����ļ���
	}
	else
	{
		if (language) cout << "Ҫɾ����Ŀ¼�ǿգ��Ƿ�ɾ�����������ļ����ļ���?Y/N" << endl;
		else cout << "Do you delete all of the files and folders you want to delete? Y/N" << endl;
		char input;
		cin >> input;
		if (input == 'Y' || input == 'y')
		{
			delete_not_empty_dir(director_name, pos);  // ɾ���ǿ��ļ���
		}
		else
		{
			if (input == 'N' || input == 'n')
			{
				if (language) cout << "����ȡ������ɾ��" << endl;
				else  cout << "You have cancelled this deletion" << endl;
				return false;
			}
			else
			{
				if (language)cout << "��������Чָ��" << endl;
				else cout << "Please enter valid instructions" << endl;
				deldir(director_name);
			}
		}
	}
	return true;
}


bool delete_empty_dir1(string director_name, int pos);

bool delete_not_empty_dir1(string director_name, int pos)   // ɾ���ǿ��ļ���
{
	folder temp = MFS.DSV[CurD];			//��ǰĿ¼ֵ������ʱĿ¼
	CurD = MFS.DSV[pos].id;					//��ǰĿ¼��ʱ������ļ�����

	vector<int>::iterator p = MFS.DSV[CurD].FV.begin();          // ɾ����Ŀ¼�������ļ�
	while (p != MFS.DSV[CurD].FV.end())
	{
		int index = *p;
		delfile(MFS.FSV[index].filename);							//ɾ���ļ�
		p++;
	}
	vector<int>::iterator dir_p = MFS.DSV[CurD].DV.begin();	//��λ��Ŀ¼�����ͷ��㣬��ֵ��p
	while (dir_p != MFS.DSV[CurD].DV.end())				//��ָ��û��ָ�������ĩβ
	{
		delete_not_empty_dir1(MFS.DSV[*dir_p].name, *dir_p);     // ɾ���ǿ���Ŀ¼���ݹ飩
		dir_p++;
	}
	CurD = temp.id;  // �ظ���ǰĿ¼���ص���ǰĿ¼��
	delete_empty_dir1(director_name, pos);  // ɾ���ѿյ��ļ���
	return true;
}




bool delete_empty_dir1(string director_name, int pos)  // ɾ���յ��ļ���
{
	vector<int>::iterator p_list = MFS.DSV[CurD].DV.begin();	//ͷָ�븳��p_list
	while (p_list != MFS.DSV[CurD].DV.end())					//ָ��û�е�Ŀ¼���һ���ڵ�
	{
		int index = *p_list;
		if (index != -1 && MFS.DSV[index].name == director_name)
		{
			//current_director.DV.erase(p_list);   // �ӵ�ǰĿ¼��ɾ��
			*p_list = -1;   // ��ʾ�ɲ�����
			return true;
		}
		p_list++;
	}
	return false;
}

bool initi1(string director_name, int pos)   //��ʽ���ǿ��ļ���
{
	folder temp = MFS.DSV[CurD];			//��ǰĿ¼ֵ������ʱĿ¼
	CurD = MFS.DSV[pos].id;					//��ǰĿ¼��ʱ������ļ�����

	vector<int>::iterator p = MFS.DSV[CurD].FV.begin();          // ɾ����Ŀ¼�������ļ�
	while (p != MFS.DSV[CurD].FV.end())
	{
		int index = *p;
		delfile(MFS.FSV[index].filename);							//ɾ���ļ�
		p++;
	}
	vector<int>::iterator dir_p = MFS.DSV[CurD].DV.begin();	//��λ��Ŀ¼�����ͷ��㣬��ֵ��p
	while (dir_p != MFS.DSV[CurD].DV.end())				//��ָ��û��ָ�������ĩβ
	{
		delete_not_empty_dir1(MFS.DSV[*dir_p].name, *dir_p);     // ɾ���ǿ���Ŀ¼���ݹ飩
		dir_p++;
	}
	CurD = temp.id;  // �ظ���ǰĿ¼���ص���ǰĿ¼��
	return true;
}


bool initi(string director_name)  // ��ʽ���ļ���
{
	int pos = includedir(director_name);
	if (pos == -1)
	{
		if (language) {
			cout << "��ǰĿ¼�в����� " << director_name << " �ļ���" << endl;
			cout << "ɾ��ʧ��" << endl;
		}
		else {
			cout << "The current directory does not contain " << director_name << " folder" << endl;
			cout << "Delete failed" << endl;
		}
		return false;
	}
	if (MFS.DSV[pos].owner != CurU.name && MFS.DSV[pos].owner != "empty")	//Ȩ��
	{
		if (language) cout << "��û�и��ļ��еĲ���Ȩ��!" << endl;
		else  cout << "You don't have access to this folder!" << endl;
		return false;
	}
	folder temp = MFS.DSV[pos];			//
	if (temp.FV.empty() && temp.DV.empty())
	{
		if (language) cout << "��ʽ���ɹ���" << endl;
		else  cout << "Formatted success��" << endl;
	}
	else
	{
		if (language) cout << "Ҫ��ʽ����Ŀ¼�ǿգ��Ƿ�ɾ�����������ļ����ļ���?Y/N" << endl;
		else cout << "Do you delete all of the files and folders you want to format? Y/N" << endl;
		char input;
		cin >> input;
		if (input == 'Y' || input == 'y')
		{
			initi1(director_name, pos);  // ɾ���ǿ��ļ���
		}
		else
		{
			if (input == 'N' || input == 'n')
			{
				if (language) cout << "����ȡ�����θ�ʽ��" << endl;
				else cout << "You had canceled this format" << endl;
				return false;
			}
			else
			{
				if (language) cout << "��������Чָ��" << endl;
				else  cout << "Please enter valid instructions" << endl;
				deldir(director_name);
			}
		}
	}
	return true;
}