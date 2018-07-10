#include "stdafx.h"
int IsFileInCurrentDirector(string file_name)   // �ж�һ�ļ����Ƿ�����ڵ�ǰĿ¼�����ļ���  �����ڷ��ض�Ӧ������ �����ڷ���-1
{
	list<int>::iterator p = myFileSystem.vector_folder[current_director_index].file_list.begin();
	while (p != myFileSystem.vector_folder[current_director_index].file_list.end())
	{
		int index = *p;
		if (index != -1 && myFileSystem.vector_file[index].file_name == file_name)
		{

			return index;
		}
		p++;
	}

	return -1;
}

int IsDirectorInCurrentDirector(string file_name)  // �ж�һ�ļ����Ƿ���ڵĵ�ǰĿ¼����Ŀ¼��
{
	bool flag = false;
	list<int>::iterator p;

	p = myFileSystem.vector_folder[current_director_index].director_list.begin();
	while (p != myFileSystem.vector_folder[current_director_index].director_list.end())
	{
		int index = *p;
		if (index != -1 && myFileSystem.vector_folder[index].name == file_name)
		{

			return index;
		}
		p++;
	}
	return -1;
}

bool IsDataAreaFull()   // �ж��������Ƿ�����
{
	if (myFileSystem.superStack.empty() && myFileSystem.free_list[GROUPNUM - 1][0] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool create(string file_name)         // �����ļ�
{
	if (IsFileInCurrentDirector(file_name) != -1)
	{
		if (language) {
			cout << "��Ŀ¼���Ѵ�����Ϊ " << file_name << " ���ļ�" << endl;
			cout << "�ļ�����ʧ��" << endl;
		}
		else
		{
			cout << "There is already a name in this directory " << file_name << " file" << endl;
			cout << "Failed file creation" << endl;
		}
		return false;
	}

	if (IsDirectorInCurrentDirector(file_name) != -1)
	{
		if (language) {
			cout << "��Ŀ¼���Ѵ�����Ϊ " << file_name << " ���ļ���" << endl;
			cout << "�ļ��д���ʧ��" << endl;
		}
		else
		{
			cout << "There is already a name in this directory " << file_name << " folder" << endl;
			cout << "Failed folder creation" << endl;
		}

		return false;
	}

	if (IsDataAreaFull())
	{
		if (language) cout << "������������û���㹻�ռ䴴���ļ�" << endl;
		else cout << "The data domain is full and there is not enough space to create a file" << endl;
		return false;
	}

	file temp;
	temp.id = myFileSystem.vector_file.size();
	temp.file_length = 1;
	temp.owner = current_user.name;
	temp.file_name = file_name;
	temp.begining_in_memory = 0;
	temp.time = gettime();
	temp.beginning_in_dataArea = AllocDataBlock();
	if (language) cout << "���ļ�����������ݿ����: " << temp.beginning_in_dataArea << endl;
	else  cout << "The data block number that the file is assigned is: " << temp.beginning_in_dataArea << endl;
	myFileSystem.vector_file.push_back(temp);
	myFileSystem.vector_folder[current_director_index].file_list.push_back(temp.id);
	return true;
}

bool close(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);

	if (pos == -1)
	{
		if (language)cout << "��ǰĿ¼������ " << file_name << " �ļ�" << endl;
		else cout << "The current directory does not exist " << file_name << " file" << endl;
		if (language)cout << "���ļ�ʧ�ܣ�" << endl;
		else cout << "read file failed" << endl;
		return false;
	}

	list<openFile>::iterator open_file_p = IsInOpenFileList(pos);
	if (open_file_p == open_file_list.end())   // ����ļ��Ƿ��Ѵ�
	{
		if (language)cout << "���ļ���δ�򿪣��޷��ر�" << endl;
		else cout << "The file is not open and cannot be closed" << endl;
		return false;
	}

	file temp = myFileSystem.vector_file[pos];
	for (int i = temp.begining_in_memory; i <= temp.begining_in_memory + temp.file_length; i++)
	{
		for (int j = 0; j<BLOCKSIZE; j++)
		{
			if (memory[i][j] != '\0')
			{
				memory[i][j] = '\0';
			}
			else
			{
				break;
			}

		}
	}
	open_file_list.erase(open_file_p);   //�Ӵ�������ɾ��
	if (language) cout << "�ر��ļ� " << file_name << " �ɹ�" << endl;
	else cout << "close the file: " << file_name << " success" << endl;
	return true;

}

bool delfile(string file_name) //ɾ���ļ�
{

	int pos = IsFileInCurrentDirector(file_name);
	if (pos == -1)
	{
		if (language) cout << "��ǰĿ¼�в��������ļ���ɾ��ʧ��" << endl;
		else cout << "This file is not included in the current directory and the failure is deleted" << endl;
		return false;
	}

	if (myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		if (language) cout << "��û�и��ļ��еĲ���Ȩ��!" << endl;
		else  cout << "You don't have access to this folder!" << endl;
		return false;
	}

	list<int>::iterator p_list = myFileSystem.vector_folder[current_director_index].file_list.begin();
	while (p_list != myFileSystem.vector_folder[current_director_index].file_list.end())
	{
		int index = *p_list;
		if (index != -1 && myFileSystem.vector_file[index].file_name == file_name)
		{
			*p_list = -1;   // ��ʾΪ������
			ReleaseDataBlock(index);
			break;
		}
		p_list++;
	}

	//myFileSystem.vector_director[current_director.id] = current_director;  // ����Ŀ¼����
	//vector<file>::iterator p = myFileSystem.vector_file.begin();
	//p += pos;
	//(*p).id = -1;      //��ʾΪ������
	//myFileSystem.vector_file.erase(p);  // ���ļ�������ɾ��
	if (language) cout << "ɾ���ļ� " << file_name << " �ɹ�" << endl;
	else  cout << "Delete the file " << file_name << " success" << endl;
	return true;
}

bool open(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);
	if (pos == -1)
	{
		if (language) {
			cout << "��ǰĿ¼�в������ļ� " << file_name << endl;
			cout << "��ʧ�ܣ�" << endl;
		}
		else
		{
			cout << "There is no file in the current directory " << file_name << endl;
			cout << "Open the failure��" << endl;
		}
		return false;
	}

	if (myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		if (language)cout << "��û�и��ļ��Ĳ���Ȩ��!" << endl;
		else cout << "You do not have access to this file!" << endl;
		return false;
	}

	if (myFileSystem.vector_file[pos].file_length > SYSOPENFILE - memory_index)  // ʣ���ļ��鲻��װ��Ҫ�򿪵��ļ�
	{
		if (language)cout << "�ڴ�ռ䲻�㣬�޷����� " << file_name << " ����,��ر������ļ�" << endl;
		else cout << "Insufficient memory space, unable to read in " << file_name << " Please close useless files" << endl;
		return false;
	}


	if (IsInOpenFileList(pos) != open_file_list.end())   // ����Ƿ��Ѵ�
	{
		if (language)cout << "���ļ��Ѵ򿪣������ظ���" << endl;
		else cout << "This file has been opened. Do not open it again" << endl;
		return false;
	}

	openFile temp;
	temp.file_index = pos;
	temp.director_index = current_director_index;
	open_file_list.push_back(temp);       // ������ļ�����

	int block_pos = myFileSystem.vector_file[pos].beginning_in_dataArea;
	myFileSystem.vector_file[pos].begining_in_memory = memory_index; // �趨��ʼλ��
	dataBlock block;
	int count = 0;

	while (1)
	{
		if (block_pos != -1)
		{
			block = myFileSystem.dataArea[block_pos];
			if (language)cout << "�ڴ����:";
			else cout << "Memory read:";
			for (int i = 0; i<block.used; i++)    // �����ݿ����ݵ��ڴ�
			{
				count++;
				memory[memory_index][i] = block.content[i];
				cout << block.content[i];
			}
			memory_index++;
			cout << endl;
			block_pos = block.next;

		}
		else
		{
			break;
		}
	}
	if (language) {
		cout << "���ļ� " << file_name << " �ɹ�!" << endl;
		cout << "�������ڴ� " << count << " ���ֽ�" << endl;
	}
	else
	{
		cout << "Open the file " << file_name << " success!" << endl;
		cout << "Co-reading memory " << count << " bytes" << endl;
	}
	return true;

}

