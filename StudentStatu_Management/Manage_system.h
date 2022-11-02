#pragma once
#include <iostream>
#include "Student.h"

#include <fstream>
#define FILENAME "stuFile.txt"
#define CLANAME "claFile.txt"
#define SCORENAME "scoFile.txt"

using namespace std;

class Student_Manager	
{
public:
	Student_Manager();
	void Show_menu();
	//保存文件
	void save();
	//统计文件中的人数
	int get_Stunum();

	//学生操作
	/***************************************************************************************/
	void Add_stu();				//添加学生信息
	void Show_stu();			//显示学生各项信息
	void Del_stu();				//清除学生信息
	void Mod_stu();				//修改学生信息
	void Find_stu();			//查找学生信息
	void Sort_stu();			//对学生信息可按照 升序/降序 排列
	void Clean_File();			//清除文件中所有的信息
	int IsExist_stu(string id);	//判断是否存在学号为id的学生并返回该位置
	void Init_stu();			//初始化文件以及将文件 stuFile.txt 中存在的学生信息记录到数据
	~Student_Manager();			//学生系统析构函数，对多余的堆变量进行清除操作
	void Exit_System();			//退出系统
	Student** StuArr;			//二维数组，存储学生数据单元
	int stu_num;				//记录当前记录的学生数量
	bool m_FileIsEmpty;			//判断文件是否为空
	/***************************************************************************************/
	//课程系统管理
	void clasave();				//将课程信息保存至文件 claFile.txt 中
	void Init_cla();			//向文件中读取学生课程信息，初始化课程系统
	void Enter_ClassManager();	//课程系统接口函数，以此函数进入课程管理系统
	void Clas_Menu();			//系统菜单显示，提供图形化界面
	void add_class();			//添加学生的课程信息
	void Show_Cla();			//打印学生的课程信息
	void Mod_Cla();				//修改学生的课程信息
	void Del_Cla();				//清除学生的课程信息
	void Find_Cla();			//查询课程存在与否
	/***************************************************************************************/
	//成绩管理系统
	void Score_menu();			//成绩系统的菜单显示，向用户提供良好的界面显示
	void Score_save();			//保存成绩信息，将成绩信息输出至文档 scoFile.txt
	void Score_init();			//初始化系统，若 scoFile.txt 文档存在且文档不为空则读取当前文件数据
	void Enter_ScoreManager();  //成绩系统的接口函数
	void add_score();			//添加课程成绩信息
	void Show_Score();			//显示学生课程成绩
	void Mod_Score();			//对目标学号学生成绩进行修改
	void Del_Score();			//重置学生成绩
	void Find_Score();			//查询单科成绩信息
	/***************************************************************************************/
};