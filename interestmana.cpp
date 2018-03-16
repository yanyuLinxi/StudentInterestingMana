#include"InterestMana.h"
#include"qstring.h"
#include"qdebug.h"

void inte::setInteName(string na)
{
    this->inteName = na;

}

void inte::setInteSplNum(int splNum)
{
    this->inteSplNum = splNum;

}

bool inte::addStudentNum(int studentSplNum)
{
    vector<int>::iterator ite;
    ite = find(studentSplNumVector.begin(), studentSplNumVector.end(), studentSplNum);
    if (ite != studentSplNumVector.end())
    {
        //该学生已经在里面了，不用添加
        return false;
    }
    else
    {
        studentSplNumVector.push_back(studentSplNum);
        sumInteStudent++;
        return true;
    }
}

bool inte::delStudentNum(int studentSplNum)
{
    vector<int>::iterator ite;
    ite = find(studentSplNumVector.begin(), studentSplNumVector.end(), studentSplNum);
    if (ite == studentSplNumVector.end())
    {
        //该学生已经不在里面了，不用删除
        return false;
    }
    else
    {
        studentSplNumVector.erase(ite);
        sumInteStudent--;
        return true;
    }
}

bool inte::operator==(const inte& cmp)
{
    if (cmp.inteName == this->inteName)
        return true;
    return false;
}

bool inte::operator==(const int inteSplNum)
{
    if (this->inteSplNum == inteSplNum)
        return true;
    return false;
}

bool inte::operator==(const string inteName)
{
    if (this->inteName == inteName)
        return true;
    return false;
}

inte::inte()
{
    inteSplNum = 0;
    sumInteStudent = 0;
}

inteClass::inteClass()
{
    inteClassName = "";
    inteClassSplNum = 0;
    sumInte = 0;
}

void inteClass::setInteClassName(string na)
{
    this->inteClassName = na;
}

void inteClass::setInteClassSplNum(int num)
{
    this->inteClassSplNum = num;
}

bool inteClass::addStudentNum(string inteName, int studentSplNum)
{
    inte* temp = searchInteByInteName(inteName);
    if (temp != nullptr)
    {//找到了该兴趣
        if (temp->addStudentNum(studentSplNum))
            return true;//添加成功
        else
            return false;//添加失败
    }
    return false;//没找到该兴趣

}

bool inteClass::delStudentNum(string inteName, int studentSplNum)
{
    inte* temp = searchInteByInteName(inteName);
    if (temp != nullptr)
    {//找到了该兴趣
        if (temp->delStudentNum(studentSplNum))
            return true;//删除成功
        else
            return false;//删除失败
    }
    return false;//没找到该兴趣
}

bool inteClass::addInte(string inteName)
{
    vector<inte>::iterator ite;
    ite = find(inteVector.begin(), inteVector.end(), inteName);
    if (ite != inteVector.end())
    {
        //已经有该兴趣向了
        return false;
    }
    else
    {
        inte temp;
        temp.setInteName(inteName);
        temp.setInteSplNum(inteVector.size());

        splNumInteMap.insert(map<int, string>::value_type(temp.getInteSplNum(), temp.getInteName()));
        InteSplNumMap.insert(map<string, int>::value_type(temp.getInteName(), temp.getInteSplNum()));

        inteVector.push_back(temp);
        sumInte++;
        return true;
    }

}

bool inteClass::delInteBySplNum(int inteSplNum)
{
    vector<inte>::iterator ite;
    ite = find(inteVector.begin(), inteVector.end(), inteSplNum);
    if (ite == inteVector.end())
    {
        //没有此兴趣项
        return false;
    }
    else
    {
        inteVector.erase(ite);
        sumInte--;

        map<string, int>::iterator ite1;
        for (ite1 = InteSplNumMap.begin(); ite1 != InteSplNumMap.end(); ite1++)
        {
            if (ite1->second == inteSplNum)
            {
                InteSplNumMap.erase(ite1);
                break;
            }
        }
        splNumInteMap.erase(inteSplNum);

        return true;
    }
}

