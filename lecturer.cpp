#include "lecturer.h"
#include <QString>
#include "course.h"
#include <QVector>
#include <iostream>

Lecturer::Lecturer(QString id, QString name, QString email, QString pass)
{
    this->Id = id;
    this->Name = name;
    this->Email = email;
    this->PasswordHash = pass;
    //std::cout << "Lecturer Constructor\n";
}

Lecturer::~Lecturer()
{
    //std::cout << "Lecturer Distructor\n";
}

void Lecturer::setPasswordHash(const QString &newPasswordHash)
{
    PasswordHash = newPasswordHash;
}


void Lecturer::AddCourses(const Course &course)
{
    this->Courses.append(course);
}

QVector<Course> Lecturer::getCourses() const
{
    return Courses;
}

void Lecturer::setCourses(const QVector<Course> &newCourses)
{
    for(Course c : newCourses)
    {
        this->Courses.append(c);
    }
}


void Lecturer::Print()
{
    std::cout << "Lecturer id: " << this->Id.toStdString() << std::endl;
    std::cout << "Lecturer name: " << this->Name.toStdString() << std::endl;
    std::cout << "Lecturer Email: " << this->Email.toStdString() << std::endl;
    std::cout << "Lecturer Courses:\n";
    for(Course c : this->Courses)
    {
        c.Print();
    }
}

QString Lecturer::getPasswordHash() const
{
    return PasswordHash;
}

QString Lecturer::getEmail() const
{
    return Email;
}

void Lecturer::setEmail(const QString &newEmail)
{
    Email = newEmail;
}

QString Lecturer::getName() const
{
    return Name;
}

void Lecturer::setName(const QString &newName)
{
    Name = newName;
}

QString Lecturer::getId() const
{
    return Id;
}

void Lecturer::setId(const QString &newId)
{
    Id = newId;
}

