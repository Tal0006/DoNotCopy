#include "student.h"
#include <QString>
#include <iostream>

Student::Student(QString name, QString id_card, QString email) :
    Name(name), IdentityCard(id_card), Email(email)
{
    //std::cout << "Student Constructor\n";
}

Student::~Student()
{
    //std::cout << "Student Distructor\n";
}

QString Student::getId() const
{
    return Id;
}

void Student::setId(const QString &newId)
{
    Id = newId;
}

QString Student::getName() const
{
    return Name;
}

void Student::setName(const QString &newName)
{
    Name = newName;
}

QString Student::getIdentityCard() const
{
    return IdentityCard;
}

void Student::setIdentityCard(const QString &newIdentityCard)
{
    IdentityCard = newIdentityCard;
}

QString Student::getEmail() const
{
    return Email;
}

void Student::setEmail(const QString &newEmail)
{
    Email = newEmail;
}

QVector<Course> Student::getCourses() const
{
    return courses;
}

void Student::setCourses(const QVector<Course> &newCourses)
{
    for(Course c : newCourses)
    {
        this->courses.append(c);
    }
}

void Student::AddCourse(Course &c)
{
    this->courses.append(c);
}

void Student::Print()
{
    //std::cout << "Id: " << this->Id.toStdString() << std::endl;
    std::cout << "Name: " << this->Name.toStdString() << std::endl;
    std::cout << "Id_Card: " << this->IdentityCard.toStdString() << std::endl;
    std::cout << "Email: " << this->Email.toStdString() << std::endl;
    std::cout << "Student Courses:\n";
    for(Course c : this->courses)
    {
        c.Print();
    }
}