bool inteClass::delInteByName(string inteName)
{
    vector<inte>::iterator ite;

    ite = find(inteVector.begin(), inteVector.end(), inteName);
    if (ite == inteVector.end())
    {
        //没有此兴趣项
        return false;
    }
    else
    {
        //找到此兴趣项，删除
        inteVector.erase(ite);
        sumInte--;

        map<int, string>::iterator ite1;
        for (ite1 = splNumInteMap.begin(); ite1 != splNumInteMap.end(); ite1++)
        {
            if (ite1->second == inteName)
            {

                splNumInteMap.erase(ite1);
                break;
            }
        }
        InteSplNumMap.erase(inteName);


        return true;
    }
}

inte* inteClass::searchInteByInteName(string inteName)
{
    inte* temp;
    vector<inte>::iterator ite;
    ite = find(inteVector.begin(), inteVector.end(), inteName);
    if (ite == inteVector.end())
    {
        temp = nullptr;
    }
    else
    {
        temp = ite->getIntePtr();
    }
    return temp;
}

inte* inteClass::searchInteByInteSplNum(int inteSplNum)
{
    inte* temp;
    vector<inte>::iterator ite;
    ite = find(inteVector.begin(), inteVector.end(), inteSplNum);
    if (ite == inteVector.end())
    {
        //没有此兴趣项
        temp = nullptr;
    }
    else
    {
        temp = ite->getIntePtr();
    }
    return temp;
}

bool inteClass::operator==(const inteClass& cmp)
{
    if (this->inteClassName == cmp.inteClassName&&this->inteClassSplNum == cmp.inteClassSplNum)
        return true;
    return false;
}
bool inteClass::operator==(const int inteClassSplNum)
{
    if (this->inteClassSplNum == inteClassSplNum)
        return true;
    return false;
}
bool inteClass::operator==(const string inteClassName)
{
    if (this->inteClassName == inteClassName)
        return true;
    return false;
}

vector<vector<int>> inteClass::getInteClassStudentNum()
{
    vector<vector<int>> temp;
    vector<inte>::iterator ite;
    for (ite = inteVector.begin(); ite != inteVector.end(); ite++)
    {
        temp.push_back(ite->getStudentSplNum());
    }
    return temp;
}

inteClassMana::inteClassMana()
{
    sumInteClass = 0;
}

int inteClassMana::getInteClassSplNumByName(string inteClassName)
{
    map<string, int>::iterator ite;
    ite = inteClassSplNumMap.find(inteClassName);
    if (ite != inteClassSplNumMap.end())
    {
        //找到了该兴趣类名
        return inteClassSplNumMap[inteClassName];
    }
    return NULL;
}

int inteClassMana::getInteSplNumByName(string inteClassName, string inteName)
{
    inteClass* tempPtr = searchInteClassByInteClassName(inteClassName);
    if (tempPtr == nullptr)
    {
        //没找到
        return NULL;
    }
    else
    {
        map<string, int>::iterator ite;
        ite = tempPtr->InteSplNumMap.find(inteName);
        if (ite != tempPtr->InteSplNumMap.end())
            return tempPtr->InteSplNumMap[inteName];
        else
            return NULL;
    }
}

string inteClassMana::getInteNameBySplNum(int inteClassSplNum, int inteSplNum)
{
    inteClass* tempPtr = searchInteClassByInteClassSplNum(inteClassSplNum);
    if (tempPtr == nullptr)
    {
        //没找到
        return "";
    }
    else
    {
        map<int, string>::iterator ite;
        ite = tempPtr->splNumInteMap.find(inteSplNum);
        if (ite != tempPtr->splNumInteMap.end())
            return tempPtr->splNumInteMap[inteSplNum];
        else
            return "";
    }
}

string inteClassMana::getInteClassNameBySplNum(int inteClassSplNum)
{
    map<int, string>::iterator ite;
    ite = splNumInteClassMap.find(inteClassSplNum);
    if (ite != splNumInteClassMap.end())
    {
        return splNumInteClassMap[inteClassSplNum];
    }
    return "";
}

