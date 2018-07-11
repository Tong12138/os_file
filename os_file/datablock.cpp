#include "stdafx.h"

void IntoSuperStack()  // free数组进入超级栈
{
	for (int i = 0; i<GROUPSIZE; i++) // 成组链中每组个数
	{
		int cmd = MFS.vacant[NextFreeG][i];
		// 成组链数组  使用的时候从小到大   被使用了置成-1
		// 下一组要使用的组数  0~GROUPNUM-1 NextFreeG
		MFS.superStack.push(cmd);
		MFS.vacant[NextFreeG][i] = -1;  //正在用的那组置为-1
	}

	StackNum = GROUPSIZE;

	if (NextFreeG < GROUPNUM)  // 如果没到最后一块就+1
	{
		NextFreeG++;
	}

}
/*
void OutSuperStack()  // 从超级栈进入free数组
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
int allocate()   //分配数据块
{
	if (MFS.superStack.empty())
	{
		IntoSuperStack();   // 从free组进入超级栈
	}
	int result = MFS.superStack.top();
	MFS.superStack.pop();
	StackNum--;
	return result;

}



void IntoFreeArray()   // 当superstack满了时，进入freeArray
{
	NextFreeG--;
	int index = GROUPSIZE - 1;           // 从栈顶开始，数组从大到小分配
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
	if (StackNum >= GROUPSIZE)  // 当superstack满了时，进入freeArray
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
		if (language)cout << "释放了 " << temp << " 号数据块" << endl;
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