list<openFile> open_file_list;

list<openFile>::iterator IsInOpenFileList(int pos)   // pos�������ļ��Ƿ��ڴ��ļ�������
{
	list<openFile>::iterator p = open_file_list.begin();
	while (p != open_file_list.end())
	{
		int index = (*p).file_index;
		if (index == pos)
		{
			return p;
		}
		p++;
	}
	return p;
}

bool read(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);
	if (pos == -1)
	{
		if (language) {
			cout << "��ǰĿ¼������ " << file_name << " �ļ�" << endl;
			cout << "���ļ�ʧ�ܣ�" << endl;
		}
		else {
			cout << "The current directory does not exist " << file_name << " file" << endl;
			cout << "Failed to read file��" << endl;
		}

		return false;
	}

	if (IsInOpenFileList(pos) == open_file_list.end())   // ����ļ��Ƿ��Ѵ�
	{
		if (language) cout << "���ļ���δ�򿪣��޷���ȡ" << endl;
		else  cout << "The file is not open and cannot be read" << endl;
		return false;
	}

	int count = 0;
	file temp = myFileSystem.vector_file[pos];
	for (int i = temp.begining_in_memory; i <= temp.begining_in_memory + temp.file_length; i++)
	{
		for (int j = 0; j<BLOCKSIZE; j++)
		{
			if (memory[i][j] != '\0')
			{
				count++;
				cout << memory[i][j];
			}
			else
			{
				break;
			}

		}
	}
	cout << endl;
	if (language)cout << "������ " << count << " ���ֽ�" << endl;
	else cout << "A total of read " << count << " bytes" << endl;
	return true;

}

