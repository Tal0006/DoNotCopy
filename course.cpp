#include "course.h"
#include <QString>
#include <iostream>

Course::Course(QString name, int Lec_Id, int year, QString semester)
{
    this->Name = name;
    this->LecturerId = Lec_Id;
    this->Year = year;
    this->Semester = semester;
    //std::cout << "Course Constructor\n";
}

Course::~Course()
{
    //std::cout << "Course Distructor\n";
}

void Course::Print()
{
    std::cout << "Course name: " << this->Name.toStdString() << std::endl;
    std::cout << "Lecturer Id: " << this->LecturerId << std::endl;
    std::cout << "Year: "        << this->Year << std::endl;
    std::cout << "Semester: "    << this->Semester.toStdString() << std::endl;
}


void Course::setName(const QString &newName)
{
    Name = newName;
}

QString Course::getName() const
{
    return Name;
}

int Course::getLecturerId() const
{
    return LecturerId;
}

void Course::setLecturerId(int newLecturerId)
{
    LecturerId = newLecturerId;
}

int Course::getYear() const
{
    return Year;
}

void Course::setYear(int newYear)
{
    Year = newYear;
}

QString Course::getSemester() const
{
    return Semester;
}

void Course::setSemester(const QString &newSemester)
{
    Semester = newSemester;
}
