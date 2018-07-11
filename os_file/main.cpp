#include"stdafx.h"
int language = 0;

void print()
{
	cout << endl;
}

void errorprint(string get) {
	if (language)cout << '\'' << get << '\'' << "不是内部或外部命令，也不是可运行的程序" << endl << "或批处理文件" << endl;
	else cout << '\'' << get << '\'' << "It is not an internal or external command, nor an executable program" << endl << "or batch file" << endl;
}

void MainPage()   // 主页信息
{
	if (language == 1) {
		cout << "--------------------------Command list-----------------------------\n";
		cout << "DIR                            查看所有目录和文件\n";
		cout << "MKDIR <OP>                     创建新目录\n";
		cout << "RMDIR <OP>                     删除目录\n";
		cout << "CD <OP>                        进入目录\n";
		cout << "FORMAT <OP>                    格式化文件夹\n";

		cout << "CREATE <OP>                    创建文件\n";
		cout << "DEL <OP>                       删除文件\n";
		cout << "CLOSE <OP>                     关闭文件\n";
		cout << "OPEN <OP FILE>                 打开文件\n";
		cout << "READ <OP>                      读文件\n";
		cout << "WRITE FILE_NAME CONTENT        写文件\n";
		cout << "WRMORE FILE_NAME CONTENT TIME  相同内容写入多次\n";
		cout << "RENAME OLD_NAME NEW_NAME       重命名\n";
		cout << "COPY NAME DES_DIRECTOR_NAME    复制文件\n";

		cout << "INITI                          格式化文件系统\n";
		cout << "HELP                           帮助\n";
		cout << "CHOOSEL                        选择语言\n";
		cout << "LOGOUT                         登出系统\n";
		cout<<"CLS                              清屏\n";
		//cout << "COLOR                        修改颜色\n";
		//cout << "COMP                         比较文件内容\n";
		cout << "TIME                           显示当前时间\n";
		cout << "DU <NAME>                        删除用户\n";


	}
	else
	{
		cout << "--------------------------Command list-----------------------------\n";
		cout << "DIR                            Show all file and folder in current index\n";
		cout << "MKDIR <OP>                     Create new director\n";
		cout << "RMDIR <OP>                     Delete folder\n";
		cout << "CD <OP>                        Open director\n";
		cout << "FORMAT <OP>                    Format folder\n";

		cout << "CREATE <OP>                    Create new file\n";
		cout << "DEL <OP>                       Delete file\n";
		cout << "CLOSE <OP>                     Close the file\n";
		cout << "OPEN <OP FILE>                 Open file\n";
		cout << "READ <OP>                      Read file\n";
		cout << "WRITE FILE_NAME CONTENT        Write specific file\n";
		cout << "WRMORE FILE_NAME CONTENT TIME  Write the same content to a file multiple times\n";
		cout << "RENAME OLD_NAME NEW_NAME       Rename\n";
		cout << "COPY NAME DES_DIRECTOR_NAME    Copy files to specified directory (absolute path)\n";

		cout << "INITI                          Format current filesystem\n";
		cout << "HELP                           Help message\n";
		cout << "CHOOSEL                        Change the language\n";
		cout << "LOGOUT                         Save and logout\n";
		cout << "CLS                            clear\n";
		cout << "TIME                           显示当前时间\n";
		cout << "DU <NAME>                        删除用户\n";


	}
}

void Currecdector()   // 显示当前目录
{
	stack<int> temp;
	folder temp_director = MFS.DSV[CurD];
	while (temp_director.father != -1)
	{
		temp.push(temp_director.id);
		temp_director = MFS.DSV[temp_director.father];
	}
	temp.push(temp_director.id);
	while (!temp.empty())
	{
		int index = temp.top();
		cout << MFS.DSV[index].name << ">";
		temp.pop();
	}
	//cout<<"$";
}

