#include"stdafx.h"
#include <stdio.h>
#include<fstream>
#include<direct.h>
// ����˳����� ����ĸ�ʽ
const int BUFF_LENGTH = 513;
char change[BUFF_LENGTH];
int error = 0;

bool LoadVectorDirector(FILE* fd, int director_num)  //����Ŀ¼��Ϣ
{

	for (int i = 0; i<director_num; i++)
	{
		folder temp;
		fscanf_s(fd, "%d%s", &temp.id, change, BUFF_LENGTH);
		temp.name = change;
		fscanf_s(fd, "%s", change, BUFF_LENGTH);   //��Ŀ¼ownerΪempty
		temp.owner = change;
		fscanf_s(fd, "%d", &temp.father);   //��Ŀ¼�ϼ�Ϊ-1
		int direcotor_count;
		fscanf_s(fd, "%d", &direcotor_count);   //Ŀ¼��
		fscanf_s(fd, "%s", change, BUFF_LENGTH);
		temp.time = change;
		while (direcotor_count--)       // ���������Ŀ¼����
		{
			int dirpos;
			fscanf_s(fd, "%d", &dirpos);
			temp.DV.push_back(dirpos);
		}
		int file_count;
		fscanf_s(fd, "%d", &file_count);
		while (file_count--)              // ����������ļ�����
		{
			int filepos;
			fscanf_s(fd, "%d", &filepos);
			temp.FV.push_back(filepos);
		}
		MFS.DSV.push_back(temp);
	}
	//cout<<"����Ŀ¼��Ϣ�ɹ���"<<endl;
	return true;
}


bool LoadVectorFile(FILE* fd, int file_num)  //�����ļ���Ϣ
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
	//cout<<"�����ļ���Ϣ�ɹ�!"<<endl;
	return true;
}



bool LoadUserInfo(FILE* fd)    // �����û���Ϣ
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


bool LoadFreeList(FILE* fd)   // ���س�����
{
	for (int i = 0; i<GROUPNUM; i++)
	{
		for (int j = 0; j<GROUPSIZE; j++)
		{
			fscanf_s(fd, "%d", &MFS.vacant[i][j]);
			//cout<<"������"<<MFS.vacant[i][j]<<endl;
		}
	}
	//cout<<"���س�������Ϣ�ɹ�!"<<endl;
	return true;
}

bool LoadSuperStack(FILE* fd)  // ���س���ջ��Ϣ
{
	fscanf_s(fd, "%d %d", &NextFreeG, &StackNum);
	int temp = StackNum;
	while (temp--)
	{
		int value;
		fscanf_s(fd, "%d", &value);
		MFS.superStack.push(value);
	}
	//cout<<"���س���ջ��Ϣ�ɹ�!"<<endl;
	return true;
}


bool LoadDataArea(FILE* fd)  //������������Ϣ
{
	for (int i = 0; i<BLOCKNUM; i++)
	{
		int is_null;
		fscanf_s(fd, "%d", &is_null);
		try
		{
			dataBlock* temp = (dataBlock*)malloc(sizeof(dataBlock));
			if (temp == NULL) {
				if (language) cout << "�ڴ�������" << endl;
				else  cout << "Memory allocation error" << endl;
				return false;
			}
			fscanf_s(fd, "%d%d", &(*temp).next, &(*temp).used);
			if (is_null == 0)    // ������ݲ��գ��������
			{
				fscanf_s(fd, "\n%[^\n]", change, BUFF_LENGTH);
				strcpy_s((*temp).content, change);
			}
			else  // ���ݿ���ֱ�Ӹ�ֵ
			{
				for (int j = 0; j<BLOCKNUM + 1; j++)
				{
					(*temp).content[j] = '\0';
				}
			}
			//cout<<"����"<<change<<endl;
			MFS.dataArea.push_back(*temp);
		}
		catch (const std::exception&)
		{
			if (language)cout << "�����ļ�ϵͳ�ɹ�" << endl;
			else cout << "LOAD ERROR!!!" << endl;
		}

	}
	//cout<<"������������Ϣ�ɹ�!"<<endl;
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
		return false;//δ�����ļ�ϵͳ����false
	}
	try          //�����ļ�ϵͳ
	{
		fscanf_s(fd, "%d", &language);
		fscanf_s(fd, "%d", &UCount);
		Initialize_Memory();
		int director_num;
		fscanf_s(fd, "%d", &director_num);
		LoadVectorDirector(fd, director_num);       //��������Ŀ¼��Ϣ
		int file_num;
		fscanf_s(fd, "%d", &file_num);
		LoadVectorFile(fd, file_num);          //���������ļ���Ϣ
		LoadUserInfo(fd);
		LoadFreeList(fd);
		LoadSuperStack(fd);
		LoadDataArea(fd);
		CurD = 0;
		memory_index = 0;

		if (language)cout << "�����ļ�ϵͳ�ɹ�!" << endl;
		else cout << "LOAD FILESYSTEM SUCCESS!" << endl;
	}
	catch (const std::exception&)
	{
		if (language)cout << "�����ļ�ϵͳʧ��!" << endl;
		else cout << "LOAD ERROR!" << endl;
	}

	fclose(fd);
	print();
	return true;
}