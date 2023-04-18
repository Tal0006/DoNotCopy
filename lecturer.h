#ifndef LECTURER_H
#define LECTURER_H

#include <QString>
#include "course.h"
#include <QVector>

class Lecturer
{
public:
    Lecturer(QString, QString, QString, QString);
    ~Lecturer();
    QString getId() const;
    void setId(const QString &newId);
    QString getName() const;
    void setName(const QString &newName);
    QString getEmail() const;
    void setEmail(const QString &newEmail);
    QString getPasswordHash() const;
    void setPasswordHash(const QString &newPasswordHash);
    void AddCourses(const Course &course);
    QVector<Course> getCourses() const;
    void setCourses(const QVector<Course> &newCourses);
    void Print();

private:
    QString Id;
    QString Name;
    QString Email;
    QString PasswordHash;
    QVector<Course> Courses;

};

#endif // LECTURER_H
