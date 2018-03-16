#pragma  once
#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
#include<string>
#include<Windows.h>
#include<deque>
#include<list>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>

using namespace std;


#endif // STUDENT_H

struct inteNumber {//由于兴趣管理采用的时三层封装，兴趣作为兴趣类的一个属性的方式，所以单独为兴趣类和兴趣做了一个结构体，
                    //重载了==符号

    int inteClass;//兴趣类别编号
    int inte;//具体兴趣编号
    bool operator==(const inteNumber& cmp);
    inteNumber(int inteClass, int inte);
};




class student {
private:
    long id;
    string name;
    string sex;
    int age;
    int department;//专业，在父类学生管理类设置Map做转化 这里我最开始的设想，由于string比int多占用太多存储空间，人数过多的话会造成大量空间浪费
                    //所以我就想将专业和兴趣设为整形，然后通过map做匹配，在需要的时候进行转换，当时想的很简单，实际上后来操作起来还是比较麻烦的
    string otherNote;
    int splNumber;//专一编码，考虑到名字可能重名，就干脆再设置一个内部编码，保证每个人编号不一样,可以区分
public:
    vector<inteNumber> inteNum; //设置inteNumber形式的vector,用来保存每个学生的兴趣项
    student(long id, string name, string sex, int age, int department, string othernote);//构造函数
    student(const student &b);
    void setSplNumber();//设置特殊编码
    int static getSplNumberByName(string);//此函数设置为静态的，可以方便的通过姓名获取专一编码
    inline int getDepartmentNum() { return department; }
    inline student* getStuPtr() {  return this; }//返回该对象的指针
    inline int getSplNumber() { return splNumber; }
    inline string getName() { return this->name; }
    inline long getId() { return this->id; }
    inline string getSex() { return this->sex; }
    inline int getAge() { return this->age; }
    inline string getOtherNote() { return this->otherNote; }
    bool modifyInfo(long id, string name, string sex, int age, int department, string othernote);
    bool addInte(int inteClass,int inte);//增加兴趣
    bool delInte(int inteClass,int inte);
};


class studentMana {
private:

public:
    //属性
    int static sumDepartment;//总的专业数量
    int static sumStudent;//总人数
    vector<student> stu;//将所有学生用数组存起来，方便查询
    map<int, string> numDepartmentMap;//设置map，说实话，这一点没有python好，map不能方便的获取value的集合，只能通过迭代器遍历，我就干脆设置了一正一反两个map结合起来用，牺牲空间复杂换时间复杂度
    map<string, int> departmentNumMap;
    map<int, student*> stuMap;//老出问题，问题还没找到，先弃之不用，等整体完成了再来修补好了。不过百分之八十是弃之不用了
                                //这个传指针总是传成了一个随机指针，我很苦恼，等我哪天发神经，我会回来debug的
    //方法
    studentMana();
    bool setDepartment(string departmentName);
    bool addStudent(long id, string name, string sex, int age, string departmentName, string othernote);//后期改进的时候可以添加重复学生检测
    bool delStudentByName(string name);
    string getDepartmentNameBySplNum(int splNum);
    student* searchStudentByName(string);//后期改进代码时，考虑学生可能有重名的
    student* searchStudentById(int);
    vector<student> searchStudentByDepartmentName(string);
    bool modifyStudentInfo(int splNumber);
    bool addInte(string name, int inteClass,int inte);
    bool delInte(string name, int inteClass, int inte);
    student* searchStudentBySplNum(int splNum);
    void getDataFromFile();//建立本机文件，获取数据
    void setData2File();//将数据重新存储
    void showAllInfo();
};
