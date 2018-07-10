#include "stdafx.h"

void IntoSuperStack()  // free������볬��ջ
{
	for (int i = 0; i<GROUPSIZE; i++) // ��������ÿ�����
	{
		int param = myFileSystem.free_list[next_free_list_index][i];
		// ����������  ʹ�õ�ʱ���С����   ��ʹ�����ó�-1
		// ��һ��Ҫʹ�õ�����  0~GROUPNUM-1 next_free_list_index
		myFileSystem.superStack.push(param);
		myFileSystem.free_list[next_free_list_index][i] = -1;  //�����õ�������Ϊ-1
	}

	super_stack_number = GROUPSIZE;

	if (next_free_list_index < GROUPNUM)  // ���û�����һ���+1
	{
		next_free_list_index++;
	}

}
/*
void OutSuperStack()  // �ӳ���ջ����free����
{
super_stack_number = 0;
int index=0;
while(!myFileSystem.superStack.empty())
{
int param = myFileSystem.superStack.top();
myFileSystem.free_list[next_free_list_index-1][index] = param;
myFileSystem.superStack.pop();
}

next_free_list_index--;
}
*/
int AllocDataBlock()   //�������ݿ�
{
	if (myFileSystem.superStack.empty())
	{
		IntoSuperStack();   // ��free����볬��ջ
	}
	int result = myFileSystem.superStack.top();
	myFileSystem.superStack.pop();
	super_stack_number--;
	return result;

}



void IntoFreeArray()   // ��superstack����ʱ������freeArray
{
	next_free_list_index--;
	int index = GROUPSIZE - 1;           // ��ջ����ʼ������Ӵ�С����
	while (!myFileSystem.superStack.empty())
	{
		int temp = myFileSystem.superStack.top();
		myFileSystem.free_list[next_free_list_index][index] = temp;
		myFileSystem.superStack.pop();
		index--;
	}
	super_stack_number = 0;
}

void IntoSuperStack(int id)
{
	myFileSystem.dataArea[id].next = -1;
	myFileSystem.dataArea[id].used = 0;
	myFileSystem.dataArea[id].content[0] = '\0';
	myFileSystem.superStack.push(id);
	super_stack_number++;
	if (super_stack_number >= GROUPSIZE)  // ��superstack����ʱ������freeArray
	{
		IntoFreeArray();
	}
}



void ReleaseDataBlock(int index)
{
	int temp = myFileSystem.vector_file[index].firstpos;
	dataBlock block = myFileSystem.dataArea[temp];
	while (1)
	{
		IntoSuperStack(temp);
		if (language)cout << "�ͷ��� " << temp << " �����ݿ�" << endl;
		else cout << "release " << temp << " datablock" << endl;
		if (block.next != -1)
		{
			temp = block.next;
			block = myFileSystem.dataArea[block.next];
		}
		else
		{
			return;
		}

	}
	{
		IntoSuperStack(temp);
		block = myFileSystem.dataArea[block.next];
	}while (block.next != -1);
}