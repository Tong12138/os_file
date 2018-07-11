#include "stdafx.h"
int includefile(string filename)   // 判断一文件名是否存在于当前目录的子文件中  若存在返回对应索引号 不存在返回-1
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

int includedir(string filename)  // 判断一文件名是否存在的当前目录的子目录中
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

bool IsDataAreaFull()   // 判断数据域是否已满
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

bool create(string filename)         // 创建文件
{
	if (includefile(filename) != -1)
	{
		if (language) {
			cout << "本目录中已存在名为 " << filename << " 的文件" << endl;
			cout << "文件创建失败" << endl;
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
			cout << "本目录中已存在名为 " << filename << " 的文件夹" << endl;
			cout << "文件夹创建失败" << endl;
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
		if (language) cout << "数据域已满，没有足够空间创建文件" << endl;
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
	if (language) cout << "该文件被分配的数据块号是: " << temp.blockpos << endl;
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
		if (language)cout << "当前目录不存在 " << filename << " 文件" << endl;
		else cout << "The current directory does not exist " << filename << " file" << endl;
		if (language)cout << "读文件失败！" << endl;
		else cout << "read file failed" << endl;
		return false;
	}

	list<openFile>::iterator open_file_p = IsInOpenFileList(pos);
	if (open_file_p == open_FV.end())   // 检查文件是否已打开
	{
		if (language)cout << "该文件还未打开，无法关闭" << endl;
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
	open_FV.erase(open_file_p);   //从打开链表中删除
	if (language) cout << "关闭文件 " << filename << " 成功" << endl;
	else cout << "close the file: " << filename << " success" << endl;
	return true;

}

bool delfile(string filename) //删除文件
{

	int pos = includefile(filename);
	if (pos == -1)
	{
		if (language) cout << "当前目录中不包含该文件，删除失败" << endl;
		else cout << "This file is not included in the current directory and the failure is deleted" << endl;
		return false;
	}

	if (MFS.FSV[pos].owner != CurU.name && MFS.FSV[pos].owner != "empty")
	{
		if (language) cout << "您没有该文件夹的操作权限!" << endl;
		else  cout << "You don't have access to this folder!" << endl;
		return false;
	}

	vector<int>::iterator p_list = MFS.DSV[CurD].FV.begin();
	while (p_list != MFS.DSV[CurD].FV.end())
	{
		int index = *p_list;
		if (index != -1 && MFS.FSV[index].filename == filename)
		{
			*p_list = -1;   // 标示为不可用
			release(index);
			break;
		}
		p_list++;
	}

	//MFS.vector_director[current_director.id] = current_director;  // 更新目录索引
	//vector<file>::iterator p = MFS.FSV.begin();
	//p += pos;
	//(*p).id = -1;      //标示为不可用
	//MFS.FSV.erase(p);  // 从文件索引中删除
	if (language) cout << "删除文件 " << filename << " 成功" << endl;
	else  cout << "Delete the file " << filename << " success" << endl;
	return true;
}

bool open(string filename)
{
	int pos = includefile(filename);
	if (pos == -1)
	{
		if (language) {
			cout << "当前目录中不存在文件 " << filename << endl;
			cout << "打开失败！" << endl;
		}
		else
		{
			cout << "There is no file in the current directory " << filename << endl;
			cout << "Open the failure！" << endl;
		}
		return false;
	}

	if (MFS.FSV[pos].owner != CurU.name && MFS.FSV[pos].owner != "empty")
	{
		if (language)cout << "您没有该文件的操作权限!" << endl;
		else cout << "You do not have access to this file!" << endl;
		return false;
	}

	if (MFS.FSV[pos].filelength > SYSOPENFILE - memory_index)  // 剩余文件块不够装载要打开的文件
	{
		if (language)cout << "内存空间不足，无法读入 " << filename << " 内容,请关闭无用文件" << endl;
		else cout << "Insufficient memory space, unable to read in " << filename << " Please close useless files" << endl;
		return false;
	}


	if (IsInOpenFileList(pos) != open_FV.end())   // 检查是否已打开
	{
		if (language)cout << "本文件已打开，请勿重复打开" << endl;
		else cout << "This file has been opened. Do not open it again" << endl;
		return false;
	}

	openFile temp;
	temp.filepos = pos;
	temp.dirpos = CurD;
	open_FV.push_back(temp);       // 加入打开文件链表

	int block_pos = MFS.FSV[pos].blockpos;
	MFS.FSV[pos].memorypos = memory_index; // 设定起始位置
	dataBlock block;
	int count = 0;

	while (1)
	{
		if (block_pos != -1)
		{
			block = MFS.dataArea[block_pos];
			if (language)cout << "内存读入:";
			else cout << "Memory read:";
			for (int i = 0; i<block.used; i++)    // 读数据块内容到内存
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
		cout << "打开文件 " << filename << " 成功!" << endl;
		cout << "共读入内存 " << count << " 个字节" << endl;
	}
	else
	{
		cout << "Open the file " << filename << " success!" << endl;
		cout << "Co-reading memory " << count << " bytes" << endl;
	}
	return true;

}

list<openFile> open_FV;

list<openFile>::iterator IsInOpenFileList(int pos)   // pos索引的文件是否在打开文件链表中
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
			cout << "当前目录不存在 " << filename << " 文件" << endl;
			cout << "读文件失败！" << endl;
		}
		else {
			cout << "The current directory does not exist " << filename << " file" << endl;
			cout << "Failed to read file！" << endl;
		}

		return false;
	}

	if (IsInOpenFileList(pos) == open_FV.end())   // 检查文件是否已打开
	{
		if (language) cout << "该文件还未打开，无法读取" << endl;
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
	if (language)cout << "共读入 " << count << " 个字节" << endl;
	else cout << "A total of read " << count << " bytes" << endl;
	return true;

}

bool write(string filename, string content)
{
	int pos = includefile(filename);
	if (pos == -1)
	{
		if (language) {
			cout << "当前目录中没有 " << filename << " 文件" << endl;
			cout << "写入失败" << endl;
		}
		else
		{
			cout << "There is no current directory " << filename << " file" << endl;
			cout << "Write failed" << endl;
		}
		return false;
	}

	if (content != "")  // 写入的内容不空时
	{
		int block_pos = MFS.FSV[pos].blockpos;
		dataBlock* block = &MFS.dataArea[block_pos];
		while ((*block).next != -1)            // 找到最后一块数据块 开始写内容
		{
			block_pos = (*block).next;
			block = &MFS.dataArea[block_pos];
		}


		int length = content.length(); //内容还剩的长度
		int used = 0;   //内容已写入的长度
		while (1)
		{
			if (BLOCKSIZE - (*block).used < length)     // 如果最后一块数据块的剩余空间小于内容
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
					block = &MFS.dataArea[block_pos];  // 再分配块空间
				}
				else
				{
					if (language)cout << "磁盘空间已满，无法写入" << endl;
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
					cout << "写入成功！" << "已在 " << block_pos << " 号数据块写入 " << (*block).used << " 字节" << endl;
				}
				else cout << "Write to successful！" << "Has been in " << block_pos << " datablock " << (*block).used << " bytes" << endl;
				return true;
			}

		}


	}
	if (language) cout << "写入内容为空！" << endl;
	else  cout << "The write content is empty！" << endl;
	return false;
}

