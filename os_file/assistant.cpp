#include"stdafx.h"
#include <string>
#include <sstream>
void dir()
{
	vector<int>::iterator director_p = MFS.DSV[CurD].DV.begin();
	cout << endl << "<DIR LIST>:" << endl;
	while (director_p != MFS.DSV[CurD].DV.end())
	{
		int index = *director_p;
		if (index != -1)      // 如果可用
		{
			cout << '\t' << MFS.DSV[index].time << "\t<DIR>" << '\t' << "name: " << MFS.DSV[index].name << '\t' << "owner: ";
			cout << MFS.DSV[index].owner << endl;
		}
		director_p++;
	}
	cout << endl;
	vector<int>::iterator file_p = MFS.DSV[CurD].FV.begin();
	cout << "<FILE LIST>:" << endl;
	while (file_p != MFS.DSV[CurD].FV.end())
	{
		int index = *file_p;
		if (index != -1)  //如果可用
		{
			cout << '\t' << MFS.FSV[index].time << "\t<FILE>" << '\t' << "name: " << MFS.FSV[index].filename << '\t' << "owner: ";
			cout << MFS.FSV[index].owner << endl;
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