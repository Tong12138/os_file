#include"stdafx.h"
#include <stdio.h>
#include<fstream>
#include<direct.h>
// 加载顺序参照 保存的格式
const int BUFF_LENGTH = 513;
char change[BUFF_LENGTH];
int error = 0;

bool LoadVectorDirector(FILE* fd, int director_num)  //加载目录信息
{

	for (int i = 0; i<director_num; i++)
	{
		folder temp;
		fscanf_s(fd, "%d%s", &temp.id, change, BUFF_LENGTH);
		temp.name = change;
		fscanf_s(fd, "%s", change, BUFF_LENGTH);   //根目录owner为empty
		temp.owner = change;
		fscanf_s(fd, "%d", &temp.father);   //根目录上级为-1
		int direcotor_count;
		fscanf_s(fd, "%d", &direcotor_count);   //目录数
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		temp.time = change;
		while (direcotor_count--)       // 载入包含的目录内容
		{
			int dirpos;
			fscanf_s(fd, "%d", &dirpos);
			temp.DV.push_back(dirpos);
		}
		int file_count;
		fscanf_s(fd, "%d", &file_count);
		while (file_count--)              // 载入包含的文件内容
		{
			int filepos;
			fscanf_s(fd, "%d", &filepos);
			temp.FV.push_back(filepos);
		}
		MFS.DSV.push_back(temp);
	}
	//cout<<"加载目录信息成功！"<<endl;
	return true;
}


bool LoadVectorFile(FILE* fd, int file_num)  //加载文件信息
{
	while (file_num--)
	{
		file temp;
		fscanf_s(fd, "%d%s", &temp.id, change, BUFF_LENGTH);
		temp.filename = change;
		fscanf_s(fd, "%d%s", &temp.blockpos, change, BUFF_LENGTH);
		temp.owner = change;
		fscanf_s(fd, "%d%d", &temp.filelength, &temp.memorypos);
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		temp.time = change;
		MFS.FSV.push_back(temp);
	}
	//cout<<"加载文件信息成功!"<<endl;
	return true;
}



bool LoadUserInfo(FILE* fd)    // 加载用户信息
{
	for (int i = 0; i<UCount; i++)
	{
		user* temp = &MFS.userinfo[i];
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		(*temp).name = change;
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		(*temp).password = change;
	}
	return true;
}


bool LoadFreeList(FILE* fd)   // 加载成组链
{
	for (int i = 0; i<GROUPNUM; i++)
	{
		for (int j = 0; j<GROUPSIZE; j++)
		{
			fscanf_s(fd, "%d", &MFS.vacant[i][j]);
			//cout<<"读入了"<<MFS.vacant[i][j]<<endl;
		}
	}
	//cout<<"加载成组链信息成功!"<<endl;
	return true;
}

bool LoadSuperStack(FILE* fd)  // 加载超级栈信息
{
	fscanf_s(fd, "%d %d", &NextFreeG, &StackNum);
	int temp = StackNum;
	while (temp--)
	{
		int value;
		fscanf_s(fd, "%d", &value);
		MFS.superStack.push(value);
	}
	//cout<<"加载超级栈信息成功!"<<endl;
	return true;
}


bool LoadDataArea(FILE* fd)  //加载数据域信息
{
	for (int i = 0; i<BLOCKNUM; i++)
	{
		int is_null;
		fscanf_s(fd, "%d", &is_null);
		try
		{
			dataBlock* temp = (dataBlock*)malloc(sizeof(dataBlock));
			if (temp == NULL) {
				if (language) cout << "内存分配出错" << endl;
				else  cout << "Memory allocation error" << endl;
				return false;
			}
			fscanf_s(fd, "%d%d", &(*temp).next, &(*temp).used);
			if (is_null == 0)    // 如果内容不空，则读出来
			{
				fscanf_s(fd, "\n%[^\n]", change, BUFF_LENGTH);
				strcpy_s((*temp).content, change);
			}
			else  // 内容空则直接赋值
			{
				for (int j = 0; j<BLOCKNUM + 1; j++)
				{
					(*temp).content[j] = '\0';
				}
			}
			//cout<<"内容"<<change<<endl;
			MFS.dataArea.push_back(*temp);
		}
		catch (const std::exception&)
		{
			if (language)cout << "加载文件系统成功" << endl;
			else cout << "LOAD ERROR!!!" << endl;
		}

	}
	//cout<<"加载数据域信息成功!"<<endl;
	return true;
}

/*void Initializerp() {

}*/

bool Load(char *s)
{
	string text;
	//fstream in;
	//in.open(guide, ios::in | ios::out | ios::binary);
	//in >> path;
	//in.close();
	FILE* fd;
	char buff[80];
	_getcwd(buff, 80);
	strcat_s(buff, "\\");
	strcat_s(buff, s);
	string buffer = buff;
	//buffer = "D:\MyFileSystem\yyt.txt";
	if (fopen_s(&fd, buffer.c_str(), "r") != 0)
	{
		return false;//未创建文件系统返回false
	}
	try          //已有文件系统
	{
		fscanf_s(fd, "%d", &language);
		fscanf_s(fd, "%d", &UCount);
		Initialize_Memory();
		int director_num;
		fscanf_s(fd, "%d", &director_num);
		LoadVectorDirector(fd, director_num);       //加载所有目录信息
		int file_num;
		fscanf_s(fd, "%d", &file_num);
		LoadVectorFile(fd, file_num);          //加载所有文件信息
		LoadUserInfo(fd);
		LoadFreeList(fd);
		LoadSuperStack(fd);
		LoadDataArea(fd);
		CurD = 0;
		memory_index = 0;

		if (language)cout << "加载文件系统成功!" << endl;
		else cout << "LOAD FILESYSTEM SUCCESS!" << endl;
	}
	catch (const std::exception&)
	{
		if (language)cout << "加载文件系统失败!" << endl;
		else cout << "LOAD ERROR!" << endl;
	}

	fclose(fd);
	print();
	return true;
}