bool inteClassMana::addInte(string inteClassName,string inteName)
{
    vector<inteClass>::iterator ite;
    ite = find(inteClassVector.begin(), inteClassVector.end(), inteClassName);
    if (ite != inteClassVector.end())
    {
        vector<inte>::iterator ite1;
        ite1 = find(ite->inteVector.begin(), ite->inteVector.end(), inteName);
        if (ite1 != ite->inteVector.end())
        {
            //已有该兴趣类和兴趣项
            return false;
        }
        else
        {
            ite->addInte(inteName);
            return true;
        }

    }
    else
    {
        inteClass temp;
        temp.setInteClassName(inteClassName);
        temp.setInteClassSplNum(inteClassVector.size());
        temp.addInte(inteName);
        inteClassVector.push_back(temp);
        inteClassSplNumMap.insert(map<string, int>::value_type(temp.getInteClassName(), temp.getInteClassSplNum()));
        splNumInteClassMap.insert(map<int, string>::value_type(temp.getInteClassSplNum(), temp.getInteClassName()));
        sumInteClass++;
        return true;
    }
}

bool inteClassMana::addStudentNum(string inteClassName, string inteName, int studentSplNum)
{
    inteClass* temp = searchInteClassByInteClassName(inteClassName);
    if (temp != nullptr)
    {
        if (temp->addStudentNum(inteName, studentSplNum))
            return true;//添加成功
        else
            return false;//添加失败
    }
    else
        return false;//没找到该兴趣类
}
bool inteClassMana::delStudentNum(string inteClassName, string inteName, int studentSplNum)
{
    inteClass* temp = searchInteClassByInteClassName(inteClassName);
    if (temp != nullptr)
    {
        if (temp->delStudentNum(inteName, studentSplNum))
            return true;//删除成功
        else
            return false;//删除失败
    }
    else
        return false;//没找到该兴趣类
}

bool inteClassMana::delInteClassByName(string inteClassName)
{
    vector<inteClass>::iterator ite;
    ite = find(inteClassVector.begin(), inteClassVector.end(), inteClassName);
    if (ite == inteClassVector.end())
    {
        //没有这个兴趣类
        return false;
    }
    else
    {
        inteClassVector.erase(ite);
        sumInteClass--;

        //删除map里的键值
        map<int, string>::iterator ite1;
        for (ite1 = splNumInteClassMap.begin();ite1 != splNumInteClassMap.end(); ite1++)
        {
            if (ite1->second == inteClassName)
            {
                splNumInteClassMap.erase(ite1);
                break;
            }
        }

        inteClassSplNumMap.erase(inteClassName);
        return true;
    }

}

bool inteClassMana::delInteByName(string inteClassName, string inteName)
{
    vector<inteClass>::iterator ite;
    ite = find(inteClassVector.begin(), inteClassVector.end(), inteClassName);
    if (ite == inteClassVector.end())
    {
        //没有这个兴趣类
        return false;
    }
    else
    {
        if(ite->delInteByName(inteName))
            return true;
        return false;
    }
}

bool inteClassMana::delInteClassByInteClassSplNum(int inteClassSplNum)
{
    vector<inteClass>::iterator ite;

    ite=find(inteClassVector.begin(), inteClassVector.end(), inteClassSplNum);
    if (ite==inteClassVector.end())
    {
        //没有这个兴趣类
        return false;
    }
    else
    {

        inteClassVector.erase(ite);
        sumInteClass--;

        //删除字典中键对值
        map<string, int>::iterator ite1;
        for (ite1 = inteClassSplNumMap.begin(); ite1 != inteClassSplNumMap.end(); ite1++)
        {
            if (ite1->second == inteClassSplNum)
            {
                inteClassSplNumMap.erase(ite1);
                break;
            }
        }
        splNumInteClassMap.erase(inteClassSplNum);
        return true;
    }

}
inteClass* inteClassMana::searchInteClassByInteClassSplNum(int inteClassSplNum)
{
    inteClass* temp;
    vector<inteClass>::iterator ite;
    ite = find(inteClassVector.begin(), inteClassVector.end(), inteClassSplNum);
    if (ite == inteClassVector.end())
    {
        temp = nullptr;
    }
    else
    {
        temp = ite->getInteClassPtr();
    }
    return temp;
}

