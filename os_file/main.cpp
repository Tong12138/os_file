#include"stdafx.h"
int language = 0;

void print()
{
	cout << endl;
}

void errorprint(string get) {
	if (language)cout << '\'' << get << '\'' << "�����ڲ����ⲿ���Ҳ���ǿ����еĳ���" << endl << "���������ļ�" << endl;
	else cout << '\'' << get << '\'' << "It is not an internal or external command, nor an executable program" << endl << "or batch file" << endl;
}

void MainPage()   // ��ҳ��Ϣ
{
	if (language == 1) {
		cout << "--------------------------Command list-----------------------------\n";
		cout << "DIR                            �鿴����Ŀ¼���ļ�\n";
		cout << "MKDIR <OP>                     ������Ŀ¼\n";
		cout << "RMDIR <OP>                     ɾ��Ŀ¼\n";
		cout << "CD <OP>                        ����Ŀ¼\n";
		cout << "FORMAT <OP>                    ��ʽ���ļ���\n";

		cout << "CREATE <OP>                    �����ļ�\n";
		cout << "DEL <OP>                       ɾ���ļ�\n";
		cout << "CLOSE <OP>                     �ر��ļ�\n";
		cout << "OPEN <OP FILE>                 ���ļ�\n";
		cout << "READ <OP>                      ���ļ�\n";
		cout << "WRITE FILE_NAME CONTENT        д�ļ�\n";
		cout << "WRMORE FILE_NAME CONTENT TIME  ��ͬ����д����\n";
		cout << "RENAME OLD_NAME NEW_NAME       ������\n";
		cout << "COPY NAME DES_DIRECTOR_NAME    �����ļ�\n";

		cout << "INITI                          ��ʽ���ļ�ϵͳ\n";
		cout << "HELP                           ����\n";
		cout << "CHOOSEL                        ѡ������\n";
		cout << "LOGOUT                         �ǳ�ϵͳ\n";
		cout<<"CLS                              ����\n";
		//cout << "COLOR                        �޸���ɫ\n";
		//cout << "COMP                         �Ƚ��ļ�����\n";
		cout << "TIME                           ��ʾ��ǰʱ��\n";
		cout << "DU <NAME>                        ɾ���û�\n";


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
		cout << "TIME                           ��ʾ��ǰʱ��\n";
		cout << "DU <NAME>                        ɾ���û�\n";


	}
}

void Currecdector()   // ��ʾ��ǰĿ¼
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
		if (language)cout << "��¼�ɹ�����ӭ��," << CurU.name << endl;
		else cout << "Login success, welcome you," << CurU.name << endl;
	}
	else
	{
		if (language) {
			cout << "��������ε�¼ʧ�ܣ���ϵͳ�Զ��ر�" << endl;
			cout << "��������˳�" << endl;
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
		Currecdector();   // ��ʾ��ǰĿ¼
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
		bool initi(string director_name);  // ��ʽ���ļ���
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
		while (1)    // ���˵�ʣ��ָ��
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

void read() {//����Ա������ע���˻�
	if (language) {
		cout << "--------------------------command list-----------------------------\n";
		cout << "register                       ע���û�\n";
		cout << "logout                         ����Աע��\n";
		cout << "help                           ������Ϣ\n";
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
		if (language) cout << "ע�������Ѵ�˸�����ֹ����ע�ᡣ" << endl;
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
		if (language)cout << "ɾ���ɹ�:";
		else cout << "Delete Successful:";
		//MFS.userinfo[UCount++] = add;
	}
	else
	{
		if (language)cout << "��û��ɾ�����û���Ȩ��:";
		else cout << "Delete Warning! no priviledge:";
	}
	return;
}

bool rootok() {
	while (true)
	{

		if (language)cout << "������ָ��" << endl;
		else cout << "Please input instruction:";
		string ins;
		cin >> ins;
		if ((ins == "register") || (ins == "REGISTER")) {
			string user_name;
			if (language)cout << "�������û���:";
			else cout << "Please enter the username:";
			cin >> user_name;
			string user_password;
			if (language)cout << "����������:";
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
		else cout << "����ָ�����������" << endl;
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
		if (language)cout << "���������Ա��Ȩ��" << endl;
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
		if (language)cout << "�����������������,�㻹�� " << --no << " �λ���" << endl;
		else cout << "Enter the error, please re-enter, you still have " << --no << " second chance" << endl;;
	}
	if (language)cout << "��������ѳ�����Σ���ǿ���˳�ϵͳ" << endl;
	else cout << "The input error has been exceeded five times and the system will be forced out" << endl;
	SignOut();
	return;
}