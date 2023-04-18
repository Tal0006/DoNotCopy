#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QAuthenticator>
#include <QNetworkProxy>
#include <QUrl>
#include <QUrlQuery>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QTextEdit>
#include <QtWidgets>
#include <QApplication>
#include <QCamera>
#include <QMediaDevices>
#include <QMediaCaptureSession>
#include <QVideoWidget>
#include <QMediaRecorder>
#include <QMediaPlayer>
#include "course.h"
#include "lecturer.h"
#include "student.h"

extern QString lec_id;
extern int NumOfCourses;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<Lecturer> getLecturers() const;
    void setLecturers(const QVector<Lecturer> &newLecturers);

    void setCourses(const QVector<Course> &newCourses);

    void setStudents(const QVector<Student> &newStudents);


signals:
    void replyDataReady(const QByteArray &data);


public slots:
    QByteArray GetCourses(QString);
    void replyFinished(QNetworkReply* reply);
    void Post(QString);
    QVector<QByteArray> ReadXlFile(QString);
    void AddCoursesToLec(QStringList Courses);
    //void AddLecturers();
    void processItem(const QString &itemId, const QString &itemName);
    void onButtonClicked();
    void onTextChanged(const QString &text);
    void PostCourse(QString Name, QString Id);
    void Test();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();


    void on_Login_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_35_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager;
    QVector<Lecturer> Lecturers;
    QVector<Student> Students;
    QVector<Course> Courses;
    bool m_buttonClicked;
};
#endif // MAINWINDOW_H