void main(int argc,char* argv[])
{
	//Initializerp();
	string command;
	char ch;
	cout << "Microsoft Windows[version 10.0.16299.431]" << endl << "(c) 2017 Microsoft Copreration.All rights reserved" << endl << endl;

	while (1)
	{
		if (Load(argv[1])) {
			break;
		}
		else {
			Initialize();
			break;
		}
		print();
	}

	if (SignIn())
	{
		system("cls");
		cout << "Microsoft Windows[version 10.0.16299.431]" << endl << "(c) 2017 Microsoft Copreration.All rights reserved" << endl << endl;
		if (language)cout << "登录成功，欢迎您," << CurU.name << endl;
		else cout << "Login success, welcome you," << CurU.name << endl;
	}
	else
	{
		if (language) {
			cout << "由于您多次登录失败，本系统自动关闭" << endl;
			cout << "按任意键退出" << endl;
		}
		else
		{
			cout << "This system will automatically closed because you failed multiple logins" << endl;
			cout << "Press any key to exit" << endl;
		}
		system("pause");
		exit(0);
	}

	while (true)
	{

		print();
		Currecdector();   // 显示当前目录
		cin >> command;
		string cmd;
		if ((command == "cmp") || (command == "CMP"))
		{
			cin >>cmd ;
			string file2;
			cin >> file2;
			same(cmd, file2);
			continue;
		}
		if ((command == "mkdir") || (command == "MKDIR"))
		{
			cin >> cmd;
			mkdir(cmd);
			continue;
		}
		if ((command == "choosel") || (command == "CHOOSEL")) {
			language_change();
			continue;
		}
		if ((command == "du") || (command == "DU"))
		{
			cin >> cmd;
			deleteuser(cmd);
			continue;
		}
		if ((command == "dir") || (command == "DIR"))
		{
			dir();
			continue;
		}
		if ((command == "cd") || (command == "CD"))
		{
			cin >> cmd;
			if(cmd!="..")
			cd(cmd);
			else
			ltdir();
			continue;
		}
		if ((command == "time") || (command == "TIME"))
		{
			string cur_time = gettime();
			cout << cur_time << endl;
			continue;
		}
		if ((command == "create") || (command == "CREATE"))
		{
			cin >> cmd;
			create(cmd);
			continue;
		}
		if ((command == "del") || (command == "DEL"))
		{
			cin >> cmd;
			delfile(cmd);
			continue;
		}
		if ((command == "rmdir") || (command == "RMDIR"))
		{
			cin >> cmd;
			deldir(cmd);
			continue;
		}
		if ((command == "write") || (command == "WRITE"))
		{
			cin >> cmd;
			string temp;
			//	cin>>temp;
			cin.get();
			getline(std::cin, temp);
			write(cmd, temp);
			continue;
		}
		if ((command == "wrmore") || (command == "WRMORE"))
		{
			cin >> cmd;
			string temp_1;

			//cin>>temp_1;
			cin.get();
			getline(std::cin, temp_1);
			int temp_2;
			cin >> temp_2;
			wrmore(cmd, temp_1, temp_2);
			continue;
		}
		if ((command == "open") || (command == "OPEN"))
		{
			cin >> cmd;
			open(cmd);
			continue;
		}
		if ((command == "read") || (command == "READ"))
		{
			cin >> cmd;
			read(cmd);
			continue;
		}
		if ((command == "close") || (command == "CLOSE"))
		{
			cin >> cmd;
			close(cmd);
			continue;
		}
		if ((command == "logout") || (command == "LOGOUT"))
		{
			SignOut();
			system("pause");
			exit(0);
		}
		bool initi(string director_name);  // 格式化文件夹
		if ((command == "format") || (command == "FORMAT"))
		{
			Initialize();
			continue;
		}
		if ((command == "rename") || (command == "RENAME"))
		{
			cin >> cmd;
			string str;
			cin >> str;

			rename(cmd, str);
			continue;
		}
		if ((command == "ini") || (command == "INI"))
		{
			cin >> cmd;
			initi(cmd);
			continue;
		}
		if ((command == "copy") || (command == "COPY"))
		{
			cin >> cmd;
			string str;
			cin >> str;
			copy(cmd, str);
			continue;
		}
		if ((command == "help") || (command == "HELP")) {
			MainPage();
			continue;
		}
		if ((command == "root") || (command == "ROOT")) {
			root();
			continue;
		}
		if ((command == "cls") || (command == "CLS"))
		{
			system("cls");
			continue;
		}
		errorprint(command);
		while (1)    // 过滤掉剩余指令
		{
			char ch;
			ch = getchar();
			if (ch == '\n')
			{
				break;
			}
		}
	}

	system("pause");
}

