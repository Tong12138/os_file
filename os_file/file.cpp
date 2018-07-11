#include "stdafx.h"
int includefile(string filename)   // �ж�һ�ļ����Ƿ�����ڵ�ǰĿ¼�����ļ���  �����ڷ��ض�Ӧ������ �����ڷ���-1
{
	vector<int>::iterator p = MFS.DSV[CurD].FV.begin();
	while (p != MFS.DSV[CurD].FV.end())
	{
		int index = *p;
		if (index != -1 && MFS.FSV[index].filename == filename)
		{

			return index;
		}
		p++;
	}

	return -1;
}

int includedir(string filename)  // �ж�һ�ļ����Ƿ���ڵĵ�ǰĿ¼����Ŀ¼��
{
	bool flag = false;
	vector<int>::iterator p;

	p = MFS.DSV[CurD].DV.begin();
	while (p != MFS.DSV[CurD].DV.end())
	{
		int index = *p;
		if (index != -1 && MFS.DSV[index].name == filename)
		{

			return index;
		}
		p++;
	}
	return -1;
}

bool IsDataAreaFull()   // �ж��������Ƿ�����
{
	if (MFS.superStack.empty() && MFS.vacant[GROUPNUM - 1][0] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool create(string filename)         // �����ļ�
{
	if (includefile(filename) != -1)
	{
		if (language) {
			cout << "��Ŀ¼���Ѵ�����Ϊ " << filename << " ���ļ�" << endl;
			cout << "�ļ�����ʧ��" << endl;
		}
		else
		{
			cout << "There is already a name in this directory " << filename << " file" << endl;
			cout << "Failed file creation" << endl;
		}
		return false;
	}

	if (includedir(filename) != -1)
	{
		if (language) {
			cout << "��Ŀ¼���Ѵ�����Ϊ " << filename << " ���ļ���" << endl;
			cout << "�ļ��д���ʧ��" << endl;
		}
		else
		{
			cout << "There is already a name in this directory " << filename << " folder" << endl;
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
	temp.id = MFS.FSV.size();
	temp.filelength = 1;
	temp.owner = CurU.name;
	temp.filename = filename;
	temp.memorypos = 0;
	temp.time = gettime();
	temp.blockpos = allocate();
	if (language) cout << "���ļ�����������ݿ����: " << temp.blockpos << endl;
	else  cout << "The data block number that the file is assigned is: " << temp.blockpos << endl;
	MFS.FSV.push_back(temp);
	MFS.DSV[CurD].FV.push_back(temp.id);
	return true;
}

bool close(string filename)
{
	int pos = includefile(filename);

	if (pos == -1)
	{
		if (language)cout << "��ǰĿ¼������ " << filename << " �ļ�" << endl;
		else cout << "The current directory does not exist " << filename << " file" << endl;
		if (language)cout << "���ļ�ʧ�ܣ�" << endl;
		else cout << "read file failed" << endl;
		return false;
	}

	list<openFile>::iterator open_file_p = IsInOpenFileList(pos);
	if (open_file_p == open_FV.end())   // ����ļ��Ƿ��Ѵ�
	{
		if (language)cout << "���ļ���δ�򿪣��޷��ر�" << endl;
		else cout << "The file is not open and cannot be closed" << endl;
		return false;
	}

	file temp = MFS.FSV[pos];
	for (int i = temp.memorypos; i <= temp.memorypos + temp.filelength; i++)
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
	open_FV.erase(open_file_p);   //�Ӵ�������ɾ��
	if (language) cout << "�ر��ļ� " << filename << " �ɹ�" << endl;
	else cout << "close the file: " << filename << " success" << endl;
	return true;

}

bool delfile(string filename) //ɾ���ļ�
{

	int pos = includefile(filename);
	if (pos == -1)
	{
		if (language) cout << "��ǰĿ¼�в��������ļ���ɾ��ʧ��" << endl;
		else cout << "This file is not included in the current directory and the failure is deleted" << endl;
		return false;
	}

	if (MFS.FSV[pos].owner != CurU.name && MFS.FSV[pos].owner != "empty")
	{
		if (language) cout << "��û�и��ļ��еĲ���Ȩ��!" << endl;
		else  cout << "You don't have access to this folder!" << endl;
		return false;
	}

	vector<int>::iterator p_list = MFS.DSV[CurD].FV.begin();
	while (p_list != MFS.DSV[CurD].FV.end())
	{
		int index = *p_list;
		if (index != -1 && MFS.FSV[index].filename == filename)
		{
			*p_list = -1;   // ��ʾΪ������
			release(index);
			break;
		}
		p_list++;
	}

	//MFS.vector_director[current_director.id] = current_director;  // ����Ŀ¼����
	//vector<file>::iterator p = MFS.FSV.begin();
	//p += pos;
	//(*p).id = -1;      //��ʾΪ������
	//MFS.FSV.erase(p);  // ���ļ�������ɾ��
	if (language) cout << "ɾ���ļ� " << filename << " �ɹ�" << endl;
	else  cout << "Delete the file " << filename << " success" << endl;
	return true;
}

bool open(string filename)
{
	int pos = includefile(filename);
	if (pos == -1)
	{
		if (language) {
			cout << "��ǰĿ¼�в������ļ� " << filename << endl;
			cout << "��ʧ�ܣ�" << endl;
		}
		else
		{
			cout << "There is no file in the current directory " << filename << endl;
			cout << "Open the failure��" << endl;
		}
		return false;
	}

	if (MFS.FSV[pos].owner != CurU.name && MFS.FSV[pos].owner != "empty")
	{
		if (language)cout << "��û�и��ļ��Ĳ���Ȩ��!" << endl;
		else cout << "You do not have access to this file!" << endl;
		return false;
	}

	if (MFS.FSV[pos].filelength > SYSOPENFILE - memory_index)  // ʣ���ļ��鲻��װ��Ҫ�򿪵��ļ�
	{
		if (language)cout << "�ڴ�ռ䲻�㣬�޷����� " << filename << " ����,��ر������ļ�" << endl;
		else cout << "Insufficient memory space, unable to read in " << filename << " Please close useless files" << endl;
		return false;
	}


	if (IsInOpenFileList(pos) != open_FV.end())   // ����Ƿ��Ѵ�
	{
		if (language)cout << "���ļ��Ѵ򿪣������ظ���" << endl;
		else cout << "This file has been opened. Do not open it again" << endl;
		return false;
	}

	openFile temp;
	temp.filepos = pos;
	temp.dirpos = CurD;
	open_FV.push_back(temp);       // ������ļ�����

	int block_pos = MFS.FSV[pos].blockpos;
	MFS.FSV[pos].memorypos = memory_index; // �趨��ʼλ��
	dataBlock block;
	int count = 0;

	while (1)
	{
		if (block_pos != -1)
		{
			block = MFS.dataArea[block_pos];
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
		cout << "���ļ� " << filename << " �ɹ�!" << endl;
		cout << "�������ڴ� " << count << " ���ֽ�" << endl;
	}
	else
	{
		cout << "Open the file " << filename << " success!" << endl;
		cout << "Co-reading memory " << count << " bytes" << endl;
	}
	return true;

}

list<openFile> open_FV;

list<openFile>::iterator IsInOpenFileList(int pos)   // pos�������ļ��Ƿ��ڴ��ļ�������
{
	list<openFile>::iterator p = open_FV.begin();
	while (p != open_FV.end())
	{
		int index = (*p).filepos;
		if (index == pos)
		{
			return p;
		}
		p++;
	}
	return p;
}

bool read(string filename)
{
	int pos = includefile(filename);
	if (pos == -1)
	{
		if (language) {
			cout << "��ǰĿ¼������ " << filename << " �ļ�" << endl;
			cout << "���ļ�ʧ�ܣ�" << endl;
		}
		else {
			cout << "The current directory does not exist " << filename << " file" << endl;
			cout << "Failed to read file��" << endl;
		}

		return false;
	}

	if (IsInOpenFileList(pos) == open_FV.end())   // ����ļ��Ƿ��Ѵ�
	{
		if (language) cout << "���ļ���δ�򿪣��޷���ȡ" << endl;
		else  cout << "The file is not open and cannot be read" << endl;
		return false;
	}

	int count = 0;
	file temp = MFS.FSV[pos];
	for (int i = temp.memorypos; i <= temp.memorypos + temp.filelength; i++)
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

bool write(string filename, string content)
{
	int pos = includefile(filename);
	if (pos == -1)
	{
		if (language) {
			cout << "��ǰĿ¼��û�� " << filename << " �ļ�" << endl;
			cout << "д��ʧ��" << endl;
		}
		else
		{
			cout << "There is no current directory " << filename << " file" << endl;
			cout << "Write failed" << endl;
		}
		return false;
	}

	if (content != "")  // д������ݲ���ʱ
	{
		int block_pos = MFS.FSV[pos].blockpos;
		dataBlock* block = &MFS.dataArea[block_pos];
		while ((*block).next != -1)            // �ҵ����һ�����ݿ� ��ʼд����
		{
			block_pos = (*block).next;
			block = &MFS.dataArea[block_pos];
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
				block_pos = allocate();
				(*block).next = block_pos;
				if (block_pos != -1)
				{
					block = &MFS.dataArea[block_pos];  // �ٷ����ռ�
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

bool wrmore(string filename, string content, int time)  // ͬһ������д����
{
	bool flag = false;
	for (int i = 0; i<time; i++)
	{
		flag = write(filename, content);
	}
	return flag;
}

bool same(string filename1, string filename2)
{
	int pos1 = includefile(filename1);
	if (pos1 == -1)
	{
		if (language) {
			cout << "��ǰĿ¼������ " << filename1 << " �ļ�" << endl;
			cout << "���ļ�ʧ�ܣ�" << endl;
		}
		else {
			cout << "The current directory does not exist " << filename1 << " file" << endl;
			cout << "Failed to read file��" << endl;
		}

		return false;
	}
	int pos2 = includefile(filename2);
	if (pos2 == -1)
	{
		if (language) {
			cout << "��ǰĿ¼������ " << filename2 << " �ļ�" << endl;
			cout << "���ļ�ʧ�ܣ�" << endl;
		}
		else {
			cout << "The current directory does not exist " << filename2 << " file" << endl;
			cout << "Failed to read file��" << endl;
		}

		return false;
	}
	if (IsInOpenFileList(pos1) == open_FV.end())   // ����ļ��Ƿ��Ѵ�
	{
		if (language) cout << filename1<<"��δ�򿪣��޷���ȡ" << endl;
		else  cout << filename1<<" is not open and cannot be read" << endl;
		return false;
	}
	if (IsInOpenFileList(pos2) == open_FV.end())   // ����ļ��Ƿ��Ѵ�
	{
		if (language) cout << filename2 << "���ļ���δ�򿪣��޷���ȡ" << endl;
		else  cout << filename1 << " is not open and cannot be read" << endl;
		return false;
	}
	int count = 0;
	file temp1 = MFS.FSV[pos1];
	string file1="",file2="";
	for (int i = temp1.memorypos; i <= temp1.memorypos + temp1.filelength; i++)
	{
		for (int j = 0; j<BLOCKSIZE; j++)
		{
			if (memory[i][j] != '\0')
			{
				count++;
				file1+= memory[i][j];
			}
			else
			{
				break;
			}

		}
	}
	file temp2 = MFS.FSV[pos2];
	for (int i = temp2.memorypos; i <= temp2.memorypos + temp2.filelength; i++)
	{
		for (int j = 0; j<BLOCKSIZE; j++)
		{
			if (memory[i][j] != '\0')
			{
				count++;
				file2 += memory[i][j];
			}
			else
			{
				break;
			}

		}
	}
	//cout << "������"<<endl;
	//cout << endl;
	//cout << file1<<endl;
	//cout << file2<<endl;
	if (file1 == file2)
	{
		if (language)cout << "�����ļ�������ͬ " << endl;
		else cout << "The content is same " << endl;
	}
	else
	{
		if (language)cout << "�����ļ����ݲ�ͬ " << endl;
		else cout << "The content is not same " << endl;
	}

	return true;
}