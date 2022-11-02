#include <iostream>
#include "Manage_system.h"
using namespace std;
#include "Student.h"

int main()
{
	Student_Manager wm;
	int choice = 0;
	while (true)
	{
		wm.Show_menu();
		cout << "请输入你选择的功能" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:wm.Exit_System();
			break;
		case 1:wm.Add_stu();
			break;
		case 2:wm.Del_stu();
			break;
		case 3:wm.Show_stu();
			break;
		case 4:wm.Mod_stu();
			break;
		case 5:wm.Find_stu();
			break;
		case 6:wm.Sort_stu();
			break;
		case 7:wm.Clean_File();
		case 8:
			cout << "当前记录人数为：" << wm.get_Stunum() << endl;
			system("pause"); system("cls");
			break;
		case 9:
			system("cls");
			wm.Enter_ClassManager();
			break;
		case 10:
			system("cls");
			wm.Enter_ScoreManager();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}