void read() {//管理员，设置注册账户
	if (language) {
		cout << "--------------------------command list-----------------------------\n";
		cout << "register                       注册用户\n";
		cout << "logout                         管理员注销\n";
		cout << "help                           帮助信息\n";
	}
	else
	{
		cout << "--------------------------command list-----------------------------\n";
		cout << "REGISTER                       Registered users\n";
		cout << "LOGOUT                         Administrator cancellation\n";
		cout << "HELP                           Help message\n";
	}
}

void reg(string name, string password) {
	if (UCount == 8) {
		if (language) cout << "注册人数已达八个，禁止继续注册。" << endl;
		else cout << "The number of registered people has reached eight, and the registration is prohibited." << endl;
		print();
		return;
	}
	user add;
	add.name = name;
	add.password = password;
	MFS.userinfo[UCount++] = add;
}

void deleteuser(string name) {
	user add;
	add.name = name;
	if (CurU.name == "root")
	{
		for (int i = 0; i < 8; i++)
		{
			if (name == MFS.userinfo[i].name)
			{
				for (i; i < 7; i++)
				{
					MFS.userinfo[i].name = MFS.userinfo[i].name;
					MFS.userinfo[i].password = MFS.userinfo[i].password;
					
					
				}
				
			}
		}
		UCount--;
		if (language)cout << "删除成功:";
		else cout << "Delete Successful:";
		//MFS.userinfo[UCount++] = add;
	}
	else
	{
		if (language)cout << "您没有删除该用户的权限:";
		else cout << "Delete Warning! no priviledge:";
	}
	return;
}

bool rootok() {
	while (true)
	{

		if (language)cout << "请输入指令" << endl;
		else cout << "Please input instruction:";
		string ins;
		cin >> ins;
		if ((ins == "register") || (ins == "REGISTER")) {
			string user_name;
			if (language)cout << "请输入用户名:";
			else cout << "Please enter the username:";
			cin >> user_name;
			string user_password;
			if (language)cout << "请输入密码:";
			else cout << "Please enter your password:";
			cin >> user_password;
			reg(user_name, user_password);
			continue;
		}
		if ((ins == "LOGOUT") || (ins == "logout")) {
			return true;
		}
		if ((ins == "help") || (ins == "HELP")) {
			read();
			continue;
		}
		system("cls");
		cout << "Microsoft Windows[version 10.0.16299.431]" << endl << "(c) 2017 Microsoft Copreration.All rights reserved" << endl << endl;
		if (language)cout << "Error instruction, please re-enter" << endl;
		else cout << "错误指令，请重新输入" << endl;
	}
	return false;
}

void root() {
	system("cls");
	cout << "Microsoft Windows[version 10.0.16299.431]" << endl << "(c) 2017 Microsoft Copreration.All rights reserved" << endl << endl;
	print();
	int key;

	int no = 5;
	while (no > 0) {
		if (language)cout << "请输入管理员授权码" << endl;
		else cout << "Please enter the administrator authorization code" << endl;
		cin >> key;
		if (key == 123456) {
			read();
			if (rootok())
				return;
			else continue;
			continue;
		}
		system("cls");
		cout << "Microsoft Windows[version 10.0.16299.431]" << endl << "(c) 2017 Microsoft Copreration.All rights reserved" << endl << endl;
		print();
		if (language)cout << "输入错误，请重新输入,你还有 " << --no << " 次机会" << endl;
		else cout << "Enter the error, please re-enter, you still have " << --no << " second chance" << endl;;
	}
	if (language)cout << "输入错误已超过五次，将强制退出系统" << endl;
	else cout << "The input error has been exceeded five times and the system will be forced out" << endl;
	SignOut();
	return;
}