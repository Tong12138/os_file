#include"stdafx.h"
#include <string>
#include <sstream>
void dir()
{
	vector<int>::iterator director_p = myFileSystem.vector_folder[current_director_index].DV.begin();
	cout << endl << "<DIR LIST>:" << endl;
	while (director_p != myFileSystem.vector_folder[current_director_index].DV.end())
	{
		int index = *director_p;
		if (index != -1)      // �������
		{
			cout << '\t' << myFileSystem.vector_folder[index].time << "\t<DIR>" << '\t' << "name: " << myFileSystem.vector_folder[index].name << '\t' << "owner: ";
			cout << myFileSystem.vector_folder[index].owner << endl;
		}
		director_p++;
	}
	cout << endl;
	vector<int>::iterator file_p = myFileSystem.vector_folder[current_director_index].FV.begin();
	cout << "<FILE LIST>:" << endl;
	while (file_p != myFileSystem.vector_folder[current_director_index].FV.end())
	{
		int index = *file_p;
		if (index != -1)  //�������
		{
			cout << '\t' << myFileSystem.vector_file[index].time << "\t<FILE>" << '\t' << "name: " << myFileSystem.vector_file[index].filename << '\t' << "owner: ";
			cout << myFileSystem.vector_file[index].owner << endl;
		}
		file_p++;
	}
	cout << endl;
}


string gettime() {
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	std::stringstream yea;
	std::string year;
	yea << sys.wYear;
	yea >> year;
	std::stringstream mou;
	std::string mouth;
	mou << sys.wMonth;
	mou >> mouth;
	std::stringstream da;
	std::string day;
	da << sys.wDay;
	da >> day;
	std::stringstream hou;
	std::string hour;
	hou << sys.wHour;
	hou >> hour;
	std::stringstream min;
	std::string minute;
	min << sys.wMinute;
	min >> minute;
	string nowtime = year + '/' + mouth + '/' + day + "---" + hour + ':' + minute;
	return nowtime;
}

void language_change() {
	if (language == 0) {
		cout << "ȷ��Ҫ�ı�����Ϊ����ô��Y/N" << endl;
	}
	else {
		cout << "Do you want to change the language for English? Y/n" << endl;
	}
	string choice;
	cin >> choice;
	bool nor = false;//�Ƿ�ı�
	if (language)nor = !nor;
	if (choice == "Y" || "y") {
		nor = !nor;
	}
	language = nor;
}