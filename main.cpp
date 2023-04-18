#include "mainwindow.h"

#include <QString>
#include <QApplication>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <qnetworkaccessmanager.h>
#include <iostream>

void AddToDB(QVector<Student>&, QVector<Course>&, QVector<Lecturer>&);
void AddStudents(QVector<Student> &Students);
void AddCourses(QVector<Course> &Courses);
void AddLecturers(QVector<Lecturer> &Lecturers);

int main(int argc, char *argv[])
{
    /*QVector<Student> Students;
    QVector<Course> Courses;
    QVector<Lecturer> Lecturers;
    AddToDB(Students, Courses, Lecturers);*/

    QApplication a(argc, argv);
    MainWindow w;
    //w.setCourses(Courses);
    //w.setLecturers(Lecturers);
    //w.setStudents(Students);

    w.show();
    return a.exec();
}


void AddToDB(QVector<Student> &Students, QVector<Course> &Courses, QVector<Lecturer> &Lecturers)
{
    QString filename = "C:/Users/user/Desktop/קורסים.xlsx";
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    db.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + QString(filename) + "");
    if(db.open())
        qDebug() << "Excel Is Connected";
    else
        qDebug() << "Excel Is Not Connected";


    QSqlQuery query(db);

    query.prepare("SELECT * FROM [" + QString("Students_") + "$A1:D8]");

    if(query.exec())
    {
        while (query.next())
        {
            Student S(query.value(1).toString(),query.value(2).toString(),query.value(3).toString());
            Students.append(S);
        }

    }
    AddStudents(Students);

    query.prepare("SELECT * FROM [" + QString("Lecturers") + "$A1:D9]");

    if(query.exec())
    {
        while (query.next())
        {
            Lecturer L(query.value(0).toString(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString());
            Lecturers.append(L);
        }

    }
    AddLecturers(Lecturers);

    query.prepare("SELECT * FROM [" + QString("Courses1") + "$A1:E6]");

    if(query.exec())
    {
        while (query.next())
        {
            Course C(query.value(1).toString(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toString());
            Courses.append(C);
        }

    }
    AddCourses(Courses);
}


void AddStudents(QVector<Student> &Students)
{
    QVector<QByteArray> cdata;
    for(Student S : Students)
    {
        QJsonObject obj;
        obj["Name"] = S.getName();
        obj["IdentityCard"] = S.getIdentityCard();
        obj["Email"] = S.getEmail();
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();
        cdata.append(data);
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    const QUrl url(QStringLiteral("https://localhost:44363/api/Student/Add"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply;

    for(int i = 0; i < cdata.size(); i++)
    {
        reply = manager->post(request, cdata[i]);
        QObject::connect(reply, &QNetworkReply::finished, [=](){
            if(reply->error() == QNetworkReply::NoError){
                QString contents = QString::fromUtf8(reply->readAll());
                qDebug() << contents;
            }
            else{
                QString err = reply->errorString();
                qDebug() << err;
            }
            reply->deleteLater();
        });
    }
}


void AddCourses(QVector<Course> &Courses)
{
    QVector<QByteArray> cdata;
    for(Course S : Courses)
    {
        QJsonObject obj;
        obj["Name"] = S.getName();
        obj["LecturerId"] = S.getLecturerId();
        obj["Semester"] = S.getSemester();
        obj["Year"] = S.getYear();
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();
        cdata.append(data);
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    const QUrl url(QStringLiteral("https://localhost:44363/api/Course/Add"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply;

    for(int i = 0; i < cdata.size(); i++)
    {
        reply = manager->post(request, cdata[i]);
        QObject::connect(reply, &QNetworkReply::finished, [=](){
            if(reply->error() == QNetworkReply::NoError){
                QString contents = QString::fromUtf8(reply->readAll());
                qDebug() << contents;
            }
            else{
                QString err = reply->errorString();
                qDebug() << err;
            }
            reply->deleteLater();
        });
    }
}


void AddLecturers(QVector<Lecturer> &Lecturers)
{
    QVector<QByteArray> cdata;
    for(Lecturer S : Lecturers)
    {
        QJsonObject obj;
        obj["Name"] = S.getName();
        obj["Email"] = S.getEmail();
        obj["PasswordHash"] = S.getPasswordHash();
        QJsonDocument doc(obj);
        QByteArray data = doc.toJson();
        cdata.append(data);
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    const QUrl url(QStringLiteral("https://localhost:44363/api/Lecturer/Add"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply;

    for(int i = 0; i < cdata.size(); i++)
    {
        reply = manager->post(request, cdata[i]);
        QObject::connect(reply, &QNetworkReply::finished, [=](){
            if(reply->error() == QNetworkReply::NoError){
                QString contents = QString::fromUtf8(reply->readAll());
                qDebug() << contents;
            }
            else{
                QString err = reply->errorString();
                qDebug() << err;
            }
            reply->deleteLater();
        });
    }
}
