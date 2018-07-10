#include "stdafx.h"

void IntoSuperStack()  // free数组进入超级栈
{
	for (int i = 0; i<GROUPSIZE; i++) // 成组链中每组个数
	{
		int param = myFileSystem.free_list[next_free_list_index][i];
		// 成组链数组  使用的时候从小到大   被使用了置成-1
		// 下一组要使用的组数  0~GROUPNUM-1 next_free_list_index
		myFileSystem.superStack.push(param);
		myFileSystem.free_list[next_free_list_index][i] = -1;  //正在用的那组置为-1
	}

	super_stack_number = GROUPSIZE;

	if (next_free_list_index < GROUPNUM)  // 如果没到最后一块就+1
	{
		next_free_list_index++;
	}

}
/*
void OutSuperStack()  // 从超级栈进入free数组
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
int AllocDataBlock()   //分配数据块
{
	if (myFileSystem.superStack.empty())
	{
		IntoSuperStack();   // 从free组进入超级栈
	}
	int result = myFileSystem.superStack.top();
	myFileSystem.superStack.pop();
	super_stack_number--;
	return result;

}



void IntoFreeArray()   // 当superstack满了时，进入freeArray
{
	next_free_list_index--;
	int index = GROUPSIZE - 1;           // 从栈顶开始，数组从大到小分配
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
	if (super_stack_number >= GROUPSIZE)  // 当superstack满了时，进入freeArray
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
		if (language)cout << "释放了 " << temp << " 号数据块" << endl;
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