bool write(string file_name, string content)
{
	int pos = IsFileInCurrentDirector(file_name);
	if (pos == -1)
	{
		if (language) {
			cout << "��ǰĿ¼��û�� " << file_name << " �ļ�" << endl;
			cout << "д��ʧ��" << endl;
		}
		else
		{
			cout << "There is no current directory " << file_name << " file" << endl;
			cout << "Write failed" << endl;
		}
		return false;
	}

	if (content != "")  // д������ݲ���ʱ
	{
		int block_pos = myFileSystem.vector_file[pos].beginning_in_dataArea;
		dataBlock* block = &myFileSystem.dataArea[block_pos];
		while ((*block).next != -1)            // �ҵ����һ�����ݿ� ��ʼд����
		{
			block_pos = (*block).next;
			block = &myFileSystem.dataArea[block_pos];
		}


		int length = content.length(); //���ݻ�ʣ�ĳ���
		int used = 0;   //������д��ĳ���
		while (1)
		{
			if (BLOCKSIZE - (*block).used < length)     // ������һ�����ݿ��ʣ��ռ�С������
			{
				for (int i = used; i<BLOCKSIZE - (*block).used + used; i++)
				{
					(*block).content[(*block).used] = content[i];
					length--;
					used++;
					(*block).used++;

				}
				(*block).content[(*block).used] = '\0';
				block_pos = AllocDataBlock();
				(*block).next = block_pos;
				if (block_pos != -1)
				{
					block = &myFileSystem.dataArea[block_pos];  // �ٷ����ռ�
				}
				else
				{
					if (language)cout << "���̿ռ��������޷�д��" << endl;
					else cout << "Disk space is full, unable to write" << endl;
					return false;
				}

			}
			else
			{
				int i;
				for (i = (*block).used; i<(*block).used + length; i++)
				{
					(*block).content[i] = content[used++];

				}
				(*block).content[i] = '\0';
				(*block).used += length;
				if (language) {
					cout << "д��ɹ���" << "���� " << block_pos << " �����ݿ�д�� " << (*block).used << " �ֽ�" << endl;
				}
				else cout << "Write to successful��" << "Has been in " << block_pos << " datablock " << (*block).used << " bytes" << endl;
				return true;
			}

		}


	}
	if (language) cout << "д������Ϊ�գ�" << endl;
	else  cout << "The write content is empty��" << endl;
	return false;
}

bool wrmore(string file_name, string content, int time)  // ͬһ������д����
{
	bool flag = false;
	for (int i = 0; i<time; i++)
	{
		flag = write(file_name, content);
	}
	return flag;
}