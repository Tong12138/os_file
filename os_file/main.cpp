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
		cout << "--------------------------������ ����-----------------------------\n";
		cout << "close file_name                �ر��ļ�\n";
		cout << "copy name des_director_name    �����ļ���ָ��Ŀ¼������·����\n";
		cout << "create file_name               �����ļ�\n";
		cout << "deldir director_name           ɾ���ļ���\n";
		cout << "delfile file_name              ɾ���ļ�\n";
		cout << "dir                          ��ʾ��ǰĿ¼�е���Ŀ¼���ļ�\n";
		cout << "initi                          ��ʽ���ļ�ϵͳ\n";
		cout << "ini director_name              ��ʽ���ļ���\n";
		cout << "logout                         ���������˳�ϵͳ\n";
		cout << "ltdir                        ������һ��Ŀ¼\n";
		cout << "mkdir director_name            ����Ŀ¼\n";
		cout << "ntdir director_name          ������һ��Ŀ¼\n";
		cout << "open file_name                 ���ļ�\n";
		cout << "read file_name                 ���ļ�\n";
		cout << "rename old_name new_name     ������\n";
		cout << "write file_name content        д�ļ�\n";
		cout << "wrmore file_name content time  ���ļ�д��ͬһ���ݶ��\n";
		cout << "help                         ������Ϣ\n";
		cout << "lan_choose                   change the language\n";
	}
	else
	{
		cout << "--------------------------Command list-----------------------------\n";
		cout << "CLOSE <OP>                     Close the file\n";
		cout << "COPY NAME DES_DIRECTOR_NAME    Copy files to specified directory (absolute path)\n";
		cout << "CREATE <OP>                    Create new file\n";
		cout << "DELDIR <OP>                    Delete folder\n";
		cout << "DELFILE <OP>                   Delete file\n";
		cout << "DIR                            Show all file and folder in current index\n";
		cout << "INITI                          Format current filesystem\n";
		cout << "INI <OP>                       Format folder\n";
		cout << "LOGOUT                         Save and logout\n";
		cout << "LTDIR                          Return to the previous level directory\n";
		cout << "MKDIR <OP>                     Create new director\n";
		cout << "NTDIR <OP>                     Open director\n";
		cout << "OPEN <OP FILE>                 Open file\n";
		cout << "READ <OP>                      Read file\n";
		cout << "RENAME OLD_NAME NEW_NAME       Rename\n";
		cout << "WRITE FILE_NAME CONTENT        Write specific file\n";
		cout << "WRMORE FILE_NAME CONTENT TIME  Write the same content to a file multiple times\n";
		cout << "HELP                           Help message\n";
		cout << "LAN_CHOOSE                     Change the language\n";
	}
}

void CurrentDirector()   // ��ʾ��ǰĿ¼
{
	stack<int> temp;
	folder temp_director = myFileSystem.vector_folder[current_director_index];
	while (temp_director.last_director != -1)
	{
		temp.push(temp_director.id);
		temp_director = myFileSystem.vector_folder[temp_director.last_director];
	}
	temp.push(temp_director.id);
	while (!temp.empty())
	{
		int index = temp.top();
		cout << myFileSystem.vector_folder[index].name << ">";
		temp.pop();
	}
	//cout<<"$";
}

void main()
{
	//Initialize_path();
	string command;
	char ch;
	cout << "Microsoft Windows[version 10.0.16299.431]" << endl << "(c) 2017 Microsoft Copreration.All rights reserved" << endl << endl;

	while (1)
	{
		if (Load()) {
			break;
		}
		else {
			Initialize();
			break;
		}
		print();
	}

	if (LoginIn())
	{
		system("cls");
		cout << "Microsoft Windows[version 10.0.16299.431]" << endl << "(c) 2017 Microsoft Copreration.All rights reserved" << endl << endl;
		if (language)cout << "��¼�ɹ�����ӭ��," << current_user.name << endl;
		else cout << "Login success, welcome you," << current_user.name << endl;
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
		CurrentDirector();   // ��ʾ��ǰĿ¼
		cin >> command;
		string param;

		if ((command == "mkdir") || (command == "MKDIR"))
		{
			cin >> param;
			mkdir(param);
			continue;
		}
		if ((command == "lan_choose") || (command == "LAN_CHOOSE")) {
			language_change();
			continue;
		}
		if ((command == "dir") || (command == "DIR"))
		{
			dir();
			continue;
		}
		if ((command == "ntdir") || (command == "NTDIR"))
		{
			cin >> param;
			ntdir(param);
			continue;
		}
		if ((command == "ltdir") || (command == "LTDIR"))
		{
			ltdir();
			continue;
		}
		if ((command == "create") || (command == "CREATE"))
		{
			cin >> param;
			create(param);
			continue;
		}
		if ((command == "delfile") || (command == "DELFILE"))
		{
			cin >> param;
			delfile(param);
			continue;
		}
		if ((command == "deldir") || (command == "DELDIR"))
		{
			cin >> param;
			deldir(param);
			continue;
		}
		if ((command == "write") || (command == "WRITE"))
		{
			cin >> param;
			string temp;
			//	cin>>temp;
			cin.get();
			getline(std::cin, temp);
			write(param, temp);
			continue;
		}
		if ((command == "wrmore") || (command == "WRMORE"))
		{
			cin >> param;
			string temp_1;

			//cin>>temp_1;
			cin.get();
			getline(std::cin, temp_1);
			int temp_2;
			cin >> temp_2;
			wrmore(param, temp_1, temp_2);
			continue;
		}
		if ((command == "open") || (command == "OPEN"))
		{
			cin >> param;
			open(param);
			continue;
		}
		if ((command == "read") || (command == "READ"))
		{
			cin >> param;
			read(param);
			continue;
		}
		if ((command == "close") || (command == "CLOSE"))
		{
			cin >> param;
			close(param);
			continue;
		}
		if ((command == "logout") || (command == "LOGOUT"))
		{
			LoginOut();
			system("pause");
			exit(0);
		}
		bool initi(string director_name);  // ��ʽ���ļ���
		if ((command == "initi") || (command == "INITI"))
		{
			Initialize();
			continue;
		}
		if ((command == "rename") || (command == "RENAME"))
		{
			cin >> param;
			string str;
			cin >> str;

			rename(param, str);
			continue;
		}
		if ((command == "ini") || (command == "INI"))
		{
			cin >> param;
			initi(param);
			continue;
		}
		if ((command == "copy") || (command == "COPY"))
		{
			cin >> param;
			string str;
			cin >> str;
			copy(param, str);
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
	myFileSystem.user_info[UCount++] = add;
}

void deleteuser(string name) {

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
	LoginOut();
	return;
}