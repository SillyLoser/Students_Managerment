#include "Manage_system.h"
#include <iostream>
using namespace std;
#include "Student.h"
using namespace std;

Student_Manager::Student_Manager()
{
	ifstream ifs;
	ifstream clis;
	ifstream scofs;
	ifs.open(FILENAME, ios::in);//读取学生信息文件
	clis.open(CLANAME, ios::in);//读取学生课程文件
	scofs.open(SCORENAME, ios::in);//读取学生成绩文件

	//若文件不存在时的初始化
	if (!ifs.is_open())
	{
		this->stu_num = 0;
		this->StuArr = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		if (!clis.is_open())clis.close();
		if (!scofs.is_open())scofs.close();
		return;
	}

	//文件存在且数据为空时的初始化
	char ch;	ifs >> ch;
	if (ifs.eof()) {
		//代表文件为空
		this->stu_num = 0;
		this->StuArr = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		if (clis.eof()) clis.close();
		if (!scofs.eof())scofs.close();
		return;
	}

	//文件存在，记录数据
	int num = get_Stunum();
	this->stu_num = num;


	//开辟空间
	this->StuArr = new Student * [this->stu_num];

	//将文件中的数据存放到数组中
	this->Init_stu();
	this->Init_cla();
	this->Score_init();
}

Student_Manager::~Student_Manager()
{
	if (this->m_FileIsEmpty != NULL)
	{
		for (int i = 0; i < this->stu_num; i++)
		{
			if (this->StuArr[i] != NULL)
			{
				StuArr[i] = NULL;
			}
		}
		delete[]this->StuArr;
		this->StuArr = NULL;
	}
}

void Student_Manager::Show_menu()
{
	system("color 7f");
	system("color 9f");
	//设置底色 颜色数值如下：0 = 黑色  8 = 灰色 1 = 蓝色  9 = 淡蓝色  2 = 绿色  A = 淡绿色 3 = 湖蓝色 B = 淡浅绿色 4 = 红色 C = 淡红色 5 = 紫色  D = 淡紫色 6 = 黄色  E = 淡黄色 7 = 白色  F = 亮白色
	//3代表背景色，f代表前景色
	system("mode con cols=85 lines=30");//窗体设置宽度和高高度的
	system("title 学生信息管理系统");//窗体控制台的标题

	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "************************---学籍管理系统----***************************" << endl;
	cout << "************************   0.退出系统      ***************************" << endl;
	cout << "************************   1.添加新学生    ***************************" << endl;
	cout << "************************   2.删除学生信息  ***************************" << endl;
	cout << "************************   3.显示学生信息  ***************************" << endl;
	cout << "************************   4.修改学生信息  ***************************" << endl;
	cout << "************************   5.查找学生信息  ***************************" << endl;
	cout << "************************   6.排序学生信息  ***************************" << endl;
	cout << "************************   7.清空文档      ***************************" << endl;
	cout << "************************   8.统计学生人数  ***************************" << endl;
	cout << "************************   9.课程管理系统  ***************************" << endl;
	cout << "************************  10.成绩管理系统  ***************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << endl;
}

void Student_Manager::Exit_System()
{
	cout << "欢迎下次使用!!" << endl;
	system("pause");
	exit(0);
}

void Student_Manager::Add_stu()
{
	cout << "请输入需要添加的学生数量" << endl;
	int num = 0;
	cin >> num;

	if (num > 0)
	{
		int newsize = this->stu_num + num;//新空间的大小
		Student** newArray = new Student * [newsize];
		if (this->StuArr != NULL)
		{
			for (int i = 0; i < this->stu_num; i++)
			{
				newArray[i] = this->StuArr[i];
			}
		}
		for (int i = 0; i < num; i++)
		{
			string m_id;
			string m_name;
			int m_age;
			string m_sex;
			string m_major;

			cout << "请输入" << i + 1 << "个学生的姓名：" << endl;
			cin >> m_name;

			cout << "请输入" << i + 1 << "个学生的年龄：" << endl;
			cin >> m_age;

			cout << "请输入" << i + 1 << "个学生的性别：" << endl;
			cin >> m_sex;

			cout << "请输入" << i + 1 << "个学生的专业：" << endl;
			cin >> m_major;

			cout << "请输入" << i + 1 << "个学生的学号：" << endl;
			cin >> m_id;

			Student* student = NULL;
			student = new Student(m_name, m_sex, m_age, m_id, m_major, 0);

			newArray[this->stu_num + i] = student;
		}
		delete[]this->StuArr;
		this->StuArr = newArray;
		this->stu_num = newsize;
		cout << "成功添加" << num << "名学生" << endl;

		//保存数据到文件
		this->save();
		this->m_FileIsEmpty = false;
	}
	else {
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}

void Student_Manager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);			//用输出的方式打开文件 -- 写文件

	for (int i = 0; i < stu_num; i++)
	{
		ofs << this->StuArr[i]->name << "  "
			<< this->StuArr[i]->id << "  "
			<< this->StuArr[i]->sex << "  "
			<< this->StuArr[i]->age << "  "
			<< this->StuArr[i]->major << endl;
	}
	ofs.close();
}

