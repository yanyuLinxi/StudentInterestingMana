#pragma  once
#ifndef INTERESTMANA_H
#define INTERESTMANA_H
#include<iostream>
#include<string>
#include<Windows.h>
#include<deque>
#include<list>
#include<vector>
#include<map>
#include<fstream>
#include<sstream>
#include <algorithm>
using namespace std;

#endif // INTERESTMANA_H

class inte {
private:
    string inteName;
    int inteSplNum;//inteSplNum=>interesting Special Number兴趣特殊编码，后面的inteClassSplNum就是兴趣类的特殊编码，和学生一样，为了节约空间，设置的特殊编码

    vector<int> studentSplNumVector;//这个用来存储选择该兴趣项的所有学生的特殊编码，一样的为了节省空间设置为int型
public:
    int sumInteStudent;
    inte();
    bool addStudentNum(int);
    inline vector<int> getStudentSplNum() { return this->studentSplNumVector; }
    void setInteName(string);
    inline string getInteName() { return inteName; }
    bool delStudentNum(int);
    void setInteSplNum(int);
    bool operator == (const inte& cmp);//重载==运算符，这个不要轻易重载，由于我只在迭代器时要用，所以问题不大
    bool operator == (const int);
    bool operator == (const string);
    inline int getInteSplNum() { return this->inteSplNum; }//获取该兴趣的特殊编码
    inline inte* getIntePtr() { return this; }//获取该对象的指针，实践证明，比引用好用多了
};

class inteClass {
private:
    string inteClassName;//兴趣类的名称
    int inteClassSplNum;
    int sumInte;//该兴趣类下的兴趣总数
public:
    vector<inte> inteVector;//将该兴趣类下的兴趣用数组全部存储下来
    map<int, string>splNumInteMap;//map，用来将兴趣的特殊编码和名字之间进行转换
    map<string, int>InteSplNumMap;//名字的意思解释一下：inteSplNumMap=>interesting Special Number Map兴趣转特殊编码map
    inteClass();
    void setInteClassName(string);
    inline string getInteClassName() { return this->inteClassName; }
    void setInteClassSplNum(int);
    inline int getInteClassSplNum() { return this->inteClassSplNum; }
    inte* searchInteByInteSplNum(int);//通过特殊编码来获得兴趣的指针
    inte* searchInteByInteName(string);
    bool addInte(string);//增加一个兴趣
    bool delInteBySplNum(int inteSplNum);
    bool delInteByName(string inteName);
    vector<vector<int>> getInteClassStudentNum();//获取该兴趣类下的所有学生，这个结构很复杂，虽然实现了，但后来并没有用这个
    inline vector<inte> getInteVector() { return inteVector; }
    inline inteClass* getInteClassPtr() { return this; }
    bool operator == (const inteClass& cmp);//一样只用在迭代器里，所以就重载了
    bool operator == (const int);
    bool operator == (const string);
    bool addStudentNum(string inteName, int splNum);//为一个兴趣项添加学生编码
    bool delStudentNum(string inteName, int splNum);
};


class inteClassMana {
public:
    vector<inteClass> inteClassVector;//存储所有兴趣类
    int sumInteClass;//所有兴趣类的总数
    inteClassMana();
    map<int, string>splNumInteClassMap;//兴趣类的特殊编码到名称的转换map
    map<string, int>inteClassSplNumMap;

    void getDataFromFile();//从文件中载入数据
    void setData2File();//保存数据
    int getInteSplNumByName(string inteClassName, string inteName);//通过兴趣的名字获取特殊编码
    string getInteNameBySplNum(int inteClassSplNum, int inteSplNum);//通过兴趣的特殊编码获取名字
    int getInteClassSplNumByName(string inteClassName);//通过兴趣类的名字获取特殊编码
    string getInteClassNameBySplNum(int inteClassSplNum);//通过兴趣类的特殊编码获取名字
    bool addInte(string inteClassName,string intName);//添加兴趣
    bool delInteClassByName(string);//通过名字删除兴趣类
    bool delInteClassByInteClassSplNum(int);//通过兴趣类的特殊编码删除兴趣类
    bool delInteByName(string inteClassName, string inteName);
    vector<vector<vector<int>>> getInteClassManaStudentNum();//获取所有学生的特殊编码，我真的不知道自己脑子是咋想的，整出个这么复杂的结构，我自己些迭代器都理了好半天
    inline vector<inteClass> getInteClassVector() { return inteClassVector; }//获取兴趣类的数组
    inteClass* searchInteClassByInteClassSplNum(int);//通过兴趣类的特殊编码找到兴趣类
    inteClass* searchInteClassByInteClassName(string);
    bool addStudentNum(string inteClassName, string inteName, int studentSplNum);//为一个兴趣类下的某个兴趣添加一个学生
    bool delStudentNum(string inteClassName, string inteName, int studentSplNum);
    void showAllInfo();//展示所有信息，测试用
};
