#include"student.h"
#include<qdebug.h>
#include<qfile.h>
#include<qstring.h>
#include<cstring>
bool inteNumber::operator==(const inteNumber& cmp)
{
    if (this->inte == cmp.inte&&this->inteClass == cmp.inteClass)
        return true;
    return false;
}

inteNumber::inteNumber(int inteClass, int inte)
{
    this->inteClass = inteClass;
    this->inte = inte;
}

void student::setSplNumber()
{
    int s=0;
    int m = 0;
    if (name != "") {
        for (int i = 0; i < name.length(); i += 2)
        {
            unsigned char a = name[i];
            unsigned char b = name[i + 1];
            m = (a - 176) * 94 + (b - 161);
            s*=10;
            s+=m;
        }
    }//每个学生有一个特殊编码，这个特殊编码是用一个哈希函数用名字生成的，这个哈希函数时网上搜的，据说很牛逼
    this->splNumber = s;

}//设置特殊编码

int student::getSplNumberByName(string name)
{
    int s = 0;
    int m=0;
    if (name != "") {
        for (int i = 0; i < name.length(); i += 2)
        {
            unsigned char a = name[i];
            unsigned char b = name[i + 1];
            m = (a - 176) * 94 + (b - 161);
            s*=10;
            s+=m;
        }
    }//静态函数生成特殊编码
    return s;
}

student::student(long id, string name, string sex, int age, int department, string othernote)
{
    this->id = id;
    this->name = name;
    this->sex = sex;
    this->age = age;
    this->department = department;
    this->otherNote = othernote;
    setSplNumber();
}

student::student(const student &stu)
{
    this->id = stu.id;
    this->name = stu.name;
    this->sex = stu.sex;
    this->age = stu.age;
    this->department = stu.department;
    this->otherNote = stu.otherNote;
    this->inteNum=stu.inteNum;
    setSplNumber();
}//拷贝构造，老实说，如果不涉及指针应该不需要拷贝构造的


student* studentMana::searchStudentBySplNum(int splNum)
{
    student* temp;
    vector<student>::iterator ite;
    for(ite=this->stu.begin();ite!=this->stu.end();ite++)
    {
        if(ite->getSplNumber()==splNum){
            temp=ite->getStuPtr();
            break;
        }
    }

    return temp;
}

bool student::modifyInfo(long id, string name, string sex, int age, int department, string othernote)
{
    this->id = id;
    this->name = name;
    this->sex = sex;
    this->age = age;
    this->department = department;
    this->otherNote = othernote;
    return true;
}//整体修改学生信息

bool student::addInte(int inteClass,int inte)
{
    vector<inteNumber>::iterator ite;
    inteNumber temp(inteClass, inte);
    ite = find(inteNum.begin(), inteNum.end(), temp);

    if (ite != inteNum.end())
    {
        //该学生已经有该兴趣，添加失败
        return false;
    }
    else
    {
        inteNum.push_back(temp);
        return true;
    }

}//增加一个兴趣


bool student::delInte(int inteClass,int inte)
{
    inteNumber temp(inteClass, inte);
    vector<inteNumber>::iterator ite;
    ite = find(inteNum.begin(), inteNum.end(), temp);
    if (ite == inteNum.end())
    {
        //没有该兴趣项，不用删除
        return false;
    }
    else
    {
        inteNum.erase(ite);
        return true;
    }

}//删除一个兴趣项



int studentMana::sumStudent = 0;
int studentMana::sumDepartment = 0;

void studentMana::getDataFromFile()
{
    ifstream ifs("StudentsInterestingManageSystem-StuData.txt");
        char str[1000];
        string s;
        long id; string name; string sex; int age; string departmentName; string othernote;
        int count = 0;
        while (ifs.getline(str, 1000))
        {
            istringstream _is(str);
            _is >> id >> name >> sex >> age >> departmentName >> othernote;
            addStudent(id, name, sex, age, departmentName, othernote);
            int inteClass;
            int inte;
            while(_is >> inteClass >> inte)
                addInte(name, inteClass, inte);
            qDebug()<<QString::fromStdString(name);

        }
        ifs.close();
}

void studentMana::setData2File()
{
    ofstream ofs("StudentsInterestingManageSystem-StuData.txt");
        vector<student>::iterator ite;
        map<int, string>::iterator ite1;
        for (ite = stu.begin(); ite != stu.end(); ite++)
        {
            ite1 = numDepartmentMap.find(ite->getDepartmentNum());
            ofs << ite->getId() << " " << ite->getName() << " " << ite->getSex() << " " << ite->getAge() << " " << ite1->second << " " << ite->getOtherNote();
            vector<inteNumber>::iterator inteIte;
            for (inteIte = ite->inteNum.begin(); inteIte != ite->inteNum.end(); inteIte++)
            {
                ofs << " "<<inteIte->inteClass << " " << inteIte->inte << " ";
            }
            ofs << endl;
        }
        ofs.close();
}

string studentMana::getDepartmentNameBySplNum(int splNum)
{
    map<int, string>::iterator iteDep;
    iteDep = numDepartmentMap.find(splNum);
    return iteDep->second;

}



studentMana::studentMana()
{
    //先留着，没想到要做什么事
    //那你留着干嘛
    //不知道，反正懒得删
    //那你打这么多字
    //要你管，你是谁啊
    //我是精分啊
}

bool studentMana::setDepartment(string departmentName)
{
    numDepartmentMap.insert(map<int, string>::value_type(sumDepartment, departmentName));
    departmentNumMap.insert(map<string, int>::value_type(departmentName, sumDepartment++));
    return true;
}

