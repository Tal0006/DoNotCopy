#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include "course.h"
#include <QVector>

class Student
{
public:
    Student(QString, QString, QString);
    ~Student();
    QString getId() const;
    void setId(const QString &newId);

    QString getName() const;
    void setName(const QString &newName);

    QString getIdentityCard() const;
    void setIdentityCard(const QString &newIdentityCard);

    QString getEmail() const;
    void setEmail(const QString &newEmail);

    QVector<Course> getCourses() const;
    void setCourses(const QVector<Course> &newCourses);

    void AddCourse(Course &c);
    void Print();

private:
    QString Id;
    QString Name;
    QString IdentityCard;
    QString Email;
    QVector<Course> courses;
};

#endif // STUDENT_H
