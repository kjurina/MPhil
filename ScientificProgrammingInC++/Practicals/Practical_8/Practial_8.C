#include <iostream>
#include <assert.h>

/* Practical 8 specific code starts here.
 */

class Researcher{
public:
  // Construct a Researcher using their name
  Researcher(const std::string&);
  std::string name()const;
  // A researcher does not have a title as such, but all researchers must have a title.
  virtual std::string title()const = 0;
private:
  std::string m_name;
};

// Initialize the name of the researcher
Researcher::Researcher(const std::string& a) : m_name(a)
{
}

// Return the researcher's name
std::string Researcher::name()const
{
  return m_name;
}

// One way of proceeding is to then split between students and non-students:

class Student : public Researcher{
public:
  // Construct a Student from their name and number of hours of lectures.
  Student(const std::string&, int);
  int lectureHoursTakenPerWeek()const;
  // Note: A student does not have a title as such either, so we do not implement the title() function here.
protected:
  // The number of lecture hours can be changed by/available to both MPhilStudent and PhdStudent
  int m_lectureHours;
};

// The name part of the construction is passed off to the Researcher base-class.
Student::Student(const std::string& a, int h) : Researcher(a), m_lectureHours(h)
{
}

int Student::lectureHoursTakenPerWeek()const
{
  return m_lectureHours;
}

class MPhilStudent : public Student{
public:
  // Construct an MPhil student from their name and no. of lecture hours.
  MPhilStudent(const std::string&, int);
  // This implements the title() function from Researcher.
  std::string title()const override;
};

// An MPhil Student just constructs its base-class Student.
MPhilStudent::MPhilStudent(const std::string& a, int h) : Student(a, h)
{
}

// Define the function to return a particular label for the MPhil Student.
std::string MPhilStudent::title()const{
  return "MPhil Student";
}

class PhdStudent : public Student{
public:
  // Construct a PhD student from their name and no. of lecture hours (zero by default).
  PhdStudent(const std::string& a, int h = 0);
  std::string title()const override;  
};

// A PhD student just passes its initialization onto its Student base class.
PhdStudent::PhdStudent(const std::string& a, int h) : Student(a, h)
{
}

std::string PhdStudent::title()const{
  return "PhD Student";
}

// All Staff members are researchers, and give lectures.
class Staff : public Researcher{
public:
  // Staff constructed from a name and no. of hours lectured.
  Staff(const std::string& a, int h);
  virtual int lectureHoursGivenPerWeek()const;
  // Staff class does not implement the title() function of Researcher;
  // this is left up to a further derived class.
protected:
  // Protected so that both the PostDoc and HeadOfGroup classes can access/change the value.
  int hoursPerWeek;
};

// Construct a staff member via their name and no. of hours to lecture.
Staff::Staff(const std::string& a, int h) : Researcher(a), hoursPerWeek(h)
{
}

int Staff::lectureHoursGivenPerWeek()const{
  return hoursPerWeek;
}

class PostDoc : public Staff{
public:
  // Construct a post-doc from their name and no. of hours to lecture
  PostDoc(const std::string& a, int h);
  std::string title()const override;
};

// Pass construction parameters to the Staff base-class
PostDoc::PostDoc(const std::string& a, int h) : Staff(a, h)
{
}

std::string PostDoc::title()const{
  return "Post Doc.";
}

class HeadOfGroup : public Staff{
public:
  // Construct head-of-group from their name and no. of hours to lecture (zero by default).
  HeadOfGroup(const std::string& a, int h = 0);
  std::string title()const override;
};

// Initialize head of group by the Staff base-class
HeadOfGroup::HeadOfGroup(const std::string& a, int h) : Staff(a, h)
{
}

std::string HeadOfGroup::title()const{
  return "Head Of Group";
}

// Neither Staff nor Student
class Visitor : public Researcher
{
public:
  Visitor(const std::string& a);
  std::string title()const override;
};

// Visitor only has a name; passed onto the Researcher base-class.
Visitor::Visitor(const std::string& a) : Researcher(a)
{
}

std::string Visitor::title()const
{
  return "Visitor";
}

int main(void)
{
  Researcher* group[5];
  group[0] = new MPhilStudent("Zebedee", 18);
  group[1] = new PhdStudent("Florence");
  group[2] = new PostDoc("Dougal", 6);
  group[3] = new HeadOfGroup("Ermintrude");
  group[4] = new Visitor("Rusty");

  for(unsigned int i=0 ; i < 5 ; i++)
  {
    std::cout << "Researcher " << i << " is called " << group[i]->name() << " and is a " << group[i]->title() << std::endl;

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
