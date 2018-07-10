#include"stdafx.h"
bool delete_empty_dir(string director_name, int pos)  // ɾ���յ��ļ���
{
	list<int>::iterator p_list = myFileSystem.vector_folder[current_director_index].director_list.begin();
	while (p_list != myFileSystem.vector_folder[current_director_index].director_list.end())
	{
		int index = *p_list;
		if (index != -1 && myFileSystem.vector_folder[index].name == director_name)
		{
			//current_director.director_list.erase(p_list);   // �ӵ�ǰĿ¼��ɾ��
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
	folder temp = myFileSystem.vector_folder[current_director_index];
	current_director_index = myFileSystem.vector_folder[pos].id;  // ��ǰĿ¼��ʱ ������ļ�����

	list<int>::iterator p = myFileSystem.vector_folder[current_director_index].file_list.begin();          // ɾ����Ŀ¼�������ļ�
	while (p != myFileSystem.vector_folder[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);
		p++;
	}

	list<int>::iterator dir_p = myFileSystem.vector_folder[current_director_index].director_list.begin();
	while (dir_p != myFileSystem.vector_folder[current_director_index].director_list.end())
	{
		delete_not_empty_dir(myFileSystem.vector_folder[*dir_p].name, *dir_p);     // ɾ���ǿ���Ŀ¼
		dir_p++;
	}
	current_director_index = temp.id;  // �ظ���ǰĿ¼
	delete_empty_dir(director_name, pos);  // ɾ���ѿյ��ļ���

	return true;

}



bool deldir(string director_name)  // ɾ���ļ���
{
	int pos = IsDirectorInCurrentDirector(director_name);
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

	if (myFileSystem.vector_folder[pos].owner != current_user.name && myFileSystem.vector_folder[pos].owner != "empty")
	{
		if (language) cout << "��û�и��ļ��еĲ���Ȩ��!" << endl;
		else cout << "You don't have access to this folder!" << endl;
		return false;
	}

	folder temp = myFileSystem.vector_folder[pos];

	if (temp.file_list.empty() && temp.director_list.empty())
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
	folder temp = myFileSystem.vector_folder[current_director_index];			//��ǰĿ¼ֵ������ʱĿ¼
	current_director_index = myFileSystem.vector_folder[pos].id;					//��ǰĿ¼��ʱ������ļ�����

	list<int>::iterator p = myFileSystem.vector_folder[current_director_index].file_list.begin();          // ɾ����Ŀ¼�������ļ�
	while (p != myFileSystem.vector_folder[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);							//ɾ���ļ�
		p++;
	}
	list<int>::iterator dir_p = myFileSystem.vector_folder[current_director_index].director_list.begin();	//��λ��Ŀ¼�����ͷ��㣬��ֵ��p
	while (dir_p != myFileSystem.vector_folder[current_director_index].director_list.end())				//��ָ��û��ָ�������ĩβ
	{
		delete_not_empty_dir1(myFileSystem.vector_folder[*dir_p].name, *dir_p);     // ɾ���ǿ���Ŀ¼���ݹ飩
		dir_p++;
	}
	current_director_index = temp.id;  // �ظ���ǰĿ¼���ص���ǰĿ¼��
	delete_empty_dir1(director_name, pos);  // ɾ���ѿյ��ļ���
	return true;
}




bool delete_empty_dir1(string director_name, int pos)  // ɾ���յ��ļ���
{
	list<int>::iterator p_list = myFileSystem.vector_folder[current_director_index].director_list.begin();	//ͷָ�븳��p_list
	while (p_list != myFileSystem.vector_folder[current_director_index].director_list.end())					//ָ��û�е�Ŀ¼���һ���ڵ�
	{
		int index = *p_list;
		if (index != -1 && myFileSystem.vector_folder[index].name == director_name)
		{
			//current_director.director_list.erase(p_list);   // �ӵ�ǰĿ¼��ɾ��
			*p_list = -1;   // ��ʾ�ɲ�����
			return true;
		}
		p_list++;
	}
	return false;
}

bool initi1(string director_name, int pos)   //��ʽ���ǿ��ļ���
{
	folder temp = myFileSystem.vector_folder[current_director_index];			//��ǰĿ¼ֵ������ʱĿ¼
	current_director_index = myFileSystem.vector_folder[pos].id;					//��ǰĿ¼��ʱ������ļ�����

	list<int>::iterator p = myFileSystem.vector_folder[current_director_index].file_list.begin();          // ɾ����Ŀ¼�������ļ�
	while (p != myFileSystem.vector_folder[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);							//ɾ���ļ�
		p++;
	}
	list<int>::iterator dir_p = myFileSystem.vector_folder[current_director_index].director_list.begin();	//��λ��Ŀ¼�����ͷ��㣬��ֵ��p
	while (dir_p != myFileSystem.vector_folder[current_director_index].director_list.end())				//��ָ��û��ָ�������ĩβ
	{
		delete_not_empty_dir1(myFileSystem.vector_folder[*dir_p].name, *dir_p);     // ɾ���ǿ���Ŀ¼���ݹ飩
		dir_p++;
	}
	current_director_index = temp.id;  // �ظ���ǰĿ¼���ص���ǰĿ¼��
	return true;
}


bool initi(string director_name)  // ��ʽ���ļ���
{
	int pos = IsDirectorInCurrentDirector(director_name);
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
	if (myFileSystem.vector_folder[pos].owner != current_user.name && myFileSystem.vector_folder[pos].owner != "empty")	//Ȩ��
	{
		if (language) cout << "��û�и��ļ��еĲ���Ȩ��!" << endl;
		else  cout << "You don't have access to this folder!" << endl;
		return false;
	}
	folder temp = myFileSystem.vector_folder[pos];			//
	if (temp.file_list.empty() && temp.director_list.empty())
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