bool wrmore(string filename, string content, int time)  // 同一份内容写入多次
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
			cout << "当前目录不存在 " << filename1 << " 文件" << endl;
			cout << "读文件失败！" << endl;
		}
		else {
			cout << "The current directory does not exist " << filename1 << " file" << endl;
			cout << "Failed to read file！" << endl;
		}

		return false;
	}
	int pos2 = includefile(filename2);
	if (pos2 == -1)
	{
		if (language) {
			cout << "当前目录不存在 " << filename2 << " 文件" << endl;
			cout << "读文件失败！" << endl;
		}
		else {
			cout << "The current directory does not exist " << filename2 << " file" << endl;
			cout << "Failed to read file！" << endl;
		}

		return false;
	}
	if (IsInOpenFileList(pos1) == open_FV.end())   // 检查文件是否已打开
	{
		if (language) cout << filename1<<"还未打开，无法读取" << endl;
		else  cout << filename1<<" is not open and cannot be read" << endl;
		return false;
	}
	if (IsInOpenFileList(pos2) == open_FV.end())   // 检查文件是否已打开
	{
		if (language) cout << filename2 << "该文件还未打开，无法读取" << endl;
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
	//cout << "读完了"<<endl;
	//cout << endl;
	//cout << file1<<endl;
	//cout << file2<<endl;
	if (file1 == file2)
	{
		if (language)cout << "两个文件内容相同 " << endl;
		else cout << "The content is same " << endl;
	}
	else
	{
		if (language)cout << "两个文件内容不同 " << endl;
		else cout << "The content is not same " << endl;
	}

	return true;
}