int Student_Manager::get_Stunum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	string id;
	string sex;
	int age;
	string major; int snum = 0;
	while (ifs >> name && ifs >> id && ifs >> sex && ifs >> age && ifs >> major)
	{
		snum++;
	}
	return snum;
}

void Student_Manager::Init_stu()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	string name;	string id;	string sex;	int age;	string major;
	int index = 0;
	while (ifs >> name && ifs >> id && ifs >> sex && ifs >> age && ifs >> major)
	{
		Student* student = NULL;
		student = new Student(name, sex, age, id, major, 0);
		this->StuArr[index++] = student;
	}
	ifs.close();
}

void Student_Manager::Show_stu()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或文件为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->stu_num; i++)
			this->StuArr[i]->ShowInfo();
	}
	system("pause");
	system("cls");
}

void Student_Manager::Del_stu()
{
	if (this->m_FileIsEmpty)cout << "文件不存在或者文件为空！" << endl;
	else
	{
		cout << "请输入需要删除的学生学号：" << endl;
		string s_id = " "; cin >> s_id;

		int index = this->IsExist_stu(s_id);

		if (index != -1)
		{
			for (int i = index; i < this->stu_num - 1; i++)
				this->StuArr[i] = this->StuArr[i + 1];
			this->stu_num--;		//跟新数组记录人员数量
			this->save();
			cout << "删除成功" << endl;
		}
		else
			cout << "删除失败，未找到该学生!" << endl;
	}
	this->save();
	this->clasave();
	this->Score_save();
	system("pause");
	system("cls");
	return;
}

int Student_Manager::IsExist_stu(string s_id)
{
	int index = -1;
	for (int i = 0; i < this->stu_num; i++)
		if (this->StuArr[i]->id == s_id)
		{
			index = i; break;
		}
	return index;
}

void Student_Manager::Mod_stu()
{
	if (this->m_FileIsEmpty)
		cout << "文件不存在或文件为空!" << endl;
	else
	{
		cout << "请输入修改学生的学号：" << endl;
		string s_id;
		cin >> s_id;

		int ret = this->IsExist_stu(s_id);
		if (ret != -1)
		{
			string new_id = "";
			string new_name = "";
			string new_major = "";
			int new_age = 0;
			string new_sex = "";

			cout << "文件中存在学号为：" << s_id << "的学生" << endl;
			cout << "请输入新的学生姓名：" << endl;
			cin >> new_name;
			cout << "请输入新的学生性别：" << endl;
			cin >> new_sex;
			cout << "请输入新的学生年龄：" << endl;
			cin >> new_age;
			cout << "请输入新的学生学号：" << endl;
			cin >> new_id;
			cout << "请输入新的学生专业：" << endl;
			cin >> new_major;

			Student* student = NULL;
			student = new Student(new_name, new_sex, new_age, new_id, new_major, 0);
			this->StuArr[ret] = student;
			cout << "修改成功！" << endl;

			this->save();
			this->clasave();
			this->Score_save();
		}
		else cout << "修改失败，查无此人！" << endl;
	}
	system("pause");
	system("cls");
}

