#include"stdafx.h"
#include <string>
#include <sstream>
void dir()
{
	list<int>::iterator director_p = myFileSystem.vector_folder[current_director_index].director_list.begin();
	cout << endl << "<DIR LIST>:" << endl;
	while (director_p != myFileSystem.vector_folder[current_director_index].director_list.end())
	{
		int index = *director_p;
		if (index != -1)      // 如果可用
		{
			cout << '\t' << myFileSystem.vector_folder[index].time << "\t<DIR>" << '\t' << "name: " << myFileSystem.vector_folder[index].name << '\t' << "owner: ";
			cout << myFileSystem.vector_folder[index].owner << endl;
		}
		director_p++;
	}
	cout << endl;
	list<int>::iterator file_p = myFileSystem.vector_folder[current_director_index].file_list.begin();
	cout << "<FILE LIST>:" << endl;
	while (file_p != myFileSystem.vector_folder[current_director_index].file_list.end())
	{
		int index = *file_p;
		if (index != -1)  //如果可用
		{
			cout << '\t' << myFileSystem.vector_file[index].time << "\t<FILE>" << '\t' << "name: " << myFileSystem.vector_file[index].file_name << '\t' << "owner: ";
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
		cout << "确认要改变语言为中文么？Y/N" << endl;
	}
	else {
		cout << "Do you want to change the language for English? Y/n" << endl;
	}
	string choice;
	cin >> choice;
	bool nor = false;//是否改变
	if (language)nor = !nor;
	if (choice == "Y" || "y") {
		nor = !nor;
	}
	language = nor;
}