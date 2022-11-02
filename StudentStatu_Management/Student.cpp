#include <iostream>
using namespace std;
#include "Student.h"

Student::Student(string s_name, string s_sex, int s_age, string s_id, string s_major,int Clasnum=0)
{
	this->name = s_name;
	this->age = s_age;
	this->major = s_major;
	this->id = s_id;
	this->sex = s_sex;
	this->Clasnum = Clasnum;
}

void Student::ShowInfo()
{
	cout << "学生姓名：" << this->name
		<< "\t学生年龄：" << this->age
		<< "\t学生性别：" << this->sex
		<< "\t学生专业：" << this->major
		<< "\t学生学号：" << this->id << endl;
}