void Student_Manager::Find_stu() {
	if (this->m_FileIsEmpty)
	{
		cout << "当前文件不存在或记录为空" << endl;
	}
	else
	{
		cout << "请输入查找的方法：" << endl;
		cout << "1---按照学生的学号查找：" << endl;
		cout << "2---按照学生的姓名查找：" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			string s;
			cout << "请输入查找的学生的学号：" << endl;
			cin >> s;

			int ret = IsExist_stu(s);
			if (ret != -1)
			{
				cout << "查找成功！！！" << endl;
				this->StuArr[ret]->ShowInfo();
			}
			else
			{
				cout << "查找失败！查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			string sname;
			cout << "请输入查找的姓名：" << endl;
			cin >> sname;

			bool flag = false;

			for (int i = 0; i < this->stu_num; i++)
			{
				if (this->StuArr[i]->name == sname)
				{
					cout << "查找成功，学生学号为："
						<< this->StuArr[i]->id
						<< "号信息如下：" << endl;

					this->StuArr[i]->ShowInfo();

					flag = true;
				}
			}
			if (!flag)cout << "查找失败，查无此人！" << endl;
		}
		else {
			cout << "输入选项有误!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void Student_Manager::Sort_stu()
{
	if (this->m_FileIsEmpty)
		cout << "当前文件为空或文件不存在！！！" << endl;
	else {
		cout << "请选择排序的方式" << endl;
		cout << "1---按学号升序排序" << endl;
		cout << "2---按学号降序排序" << endl;

		int choice = 0;
		cin >> choice;
		if (choice == 1)
		{
			for (int end = this->stu_num - 1; end > 0; end--)
				for (int begin = 0; begin < end; begin++)
				{
					if (StuArr[begin]->id.length() > StuArr[end]->id.length()
						|| ((StuArr[begin]->id.length() == StuArr[end]->id.length())
							&& StuArr[begin]->id > StuArr[end]->id))
					{
						string tempname = StuArr[begin]->name;
						string tempid = StuArr[begin]->id;
						string tempmajor = StuArr[begin]->major;
						string tempsex = StuArr[begin]->sex;
						int tempage = StuArr[begin]->age;

						StuArr[begin]->name = StuArr[end]->name;
						StuArr[begin]->id = StuArr[end]->id;
						StuArr[begin]->major = StuArr[end]->major;
						StuArr[begin]->sex = StuArr[end]->sex;
						StuArr[begin]->age = StuArr[end]->age;

						StuArr[end]->name = tempname;
						StuArr[end]->id = tempid;
						StuArr[end]->major = tempmajor;
						StuArr[end]->sex = tempsex;
						StuArr[end]->age = tempage;
					}
				}
		}
		else if (choice == 2)
		{
			for (int end = this->stu_num - 1; end > 0; end--)
				for (int begin = 0; begin < end; begin++)
				{
					if (StuArr[begin]->id.length() < StuArr[end]->id.length()
						|| ((StuArr[begin]->id.length() == StuArr[end]->id.length())
							&& StuArr[begin]->id < StuArr[end]->id))
					{
						string tempname = StuArr[begin]->name;
						string tempid = StuArr[begin]->id;
						string tempmajor = StuArr[begin]->major;
						string tempsex = StuArr[begin]->sex;
						int tempage = StuArr[begin]->age;

						StuArr[begin]->name = StuArr[end]->name;
						StuArr[begin]->id = StuArr[end]->id;
						StuArr[begin]->major = StuArr[end]->major;
						StuArr[begin]->sex = StuArr[end]->sex;
						StuArr[begin]->age = StuArr[end]->age;

						StuArr[end]->name = tempname;
						StuArr[end]->id = tempid;
						StuArr[end]->major = tempmajor;
						StuArr[end]->sex = tempsex;
						StuArr[end]->age = tempage;
					}
				}
		}
		else cout << "输入有误!!!" << endl;
		this->save();
	}
	system("pause");
	system("cls");
}

void Student_Manager::Clean_File()
{
	cout << "确认清空?" << endl;
	cout << "1---确定" << endl;
	cout << "2---取消" << endl;
	int choice = 0;
	cin >> choice;
	if (choice == 1)
	{
		ofstream cofs(CLANAME, ios::trunc);//课程系统文件的重置
		cofs.close();

		if (this->StuArr != NULL)
		{
			for (int i = 0; i < this->stu_num; i++)
			{
				this->StuArr[i]->Clasnum = 0;
				delete[]this->StuArr[i]->Clas;
				this->StuArr[i]->Clas = NULL;
			}
		}
		/*------------------------------------------------------------------------*/
		ofstream sfs(SCORENAME, ios::trunc);//成绩系统文件的重置
		sfs.close();
		if (this->StuArr != NULL)
		{
			for (int i = 0; i < this->stu_num; i++)
			{
				delete[]this->StuArr[i]->Sco_re;
				this->StuArr[i]->Sco_re = NULL;
			}
		}


		/*------------------------------------------------------------------------*/
		ofstream ofs(FILENAME, ios::trunc);//学生系统文件的重置
		ofs.close();

		if (this->StuArr != NULL)
		{
			for (int i = 0; i < this->stu_num; i++)
			{
				//delete this->StuArr[i];
				this->StuArr[i] = NULL;
			}


			delete[]this->StuArr;
			this->StuArr = NULL;
			this->stu_num = 0;
			this->m_FileIsEmpty = true;
		}
	}
}

/*******************************************************************************/
void Student_Manager::Clas_Menu()
{
	system("color 7f");
	system("color 2f");
	//设置底色 颜色数值如下：0 = 黑色  8 = 灰色 1 = 蓝色  9 = 淡蓝色  2 = 绿色  A = 淡绿色 3 = 湖蓝色 B = 淡浅绿色 4 = 红色 C = 淡红色 5 = 紫色  D = 淡紫色 6 = 黄色  E = 淡黄色 7 = 白色  F = 亮白色
	//3代表背景色，f代表前景色
	system("mode con cols=85 lines=30");//窗体设置宽度和高高度的
	system("title 学生课程管理系统");//窗体控制台的标题
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "************************----课程管理系统----***************************" << endl;
	cout << "************************   0.返回上级界面  ***************************" << endl;
	cout << "************************   1.添加学生课程  ***************************" << endl;
	cout << "************************   2.删除学生课程  ***************************" << endl;
	cout << "************************   3.查找学生课程  ***************************" << endl;
	cout << "************************   4.修改学生课程  ***************************" << endl;
	cout << "************************   5.显示学生课程  ***************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
}
void Student_Manager::Enter_ClassManager()
{
	while (true)
	{
		Clas_Menu();
		cout << "请输入你的选择： " << endl;
		int choose; cin >> choose;
		switch (choose)
		{
		case 0:
		{
			cout << "确认返回？？" << endl;
			cout << "1---确认" << endl; cout << "2---取消" << endl;
			int cho; cin >> cho;
			if (cho == 1)
			{
				system("cls");
				return;
			}
			else
			{
				system("cls");
				break;
			}
		}
		case 1:
			add_class();
			break;
		case 2:Del_Cla();
			break;
		case 3:Find_Cla();
			break;
		case 4:Mod_Cla();
			break;
		case 5:Show_Cla();
			break;
		}
	}system("pause"); system("cls");
}
void Student_Manager::add_class() {
	if (this->m_FileIsEmpty)
		cout << "当前记录为空，无法添加！！" << endl;
	else
	{
		cout << "请输入需要添加课程的学生编号：" << endl;
		string idd;
		cin >> idd;
		int ret = IsExist_stu(idd);
		if (ret != -1) {
			cout << "学生  " << StuArr[ret]->name << "  目前已有课程数量:    " << StuArr[ret]->Clasnum << endl;
			cout << "请输入需要添加课程的数量" << endl;
			int num; cin >> num;
			int rnum = this->StuArr[ret]->Clasnum;
			if (rnum == 0 || StuArr[ret]->Clas == NULL)
			{
				this->StuArr[ret]->Clas = new string[num];
				//——————————————————————————————————————
				this->StuArr[ret]->Sco_re = new string[num];
				//——————————————————————————————————————
			}
			else
			{
				string* temp = new string[rnum + num];
				//——————————————————————————————————————
				string* scotemp = new string[rnum + num];
				//——————————————————————————————————————
				for (int i = 0; i < rnum; i++)
				{
					temp[i] = StuArr[ret]->Clas[i];
					//——————————————————————————————————————
					scotemp[i] = StuArr[ret]->Sco_re[i];
					//——————————————————————————————————————
				}
				delete[]StuArr[ret]->Clas;
				//——————————————————————————————————————
				delete[]StuArr[ret]->Sco_re;
				//——————————————————————————————————————
				//——————————————————————————————————————
				StuArr[ret]->Sco_re = scotemp;
				//——————————————————————————————————————
				StuArr[ret]->Clas = temp;
			}
			for (int i = rnum; i < num + rnum; i++)
			{
				cout << "输入添加的第" << i + 1 << "门课程：" << endl;
				cin >> StuArr[ret]->Clas[i]; StuArr[ret]->Sco_re[i] = "0";
			}

			this->StuArr[ret]->Clasnum += num;
			cout << "添加课程完毕，当前课程总数为：" << this->StuArr[ret]->Clasnum << endl;
		}
		else cout << "该学生不存在" << endl;
	}
	if (!this->m_FileIsEmpty)this->clasave();
	if (!this->m_FileIsEmpty)this->Score_save();
	system("pause");
	system("cls");
}
void Student_Manager::Show_Cla() {
	if (this->m_FileIsEmpty)
		cout << "当前不存在学生，无法显示课程" << endl;
	else
	{
		cout << "请输入学号，显示该学号课程信息" << endl;
		string stuid; cin >> stuid;
		int ret = IsExist_stu(stuid);
		if (ret != -1)
		{
			cout << "学号为" << stuid << "的学生：" << StuArr[ret]->name
				<< "当前课程数量：" << StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "课程：" << i + 1 << "     " << StuArr[ret]->Clas[i] << endl;
		}
		else cout << "不存在该学号学生，退出" << endl;
	}
	system("pause");
	system("cls");
}
void Student_Manager::Mod_Cla() {
	if (!m_FileIsEmpty)
	{
		cout << "请输入需要修改课程的学生学号：" << endl;
		string idd; cin >> idd;
		int ret = IsExist_stu(idd);
		if (ret != -1)
		{
			cout << "存在学号为： " << idd << " 的学生" << endl;
			cout << "该学生目前课程数量为： " << this->StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "课程：" << i + 1 << "     " << StuArr[ret]->Clas[i] << endl;
			cout << "请输入需要修改的课程名" << endl;
			string mod_name; cin >> mod_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == mod_name)
				{
					cout << "请输入修改后的课程  : " << endl;
					cin >> mod_name;
					StuArr[ret]->Clas[i] = mod_name;
					cout << "修改成功！！！" << endl;
					system("pause");
					this->clasave();
					return;
				}
				cout << "学生： " << StuArr[ret]->name << " 不存在该课程！！" << endl;
		}
		else
			cout << "不存在学号为： " << idd << " 的学生" << endl;
	}
	else
		cout << "文件不存在！！" << endl;
	system("pause");
	system("cls");
}
void Student_Manager::Del_Cla() {
	if (!this->m_FileIsEmpty)
	{
		cout << "请输入需要进行删除操作的学生编号：" << endl;
		string idd; cin >> idd;
		int ret = IsExist_stu(idd);
		if (ret != -1)
		{
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "课程：" << i + 1 << "     " << StuArr[ret]->Clas[i] << endl;
			cout << "请输入需要删除的课程名称：" << endl;
			string del_name; cin >> del_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++) {
				if (StuArr[ret]->Clas[i] == del_name)
				{
					for (int j = i + 1; j < StuArr[ret]->Clasnum; j++)
					{
						StuArr[ret]->Clas[j - 1] = StuArr[ret]->Clas[j];
						StuArr[ret]->Sco_re[j - 1] = StuArr[ret]->Sco_re[j];
					}
					this->StuArr[ret]->Clasnum--;
					this->Score_save(); this->clasave();
					cout << "删除成功！！" << endl;
					system("pause"); return;
					return;
				}
			}
			cout << "删除失败，课程不存在" << endl;
		}
		else cout << "不存在学号为： " << idd << " 的学生" << endl;
	}
	else cout << "当前不存在学生，无法进行课程管理！" << endl;
}
void Student_Manager::Find_Cla() {
	if (!m_FileIsEmpty)
	{
		cout << "请输入查找的学生 ： " << endl;
		string stu_id; cin >> stu_id;
		int ret = IsExist_stu(stu_id);
		if (ret != -1)
		{
			cout << "请输入需要查找的课程 名称 ：" << endl;
			string cla_name; cin >> cla_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == cla_name)
				{
					cout << "存在 课程：" << cla_name << endl;
					system("pause"); return;
				}
			cout << "不存在课程： " << cla_name << endl;
		}
		else cout << "不存在学号为： " << stu_id << " 的学生" << endl;
	}
	else
		cout << "当前学生数量为空，无法进行课程管理！！" << endl;
	system("pause");
	system("cls");
}
void Student_Manager::Init_cla() {
	ifstream clis;
	clis.open(CLANAME, ios::in);
	string cname, cid, clas; int clsnum;

	int index = 0;

	while (clis >> cname && clis >> cid && clis >> clsnum)
	{
		this->StuArr[index]->Clas = new string[1000];
		this->StuArr[index]->Sco_re = new string[1000];
		this->StuArr[index]->Clasnum = clsnum;

		for (int i = 0; i < this->StuArr[index]->Clasnum; i++)
		{
			clis >> this->StuArr[index]->Clas[i];
		}
		index++;
	}
	clis.close();
}
void Student_Manager::clasave() {
	ofstream cofs;
	cofs.open(CLANAME, ios::out);

	for (int i = 0; i < this->stu_num; i++)
	{
		cofs << StuArr[i]->name << " " << StuArr[i]->id << " " << StuArr[i]->Clasnum << " ";
		for (int j = 0; j < this->StuArr[i]->Clasnum; j++)
			cofs << this->StuArr[i]->Clas[j] << " ";
		cofs << endl;
	}
	cofs.close();
}
/*******************************************************************************/

