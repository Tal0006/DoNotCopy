#ifndef COURSE_H
#define COURSE_H

#include <QString>

class Course
{
public:
    Course(QString,int,int,QString);
    ~Course();
    void Print();
    void setName(const QString &newName);

    QString getName() const;

    int getLecturerId() const;
    void setLecturerId(int newLecturerId);

    int getYear() const;
    void setYear(int newYear);

    QString getSemester() const;
    void setSemester(const QString &newSemester);

private:
    QString Name;
    int LecturerId;
    int Year;
    QString Semester;


};

#endif // COURSE_H
