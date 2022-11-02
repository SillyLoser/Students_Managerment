#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Student
{
public:
	//含参的构造函数
	Student(string s_name, string s_sex, int s_age, string s_id, string s_major, int Clasnum);
	~Student();
	//显示学生各项信息的函数接口
	void ShowInfo();
public:
	string id;//记录学生的学号
	string name;//记录学生的姓名
	string major;//记录学生的专业
	int age;//记录学生的年龄
	string sex;//记录学生的性别

	string* Clas;//存放课程
	string* Sco_re;//存放课程成绩
	int Clasnum;//记录存在课程数量
};