void Student_Manager::Score_menu()
{
	system("color 7f");
	system("color 6f");
	//设置底色 颜色数值如下：0 = 黑色  8 = 灰色 1 = 蓝色  9 = 淡蓝色  2 = 绿色  A = 淡绿色 3 = 湖蓝色 B = 淡浅绿色 4 = 红色 C = 淡红色 5 = 紫色  D = 淡紫色 6 = 黄色  E = 淡黄色 7 = 白色  F = 亮白色
	//3代表背景色，f代表前景色	
	system("mode con cols=85 lines=30");//窗体设置宽度和高高度的
	system("title 学生成绩管理系统");//窗体控制台的标题
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "************************----成绩管理系统----***************************" << endl;
	cout << "************************   0.返回上级界面  ***************************" << endl;
	cout << "************************   1.添加学生成绩  ***************************" << endl;
	cout << "************************   2.重置学生成绩  ***************************" << endl;
	cout << "************************   3.查询学生成绩  ***************************" << endl;
	cout << "************************   4.修改学生成绩  ***************************" << endl;
	cout << "************************   5.显示学生成绩  ***************************" << endl;
	cout << "**********************************************************************" << endl;
	cout << "**********************************************************************" << endl;
}
void Student_Manager::Enter_ScoreManager()
{
	while (true)
	{
		Score_menu();
		cout << "请输入你的选择： " << endl;
		int cho; cin >> cho;
		switch (cho)
		{
		case 0:
		{
			cout << "确认返回？？" << endl;
			cout << "1---确认" << endl; cout << "2---取消" << endl;
			int chio; cin >> chio;
			if (chio == 1)
			{
				system("cls");
				return;
			}
			else
			{
				system("cls");
				break;
			}
		}
		case 1:
			add_score();
			break;
		case 2:Del_Score();
			break;
		case 3:Find_Score();
			break;
		case 4:Mod_Score();
			break;
		case 5:Show_Score();
			break;
		}
	}system("pause"); system("cls");
}
void Student_Manager::add_score()
{
	if (this->m_FileIsEmpty)cout << "当前系统无记录学生，操作失败 ! ! !" << endl;
	else {
		cout << "输入需要需要进行操作的学生学号： " << endl;
		string id;
		cin >> id;
		int ret = IsExist_stu(id);
		if (ret != -1) {
			cout << "学生  " << StuArr[ret]->name << "  目前已有课程数量:    " << StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "课程：" << i + 1 << "     " << StuArr[ret]->Clas[i] << endl;
			cout << "请输入需要操作的课程的名称" << endl;
			string mod_name; cin >> mod_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == mod_name)
				{
					cout << "输入记录分数：" << endl;
					string tempscore = ""; cin >> tempscore;
					this->StuArr[ret]->Sco_re[i] = tempscore;
					cout << "成绩修改成功 ! ! ! " << endl;
					break;
				}
		}
		else cout << "不存在学号为： " << id << "的学生" << endl;
	}
	if (!this->m_FileIsEmpty)this->Score_save();
	system("pause");
	system("cls");
}
void Student_Manager::Score_save()
{
	ofstream scofs;
	scofs.open(SCORENAME, ios::out);

	for (int i = 0; i < this->stu_num; i++)
	{
		for (int j = 0; j < this->StuArr[i]->Clasnum; j++)
			scofs << StuArr[i]->name << " " << StuArr[i]->id << " " << this->StuArr[i]->Clas[j] << " " << this->StuArr[i]->Sco_re[j] << endl;
	}
	scofs.close();
}
void Student_Manager::Score_init()
{
	ifstream scis;
	scis.open(SCORENAME, ios::in);
	string cname, cid, scname, sco;

	int index = 0;

	while (scis >> cname && scis >> cid && scis >> scname && scis >> sco)
	{
		int tret = this->IsExist_stu(cid);
		if (tret != -1)
			for (int i = 0; i < this->StuArr[tret]->Clasnum; i++)
				if (this->StuArr[tret]->Clas[i] == scname)
				{
					this->StuArr[tret]->Sco_re[i] = sco;
					break;
				}
	}
	scis.close();
}
void Student_Manager::Show_Score()

