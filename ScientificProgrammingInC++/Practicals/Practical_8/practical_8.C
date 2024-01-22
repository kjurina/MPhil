#include <iostream>
#include <string>
#include <array>

using namespace std;

class Researcher
{
private:
    string name_;
public:
    Researcher(const string&);

    string name()const;

    //Researcher(string name, int age);
    virtual string title()const = 0;
};
Researcher::Researcher(const string& a)
:
name_(a)
{
}
std::string Researcher::name()const
{
  return name_;
}

class Student : public Researcher
{
private:
    int hours_;
    
public:
    Student(const string&, int);
    int lectureHoursTakenPerWeek()const;
protected:
    int m_lectureHours;
};

Student::Student(const string& a, int h)
:
Researcher(a),
m_lectureHours(h)
{
}

int Student::lectureHoursTakenPerWeek()const
{
  return m_lectureHours;
}

class MPhilStudent : public Student
{
public:
    MPhilStudent(const string&, int);

    string title() const override;
};

MPhilStudent::MPhilStudent(const string& a, int h)
:
Student(a, h)
{
}

string MPhilStudent::title()const
{
    return "MPhil Student";
}

class PhDStudent : public Student
{
public:
    PhDStudent(const string& a, int h = 0);

    string title()const override;
};

PhDStudent::PhDStudent(const string& a, int h)
:
Student(a, h)
{
}

string PhDStudent::title()const
{
    return "PhD Student";
}

class Staff : public Researcher
{
public:
    Staff(const string&, int);

    //string title()const override;

    int lectureHoursGivenPerWeek()const;

protected:
    int m_LecturesGiven;
};

Staff::Staff(const string& a, int h)
:
Researcher(a),
m_LecturesGiven(h)
{
}

int Staff::lectureHoursGivenPerWeek()const
{
  return m_LecturesGiven;
}

class PostDoc : public Staff
{
public:
    PostDoc(const string& a, int h);

    string title()const override;
};

PostDoc::PostDoc(const string& a, int h)
:
Staff(a, h)
{
}

string PostDoc::title() const 
{
    return "PostDoc";
}

class HeadOfGroup : public Staff
{
public:
    HeadOfGroup(const string& a, int  = 0);

    string title()const override;
};

HeadOfGroup::HeadOfGroup(const string& a, int h)
:
Staff(a, h)
{
}

string HeadOfGroup::title() const 
{
    return "Head Of Group";
}

class Visitor : public Researcher
{
private:
    
public:
    Visitor(const string&);
    string title() const override;

protected:
};

Visitor::Visitor(const string& a)
:
Researcher(a)
{
}
string Visitor::title() const 
{
    return "Visitor";
}


int main()
{
    std::array<Researcher*,5> group;
    group[0] = new MPhilStudent("Zebedee", 18);
    group[1] = new PhDStudent("Florence");
    group[2] = new PostDoc("Dougal", 6);
    group[3] = new HeadOfGroup("Ermintrude");
    group[4] = new Visitor("Rusty");

    for(unsigned int i=0 ; i < 5 ; i++)
    {
        std::cout << "Researcher " << i << " is called " << (*group[i]).name() << " and is a " << group[i]->title() << std::endl;

        Student* s = dynamic_cast<Student*>(group[i]);
        if(s)
        {
            std::cout << s->name() << " is a student and must attend " << s->lectureHoursTakenPerWeek() << " hours of lectures per week" << std::endl;
        }

        Staff* s2 = dynamic_cast<Staff*>(group[i]);
        if(s2)
        {
            std::cout << s2->name() << " is a member of staff and must give " << s2->lectureHoursGivenPerWeek() << " hours of lectures per week" << std::endl;
        }
        
        if(!s2 && !s)
        {
            std::cout << group[i]->name() << " is neither student nor staff" << std::endl;
        }
        std::cout << "__________________________" << std::endl;
    }

    for(unsigned int i=0 ; i < 5 ; i++)
    {
        delete group[i];
    }
    return 0;
}
