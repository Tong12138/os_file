#include "stdafx.h"

void IntoSuperStack()  // free������볬��ջ
{
	for (int i = 0; i<GROUPSIZE; i++) // ��������ÿ�����
	{
		int cmd = MFS.vacant[NextFreeG][i];
		// ����������  ʹ�õ�ʱ���С����   ��ʹ�����ó�-1
		// ��һ��Ҫʹ�õ�����  0~GROUPNUM-1 NextFreeG
		MFS.superStack.push(cmd);
		MFS.vacant[NextFreeG][i] = -1;  //�����õ�������Ϊ-1
	}

	StackNum = GROUPSIZE;

	if (NextFreeG < GROUPNUM)  // ���û�����һ���+1
	{
		NextFreeG++;
	}

}
/*
void OutSuperStack()  // �ӳ���ջ����free����
{
StackNum = 0;
int index=0;
while(!MFS.superStack.empty())
{
int cmd = MFS.superStack.top();
MFS.vacant[NextFreeG-1][index] = cmd;
MFS.superStack.pop();
}

NextFreeG--;
}
*/
int allocate()   //�������ݿ�
{
	if (MFS.superStack.empty())
	{
		IntoSuperStack();   // ��free����볬��ջ
	}
	int result = MFS.superStack.top();
	MFS.superStack.pop();
	StackNum--;
	return result;

}



void IntoFreeArray()   // ��superstack����ʱ������freeArray
{
	NextFreeG--;
	int index = GROUPSIZE - 1;           // ��ջ����ʼ������Ӵ�С����
	while (!MFS.superStack.empty())
	{
		int temp = MFS.superStack.top();
		MFS.vacant[NextFreeG][index] = temp;
		MFS.superStack.pop();
		index--;
	}
	StackNum = 0;
}

void IntoSuperStack(int id)
{
	MFS.dataArea[id].next = -1;
	MFS.dataArea[id].used = 0;
	MFS.dataArea[id].content[0] = '\0';
	MFS.superStack.push(id);
	StackNum++;
	if (StackNum >= GROUPSIZE)  // ��superstack����ʱ������freeArray
	{
		IntoFreeArray();
	}
}



void release(int index)
{
	int temp = MFS.FSV[index].blockpos;
	dataBlock block = MFS.dataArea[temp];
	while (1)
	{
		IntoSuperStack(temp);
		if (language)cout << "�ͷ��� " << temp << " �����ݿ�" << endl;
		else cout << "release " << temp << " datablock" << endl;
		if (block.next != -1)
		{
			temp = block.next;
			block = MFS.dataArea[block.next];
		}
		else
		{
			return;
		}

	}
	{
		IntoSuperStack(temp);
		block = MFS.dataArea[block.next];
	}while (block.next != -1);
}