bool studentMana::addStudent(long id,string name,string sex,int age,string departmentName,string othernote)
{
    /*添加学生专业*/
    map<string, int>::iterator ite;
    ite = departmentNumMap.find(departmentName);
    int departmentNum;
    if (ite != departmentNumMap.end())
    {
         departmentNum = ite->second;
    }
    else
    {
        setDepartment(departmentName);
        ite = departmentNumMap.find(departmentName);
         departmentNum = ite->second;
    }//在字典中查找专业名称，如果有，则返回专业代码，没有则插入专业并返回专业代码。

    /*创建学生信息*/
    student a(id, name, sex, age, departmentNum, othernote);
    map<int, student*>::iterator ite1;

    stu.push_back(a);
    stuMap.insert(map<int, student*>::value_type(stu[0].getSplNumber(), stu[0].getStuPtr()));//在map中插入学生信息

    sumStudent++;
    return true;
}

bool studentMana::delStudentByName(string name)
{
    int splNum = student::getSplNumberByName(name);
    map<int, student*>::iterator ite;
    vector<student>::iterator iteStu;
    for (iteStu = stu.begin(); iteStu != stu.end();iteStu++)//从stu vector中删除这个学生的信息。
    {

        if (iteStu->getName()==name)
        {
            sumStudent--;
            stu.erase(iteStu);
            return true;
        }
    }

    return true;
}

student* studentMana::searchStudentById(int _id)
{
    vector<student>::iterator ite;
    for (ite = stu.begin(); ite != stu.end();ite++)
    {
        if (ite->getId() == _id)
        {
            return ite->getStuPtr();
        }
    }
    //没有找到该学生
    return nullptr;
}

student* studentMana::searchStudentByName(string _name)
{
    vector<student>::iterator ite;
    for (ite = stu.begin(); ite != stu.end(); ite++)
    {
        if (ite->getName() == _name)
        {
            return ite->getStuPtr();
        }
    }
    //没有找到该学生
    return nullptr;
}

vector<student> studentMana::searchStudentByDepartmentName(string _departmentName)
{
    vector<student> stuTemp;
    int _departmentNum;
    cout << _departmentName;
    map<string, int>::iterator iteDep = departmentNumMap.find(_departmentName);
    if (iteDep == departmentNumMap.end())
    {

        //没找到
        return stuTemp;
    }
    else
    {
        _departmentNum = iteDep->second;
    }

    vector<student>::iterator ite;
    for (ite = stu.begin(); ite != stu.end(); ite++)
    {
        if (ite->getDepartmentNum() == _departmentNum)
        {
            stuTemp.push_back(*ite);
        }
    }//找到了返回所有为该专业的人的指针
    return stuTemp;
}

bool studentMana::modifyStudentInfo(int _splNumber)
{

    long id; string name; string sex; int age; string departmentName; string othernote;
    cin >> id >> name >> sex >> age >> departmentName >> othernote;
    /*添加学生专业*/
    map<string, int>::iterator ite;
    ite = departmentNumMap.find(departmentName);
    int departmentNum;
    if (ite != departmentNumMap.end())
    {
        departmentNum = ite->second;
    }
    else
    {
        setDepartment(departmentName);
        ite = departmentNumMap.find(departmentName);
        departmentNum = ite->second;
    }//在字典中查找专业名称，如果有，则返回专业代码，没有则插入专业并返回专业代码。


    vector<student>::iterator iteStu;
    for (iteStu = stu.begin(); iteStu != stu.end(); ite++)
    {
        if (iteStu->getSplNumber() == _splNumber)
        {
            iteStu->modifyInfo(id, name, sex, age, departmentNum, othernote);
            return true;
        }
    }
    //没查找到，修改不成功
    return false;
}

bool studentMana::addInte(string name, int inteClass, int inte)
{
    student* temp;
    temp = searchStudentByName(name);
    if (temp == nullptr)
    {
        //寻找失败，没有此人
        return false;
    }
    else
    {
        temp->addInte(inteClass, inte);
        return true;
    }
}

bool studentMana::delInte(string name, int inteClass, int inte)
{
    student* temp;
    temp = searchStudentByName(name);
    if (temp == nullptr)
    {
        //寻找失败，没有此人
        return false;
    }
    else
    {
        temp->delInte(inteClass, inte);
        return true;
    }
}

void studentMana::showAllInfo()
{
    vector<student>::iterator ite;
    for (ite = stu.begin(); ite != stu.end(); ite++)
    {
        map<int, string>::iterator iteDep;
        iteDep = numDepartmentMap.find(ite->getDepartmentNum());
        int id=ite->getId();

        QString name=QString::fromStdString( ite->getName());
        QString sex=QString::fromStdString(ite->getSex());
        QString department=QString::fromStdString(iteDep->second);
        QString otherNote=QString::fromStdString(ite->getOtherNote());

        // cout << endl << "id:" << id << " name:" << ite->getName() << " age:" << ite->getAge() << " department:" << iteDep->second << " notes:" << ite->getOtherNote();
        qDebug() << "\nid:" << id << " name:" << name << " age:" << ite->getAge()<<" sex:"<<sex << " department:" << department<< " notes:" << otherNote;
        vector<inteNumber>::iterator _ite;
        for (_ite = ite->inteNum.begin(); _ite != ite->inteNum.end(); _ite++)
        {
            qDebug()<<"getHere";
            qDebug() << "\n\tinteClass:" << _ite->inteClass << " inte" << _ite->inte;
        }
    }


    map<int, string>::iterator ite1;
    for (ite1 = numDepartmentMap.begin(); ite1 != numDepartmentMap.end(); ite1++)
    {
        qDebug() << "\nite1DepartNUM:" << ite1->first << "  ite1Name:" <<QString::fromStdString( ite1->second);
    }
    //cout << endl << " sumStudents:" << sumStudent << " sumDepartment:" << sumDepartment;
}