inteClass* inteClassMana::searchInteClassByInteClassName(string inteClassName)
{
    inteClass* temp;
    vector<inteClass>::iterator ite;
    ite = find(inteClassVector.begin(), inteClassVector.end(), inteClassName);
    if (ite == inteClassVector.end())
    {
        temp = nullptr;
    }
    else
    {
        temp = ite->getInteClassPtr();
    }
    return temp;
}

vector<vector<vector<int>>> inteClassMana::getInteClassManaStudentNum()
{
    vector<vector<vector<int>>> temp;
    vector<inteClass>::iterator ite;
    for (ite = inteClassVector.begin(); ite != inteClassVector.end(); ite++)
    {
        temp.push_back(ite->getInteClassStudentNum());
    }
    return temp;
}

void inteClassMana::showAllInfo()
{
    vector<inte> _inteVector;
    vector<inteClass> _inteClassVector=getInteClassVector();
    vector<int> _studentVector;

    vector<inte>::iterator _inteIte;
    vector<inteClass>::iterator _inteClassIte;

    for (_inteClassIte = _inteClassVector.begin(); _inteClassIte != _inteClassVector.end(); _inteClassIte++)
    {
       // cout << endl << _inteClassIte->getInteClassName() << ":";
        QString inteClassName=QString::fromStdString( _inteClassIte->getInteClassName());
        qDebug()<<"\n"<<inteClassName<<":";
        _inteVector = _inteClassIte->getInteVector();
        for (_inteIte = _inteVector.begin(); _inteIte != _inteVector.end(); _inteIte++)
        {
            //cout << endl <<"\t"<< _inteIte->getInteName() << ":";
            QString inteName=QString::fromStdString(_inteIte->getInteName());
            qDebug()<<"\n\t"<<inteName<<":";
            _studentVector = _inteIte->getStudentSplNum();
            for (int i=0;i<_studentVector.size();i++)
            {
                qDebug()<<"\n\t\tstudents:"<<_studentVector[i];
                //cout << endl << "\t\tstudents:" << _studentVector[i];
            }
        }
    }

    //下面代码为测试兴趣类是否争取存储的代码
    /*vector<inteClass>::iterator _ite;
    for (_ite = inteClassVector.begin(); _ite != inteClassVector.end(); _ite++)
    {
        cout << _ite->getInteClassName() << "类有:\n";
        vector<inte>::iterator _ite1;
        for (_ite1 = _ite->inteVector.begin(); _ite1 != _ite->inteVector.end(); _ite1++)
        {
            cout << _ite1->getInteName() << endl;
        }
        cout << endl;
    }*/
}

void inteClassMana::getDataFromFile()
{
    ifstream ifs("InteData.txt");
    char str[1000];
    string s;
    string inteClassName;
    string inteName;
    int studentSplNum;
    while (ifs.getline(str, 1000))
    {
        istringstream _is(str);
        _is >> inteClassName >> inteName;
        addInte(inteClassName, inteName);
        while (_is >> studentSplNum)
        {
            addStudentNum(inteClassName, inteName, studentSplNum);
        }
    }
    ifs.close();
}

void inteClassMana::setData2File()
{
    ofstream ofs("InteData.txt");
    vector<inteClass>::iterator _inteClassIte;
    vector<inte>::iterator _inteIte;

    vector<inteClass> _inteClassVector = getInteClassVector();
    vector<inte> _inteVector;

    for (_inteClassIte = _inteClassVector.begin(); _inteClassIte != _inteClassVector.end(); _inteClassIte++)
    {

        _inteVector = _inteClassIte->getInteVector();
        for (_inteIte = _inteVector.begin(); _inteIte != _inteVector.end(); _inteIte++)
        {
            ofs << _inteClassIte->getInteClassName() << " " << _inteIte->getInteName() << " ";
            vector<int> _studentVector=_inteIte->getStudentSplNum();
            for (int i=0;i<_studentVector.size();i++)
            {
                ofs << _studentVector[i] << " ";
            }
            ofs << endl;
        }

    }
    ofs.close();
}