{
	if (this->m_FileIsEmpty)
		cout << "当前不存在学生，无法显示课程" << endl;
	else
	{
		cout << "请输入学号，显示该学号课程成绩信息" << endl;
		string stuid; cin >> stuid;
		int ret = IsExist_stu(stuid);
		if (ret != -1)
		{
			cout << "学号为" << stuid << "的学生：" << StuArr[ret]->name
				<< "当前课程数量：" << StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "课程:     " << StuArr[ret]->Clas[i] << "   分数为： " << StuArr[ret]->Sco_re[i] << endl;
		}
		else  cout << "不存在该学号学生，退出" << endl;
	}
	system("pause");
	system("cls");
}
void Student_Manager::Mod_Score()	
{
	if (!m_FileIsEmpty)
	{
		cout << "请输入需要修改成绩的学生学号：" << endl;
		string idd; cin >> idd;
		int ret = IsExist_stu(idd);
		if (ret != -1)
		{
			cout << "存在学号为： " << idd << " 的学生" << endl;
			cout << "该学生目前课程数量为： " << this->StuArr[ret]->Clasnum << endl;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				cout << "课程：" << i + 1 << "     " << StuArr[ret]->Clas[i] << "		目前分数为：" << StuArr[ret]->Sco_re[i] << endl;
			cout << "请输入需要修改成绩的课程名" << endl;
			string mod_score; cin >> mod_score;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == mod_score)
				{
					cout << "请输入修改后的成绩  : " << endl;
					cin >> mod_score;
					StuArr[ret]->Sco_re[i] = mod_score;
					cout << "修改成功！！！" << endl;
					break;
				}
		}
		else
			cout << "不存在学号为： " << idd << " 的学生" << endl;
	}
	else
		cout << "文件不存在！！" << endl;
	this->Score_save();
	system("pause");
	system("cls");
}
void Student_Manager::Del_Score()
{
	if (this->m_FileIsEmpty)cout << "文件不存在或者文件为空！" << endl;
	else
	{
		cout << "请输入需要重置成绩的学生学号：" << endl;
		string s_id = " "; cin >> s_id;

		int index = this->IsExist_stu(s_id);

		if (index != -1)
		{
			for (int i = 0; i < StuArr[index]->Clasnum; i++)
				this->StuArr[index]->Sco_re[i] = "0";
			this->Score_save();
			cout << "重置成功" << endl;
		}
		else
			cout << "删除失败，未找到该学生!" << endl;
	}
	system("pause");
	system("cls");
	return;
}
void Student_Manager::Find_Score()
{
	if (!m_FileIsEmpty)
	{
		cout << "请输入查询的学生 ： " << endl;
		string stu_id; cin >> stu_id;
		int ret = IsExist_stu(stu_id);
		if (ret != -1)
		{
			cout << "请输入需要查询的课程 名称 ：" << endl;
			string cla_name; cin >> cla_name;
			for (int i = 0; i < StuArr[ret]->Clasnum; i++)
				if (StuArr[ret]->Clas[i] == cla_name)
				{
					cout << "课程：" << cla_name <<"成绩为："<<StuArr[ret]->Sco_re[i] << endl;
					system("pause"); return;
				}
			cout << "不存在课程： " << cla_name << endl;
		}
		else cout << "不存在学号为： " << stu_id << " 的学生" << endl;
	}
	else
		cout << "当前学生数量为空，无法进行课程管理！！" << endl;
	system("pause");
	system("cls");

}