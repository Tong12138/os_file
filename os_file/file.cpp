#include "stdafx.h"
int IsFileInCurrentDirector(string filename)   // 判断一文件名是否存在于当前目录的子文件中  若存在返回对应索引号 不存在返回-1
{
	vector<int>::iterator p = myFileSystem.vector_folder[current_director_index].FV.begin();
	while (p != myFileSystem.vector_folder[current_director_index].FV.end())
	{
		int index = *p;
		if (index != -1 && myFileSystem.vector_file[index].filename == filename)
		{

			return index;
		}
		p++;
	}

	return -1;
}

int IsDirectorInCurrentDirector(string filename)  // 判断一文件名是否存在的当前目录的子目录中
{
	bool flag = false;
	vector<int>::iterator p;

	p = myFileSystem.vector_folder[current_director_index].DV.begin();
	while (p != myFileSystem.vector_folder[current_director_index].DV.end())
	{
		int index = *p;
		if (index != -1 && myFileSystem.vector_folder[index].name == filename)
		{

			return index;
		}
		p++;
	}
	return -1;
}

bool IsDataAreaFull()   // 判断数据域是否已满
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

bool create(string filename)         // 创建文件
{
	if (IsFileInCurrentDirector(filename) != -1)
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

	if (IsDirectorInCurrentDirector(filename) != -1)
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
	temp.id = myFileSystem.vector_file.size();
	temp.file_length = 1;
	temp.owner = current_user.name;
	temp.filename = filename;
	temp.begining_in_memory = 0;
	temp.time = gettime();
	temp.firstpos = AllocDataBlock();
	if (language) cout << "该文件被分配的数据块号是: " << temp.firstpos << endl;
	else  cout << "The data block number that the file is assigned is: " << temp.firstpos << endl;
	myFileSystem.vector_file.push_back(temp);
	myFileSystem.vector_folder[current_director_index].FV.push_back(temp.id);
	return true;
}

bool close(string filename)
{
	int pos = IsFileInCurrentDirector(filename);

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
	open_FV.erase(open_file_p);   //从打开链表中删除
	if (language) cout << "关闭文件 " << filename << " 成功" << endl;
	else cout << "close the file: " << filename << " success" << endl;
	return true;

}

bool delfile(string filename) //删除文件
{

	int pos = IsFileInCurrentDirector(filename);
	if (pos == -1)
	{
		if (language) cout << "当前目录中不包含该文件，删除失败" << endl;
		else cout << "This file is not included in the current directory and the failure is deleted" << endl;
		return false;
	}

	if (myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		if (language) cout << "您没有该文件夹的操作权限!" << endl;
		else  cout << "You don't have access to this folder!" << endl;
		return false;
	}

	vector<int>::iterator p_list = myFileSystem.vector_folder[current_director_index].FV.begin();
	while (p_list != myFileSystem.vector_folder[current_director_index].FV.end())
	{
		int index = *p_list;
		if (index != -1 && myFileSystem.vector_file[index].filename == filename)
		{
			*p_list = -1;   // 标示为不可用
			ReleaseDataBlock(index);
			break;
		}
		p_list++;
	}

	//myFileSystem.vector_director[current_director.id] = current_director;  // 更新目录索引
	//vector<file>::iterator p = myFileSystem.vector_file.begin();
	//p += pos;
	//(*p).id = -1;      //标示为不可用
	//myFileSystem.vector_file.erase(p);  // 从文件索引中删除
	if (language) cout << "删除文件 " << filename << " 成功" << endl;
	else  cout << "Delete the file " << filename << " success" << endl;
	return true;
}

bool open(string filename)
{
	int pos = IsFileInCurrentDirector(filename);
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

	if (myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		if (language)cout << "您没有该文件的操作权限!" << endl;
		else cout << "You do not have access to this file!" << endl;
		return false;
	}

	if (myFileSystem.vector_file[pos].file_length > SYSOPENFILE - memory_index)  // 剩余文件块不够装载要打开的文件
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
	temp.file_index = pos;
	temp.director_index = current_director_index;
	open_FV.push_back(temp);       // 加入打开文件链表

	int block_pos = myFileSystem.vector_file[pos].firstpos;
	myFileSystem.vector_file[pos].begining_in_memory = memory_index; // 设定起始位置
	dataBlock block;
	int count = 0;

	while (1)
	{
		if (block_pos != -1)
		{
			block = myFileSystem.dataArea[block_pos];
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
		int index = (*p).file_index;
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
	int pos = IsFileInCurrentDirector(filename);
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
	if (language)cout << "共读入 " << count << " 个字节" << endl;
	else cout << "A total of read " << count << " bytes" << endl;
	return true;

}

bool write(string filename, string content)
{
	int pos = IsFileInCurrentDirector(filename);
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
		int block_pos = myFileSystem.vector_file[pos].firstpos;
		dataBlock* block = &myFileSystem.dataArea[block_pos];
		while ((*block).next != -1)            // 找到最后一块数据块 开始写内容
		{
			block_pos = (*block).next;
			block = &myFileSystem.dataArea[block_pos];
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
				block_pos = AllocDataBlock();
				(*block).next = block_pos;
				if (block_pos != -1)
				{
					block = &myFileSystem.dataArea[block_pos];  // 再分配块空间
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