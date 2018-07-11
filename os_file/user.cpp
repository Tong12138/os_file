#include "stdafx.h"
#include<fstream>

user CurU;

bool CheckUser(string name, string password) // �����û��Ƿ��ǳ�ʼ�����û�
{
	for (int i = 0; i<USERNUM; i++)
	{
		if (MFS.userinfo[i].name == name && MFS.userinfo[i].password == password)
		{
			return true;
		}

	}
	return false;
}//denglu

bool SignIn()    //��¼ģ��
{

	int chance = 5;
	string name;
	string password;
	while (chance > 0)
	{
		if (language) cout << "�������û���:";
		else cout << "USERNAME:";
		cin >> name;
		if (language)cout << "���������룺";
		else cout << "PASSWORD:";
		cin >> password;
		if (CheckUser(name, password))
		{
			CurU.name = name;
			CurU.password = password;
			return true;
		}
		else
		{
			if (language)cout << "�û������������������ " << --chance << " �λ���" << endl;
			else cout << "User name or password error, you have " << --chance << " more chances" << endl;
			print();
		}
	}
	return false;


}//denglu




 /* �����ʽ
 1. vector_director�ĸ���
 2.vector_director������
 3.FSV�ĸ���
 4.FSV������
 5.userinfo����
 6.vacant����  �����С����
 7.super_stack����
 8.data_area����
 */



 /*�����ʽ
 1.int id
 2.char* name
 3.char* owner
 4.int father
 5.int director��Ŀ
 6.int DV
 7.int file��Ŀ
 8.int FV
 */
bool SaveVectorDirector(FILE* fd)  //����Ŀ¼��Ϣ
{
	vector<folder>::iterator p = MFS.DSV.begin();//����һ����������ָ���һ��Ԫ��

	while (p != MFS.DSV.end())
	{
		int director_num = (*p).DV.size();
		int file_num = (*p).FV.size();

		fprintf(fd, "%d\n%s\n%s\n%d\n%d\n%s\n", (*p).id, (*p).name.c_str(), (*p).owner.c_str(), (*p).father, director_num, (*p).time.c_str());

		vector<int>::iterator p_list = (*p).DV.begin();  // д��DV
		while (p_list != (*p).DV.end())
		{
			fprintf(fd, "%d\n", (*p_list));
			p_list++;
		}

		fprintf(fd, "%d\n", file_num);
		p_list = (*p).FV.begin();          // д��FV
		while (p_list != (*p).FV.end())
		{
			fprintf(fd, "%d\n", (*p_list));
			p_list++;
		}

		p++;
	}
	//cout<<"����Ŀ¼��Ϣ�ɹ�"<<endl;
	return true;
}



/*�����ʽ
1.int id
2.char* filename
3.int blockpos
4.char* owner
5.int filelength
6.int beginning_in_memory
*/
bool SaveVectorFile(FILE* fd)  // �����ļ���Ϣ
{
	vector<file>::iterator p = MFS.FSV.begin();
	while (p != MFS.FSV.end())
	{
		fprintf(fd, "%d\n%s\n%d\n%s\n%d\n%d\n%s\n", (*p).id, (*p).filename.c_str(), (*p).blockpos, (*p).owner.c_str(), (*p).filelength, (*p).memorypos, (*p).time.c_str());
		p++;
	}
	//cout<<"�����ļ���Ϣ�ɹ�"<<endl;
	return true;
}

bool SaveUserInfo(FILE* fd)  // �����û���Ϣ
{

	for (int i = 0; i<UCount; i++)
	{
		user temp = MFS.userinfo[i];
		fprintf(fd, "%s\n%s\n", temp.name.c_str(), temp.password.c_str());
	}
	//cout<<"�����û���Ϣ�ɹ�"<<endl;
	return true;
}



bool SaveFreeList(FILE* fd)  //���������
{
	for (int i = 0; i<GROUPNUM; i++)
	{
		for (int j = 0; j<GROUPSIZE; j++)
		{
			fprintf(fd, "%d\n", MFS.vacant[i][j]);
		}
	}
	//cout<<"����������ɹ�"<<endl;
	return true;
}



/*
1. int NextFreeG;   // ��һ��Ҫʹ�õ�����  0~GROUPNUM-1
2. int StackNum;     // ����ջ�п���ʹ�õĿ���
3. int ջ������ ����
*/

bool SaveSuperStack(FILE* fd)  // ���泬��ջ
{
	stack<int> temp;
	fprintf(fd, "%d\n%d\n", NextFreeG, StackNum);
	while (!MFS.superStack.empty())   // �����ݱ��浽��һ��ջ�У����򱣴棬�������ص�ʱ��˳��Ŷ�
	{
		int top = MFS.superStack.top();
		temp.push(top);
		MFS.superStack.pop();
	}
	while (!temp.empty())
	{
		fprintf(fd, "%d\n", temp.top());
		temp.pop();
	}
	//cout<<"���泬��ջ�ɹ�"<<endl;
	return true;
}



//�����ʽ  int is_null  int next  int used  char* content
bool SaveDataArea(FILE* fd) //��������������
{
	for (int i = 0; i<BLOCKNUM; i++)
	{
		int is_null = 1;    // ������ǣ�1��ʾ�����ǿգ�0��ʾ�ǿ�
		dataBlock temp = MFS.dataArea[i];
		if (temp.content[0] != '\0')       // ����ǿգ����ϱ��
		{
			is_null = 0;
		}
		fprintf(fd, "%d\n%d\n%d\n", is_null, temp.next, temp.used);
		if (is_null == 0)    //�ǿյİ����ݴ���
		{
			fprintf(fd, "%s\n", temp.content);
		}
	}
	//cout<<"�������������ݳɹ�"<<endl;
	return true;
}

bool SignOut()
{
	FILE* out;
	if (fopen_s(&out, guide.c_str(), "w+") != 0) {

	}
	fprintf(out, "%s\n", path.c_str());
	fclose(out);
	FILE* fd;
	try
	{
		if (fopen_s(&fd, path.c_str(), "w+") != 0)
		{
			if (language) cout << "���ļ� " << path << " ʧ�ܣ��޷�����" << endl;
			else  cout << "Open the file " << path << " failure, unable to save" << endl;
			return false;
		}
		fprintf(fd, "%d\n\n", language);
		fprintf(fd, "%d\n\n", UCount);
		int director_num = MFS.DSV.size();
		int file_num = MFS.FSV.size();
		fprintf(fd, "%d\n", director_num);
		SaveVectorDirector(fd);      //д��vector_director����
		fprintf(fd, "\n%d\n", file_num);
		SaveVectorFile(fd);
		fprintf(fd, "\n");
		SaveUserInfo(fd);
		fprintf(fd, "\n");
		SaveFreeList(fd);
		fprintf(fd, "\n");
		SaveSuperStack(fd);
		fprintf(fd, "\n");
		SaveDataArea(fd);
		//language = 0;
		//fprintf(fd, "%d\n", language);
	}
	catch (const std::exception&)
	{
		if (language) {
			cout << "����ʧ��" << endl;
		}
		else cout << "save up failed" << endl;
	}
	if (language) {
		cout << "�ļ�ϵͳ����ɹ�!" << endl;
	}
	else cout << "save up success" << endl;
	print();
	fclose(fd);

	return true;
}

