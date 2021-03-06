// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件
#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <string>
#include <windows.h> 

using namespace std;

#define BLOCKSIZE  512 // 数据块内容大小
#define BLOCKNUM  512  // 数据块数目
#define GROUPSIZE  BLOCKSIZE / sizeof(int)     // 成组链中每组个数
#define GROUPNUM  sizeof(int)		//  成组链组数，可以认为基本为4.
#define SYSOPENFILE  35      // 允许的最大文件长度，即占数据块的最大数目
#define USERNUM  8           // 最大用户数



extern string path;//根目录，存放虚拟文件系统存储文件
const string guide = "guide.txt";//根目录索引文件
extern int UCount;//当前用户数量

typedef struct file {
	int id;                // 文件索引号
	string filename;      // 文件名
	int    blockpos;     // 在数据域中的第一个位置
	string owner;          // 文件所有者的名字
	int    filelength;    // 文件所占数据块块数
	int memorypos;     // 在内存中的第一个位置
	string time;//产生或修改时间
}file;

typedef struct folder {
	int id;                // 目录索引号
	string name;			// 目录名
	vector<int> FV;   // 本目录中的文件链表
	vector<int> DV;  // 本目录中的文件夹链表
	string owner;           // 文件夹拥有者
	int father;   // 上一级目录        // 根目录的上一级 设为 -1
	string time;//产生或修改时间
}folder;

typedef struct dataBlock {   //数据块
	int used;      // 已使用的空间
	int next;      // 下一个数据块
	char content[BLOCKSIZE + 1];  // 数据块内容 最后一位放'\0'
}dataBlock;

typedef struct user {
	string name;
	string password;
}user;

typedef struct {//打开的文件
	int filepos;  // 文件索引
	int dirpos;  // 目录索引
}openFile;

typedef struct fileSystem {      //文件系统
	vector<dataBlock> dataArea;     // 数据域
	stack<int>        superStack;   // 超级栈
	int vacant[GROUPNUM][GROUPSIZE];  // 成组链数组  使用的时候从小到大   被使用了置成-1
														  //  即，从vacant[0][127]开始，用到freelist[0][0]，用完再vacant[1][127]。。。。最后是vacant[3][0]
	user userinfo[USERNUM];     // 用户信息
	vector<folder> DSV;    // 存放所有目录信息
	vector<file> FSV;            // 存放所有文件信息
}fileSystem;

extern string rp;//根目录路径
extern int lan;
extern int language;//语言选择项，为0为英文，为1为中文
extern file CurF;         // 当前打开的文件
extern int NextFreeG;   // 下一组要使用的组数  0~GROUPNUM-1
extern int StackNum;     // 超级栈中可以使用的块数

extern int CurD;  // 当前目录的索引
extern user CurU;           // 当前登录的用户
extern char memory[SYSOPENFILE][BLOCKSIZE];         // 内存
extern int memory_index;          // 可用内存索引,即开始的位置
extern fileSystem MFS;     // 文件系统
									//extern string  path;    // 于硬盘中的根路径
extern list<openFile> open_FV;   // 打开的文件链表

extern string gettime();//获取当前系统时间
extern void language_change();//语言改变
extern void root();//管理员
extern bool Initialize();      // 初始化文件系统
extern bool SignIn();           // 登录模块
extern void print();   // 画分割线
extern void mkdir(string folder_name);   // 新建目录
extern void dir();      // 显示该目录下内容
extern bool cd(string folder_name);  // 前往下一级目录
extern void ltdir();  // 前往上一级目录
extern int allocate();  // 分配数据块 
extern void release(int index);  // 释放数据块
extern bool create(string filename); //创建文件
extern bool delfile(string filename);  // 删除文件
extern bool deldir(string folder_name); //删除目录
extern int includefile(string filename);  // 判断文件是否在当前目录中      返回文件索引号
extern int includedir(string filename); // 判断文件是否存在于当前目录中  返回目录索引号
extern list<openFile>::iterator IsInOpenFileList(int pos);      // 判断文件是否已打开
extern bool write(string filename, string content);     // 向文件写入内容
extern bool wrmore(string filename, string content, int time);     //向文件写入同一内容多次
extern bool open(string filename);          // 打开文件，将文件内容读到内存
extern bool read(string filename);   // 从内存中将文件内容读出来
extern bool close(string filename);  // 将打开的文件关闭
extern bool SignOut();              // 退出系统，保存已有信息
extern bool Load(char* s);              // 载入保存的信息
extern void Initialize_Memory();   //初始化内存
extern bool rename(string old_name, string new_name);       //重命名
extern bool copy(string name, string path);   // 复制
extern bool same(string name1, string name2);
extern void deleteuser(string name);