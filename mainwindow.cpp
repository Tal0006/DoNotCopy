#include "mainwindow.h"
#include "qaudioinput.h"
#include "qgridlayout.h"
#include "qmediaformat.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QAxObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtCore>
#include <QtHttpServer>
#include <QComboBox>
#include <QInputDialog>
#include <QtWidgets>

QString lec_id;
int NumOfCourses;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

}


MainWindow::~MainWindow()
{
    delete manager;
    delete ui;
}



void MainWindow::on_Login_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::setCourses(const QVector<Course> &newCourses)
{
    for(Course c : newCourses)
    {
        this->Courses.append(c);
    }
}

void MainWindow::setStudents(const QVector<Student> &newStudents)
{
    for(Student s : newStudents)
    {
        this->Students.append(s);
    }
}

QVector<Lecturer> MainWindow::getLecturers() const
{
    return Lecturers;
}

void MainWindow::setLecturers(const QVector<Lecturer> &newLecturers)
{
    for(Lecturer L : newLecturers)
    {
        this->Lecturers.append(L);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}



void MainWindow::on_pushButton_4_clicked()
{
    QString username = ui->Lec_UN_Line_Edit->text();
    QString password = ui->Lec_Pass_Line_Edit->text();
    manager = new QNetworkAccessManager(this);
    const QUrl url(QStringLiteral("https://localhost:44363/api/Home/LoginIsValid"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject obj;
    obj["UserName"] = username;
    obj["Password"] = password;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();
    QNetworkReply *reply;
    reply = manager->post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
    if(reply->error() == QNetworkReply::NoError)
    {
        QString contents = QString::fromUtf8(reply->readAll());
        qDebug() << contents;
        lec_id = contents;
        ui->stackedWidget->setCurrentIndex(4);

        QByteArray Lec_Cour = GetCourses(contents);
        qDebug() << "Lec_Cour: " << Lec_Cour;
        //AddCoursesToLec(Lec_Cour);
    }
    else{
        QMessageBox::information(this, tr("File Name"),"User Name or password incorrect");
        QString err = reply->errorString();
        qDebug() << err;
    }
    reply->deleteLater();
    });

}

//void AddCoursesToLec()
//{
//    QVector<QPushButton> courses_bt;

//    for(auto a : Lec_courses)
//    {

//    }
//}

void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}



void MainWindow::on_pushButton_12_clicked()
{
    QString File_name = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All Files (*.*);;Text File (*txt);;Music File(.mp3)");
    QMessageBox::information(this, tr("File Name"), File_name);
    //GetCourses();
    Post(File_name);
}

QByteArray MainWindow::GetCourses(QString Lec_Id)
{
    QUrl url(QStringLiteral("https://localhost:44363/api/Course/GetLecturerCourse"));
    QUrlQuery query;

    query.addQueryItem("LecturerId", Lec_Id);
    url.setQuery(query.query());
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->get(QNetworkRequest(url));

//    connect(reply, &QNetworkReply::finished, this, [this, reply]()
//    {
//        qDebug() << "Reply: " << reply->readAll();
//        replyFinished(reply);
//    });

    connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() == QNetworkReply::NoError) {
                // Read the response data from the reply
                QByteArray responseData = reply->readAll();
                qDebug() << responseData;
                // Parse the response data as a JSON object
                QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
                QJsonObject jsonObject = jsonDocument.object();
                QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
                QJsonArray jsonArray = jsonResponse.array();

                QStringList courseNames;
                for (int i = 0; i < jsonArray.size(); i++) {
                    QJsonObject obj = jsonArray[i].toObject();
                    QString courseName = obj["courseName"].toString();
                    courseNames.append(courseName);
                }
                NumOfCourses = courseNames.size();
                AddCoursesToLec(courseNames);
                // Extract the item data from the JSON object
                QString itemId = jsonObject.value("id").toString();
                QString itemName = jsonObject.value("courseName").toString();
                //QGridLayout* layout = new QGridLayout();
                //ui->listView->setLayout(layout);

                /*QVector<QPushButton*> buttons2DVector(8);
                buttons2DVector.resize(8);
                QPushButton *b = new QPushButton(itemName);
                layout->addWidget(b);
                buttons2DVector[0] = b;*/

                // Call another function to process the item data
                processItem(itemId, itemName);
            } else {
                qDebug() << "Error:" << reply->errorString();
            }

            // Clean up the network manager and reply objects

            reply->deleteLater();
            manager->deleteLater();
        });

    return reply->readAll();

}


//QStringList parseResponse(QString response)
//{
//    QJsonDocument jsonResponse = QJsonDocument::fromJson(response.toUtf8());
//    QJsonArray jsonArray = jsonResponse.array();

//    QStringList courseNames;
//    for (int i = 0; i < jsonArray.size(); i++) {
//        QJsonObject obj = jsonArray[i].toObject();
//        QString courseName = obj["courseName"].toString();
//        courseNames.append(courseName);
//    }

//    return courseNames;
//}

void MainWindow::processItem(const QString &itemId, const QString &itemName)
{
    qDebug() << "id: " << itemId << "\nName: " << itemName;
}

void MainWindow::replyFinished(QNetworkReply* reply)
{
    // Get the reply data
    QByteArray data = reply->readAll();

    // Emit the data ready signal
    emit replyDataReady(data);

    // Delete the reply object
    reply->deleteLater();
}



void MainWindow::on_pushButton_13_clicked()
{
    //QString File_name = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "All Files (*.*);;Text File (*txt);;Music File(.mp3)");
    //QMessageBox::information(this, tr("File Name"), File_name);
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_pushButton_22_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_pushButton_30_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}




void MainWindow::Post(QString File_name)
{
    manager = new QNetworkAccessManager(this);
    const QUrl url(QStringLiteral("https://localhost:44363/api/Student/Add"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QVector<QByteArray> cdata = ReadXlFile(File_name);
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


QVector<QByteArray> MainWindow::ReadXlFile(QString File_Name)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    db.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + QString(File_Name) + "");
    if(db.open())
        qDebug() << "Excel Is Connected";
    else
        qDebug() << "Excel Is Not Connected";


    QSqlQuery query(db);

    query.prepare("SELECT * FROM [" + QString("Students") + "$A8:D15]");
    QVector<QByteArray> cdata;
    if(query.exec())
    {
        while (query.next())
        {
            QJsonObject obj;
            //obj["Id"] = query.value(0).toInt();
            obj["Name"] = query.value(1).toString();
            //obj["Year"] = query.value(3).toInt();
            //obj["Semester"] = query.value(4).toString();
            obj["IdentifyCard"] = query.value(2).toString();
            obj["Email"] = query.value(3).toString();
            QJsonDocument doc(obj);
            QByteArray data = doc.toJson();
            cdata.append(data);
        }

    }

    return cdata;

}

void MainWindow::PostCourse(QString Name, QString Id)
{
    manager = new QNetworkAccessManager(this);
    const QUrl url(QStringLiteral("https://localhost:44363/api/Course/AddCourse"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["Name"] = Name;
    json["LecturerId"] = Id;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QNetworkReply *reply;
    reply = manager->post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [=](){
    if(reply->error() == QNetworkReply::NoError)
    {
        QString contents = QString::fromUtf8(reply->readAll());
    }
    else{
        QMessageBox::information(this, tr("File Name"),"User Name or password incorrect");
        QString err = reply->errorString();
        qDebug() << err;
    }
    reply->deleteLater();
    });

    QVector<QPushButton*> buttons2DVector(8);
    buttons2DVector.resize(8);
    QPushButton *b = new QPushButton(Name);
    ui->listView->layout()->addWidget(b);
    buttons2DVector[NumOfCourses] = b;
    QObject::connect(b, &QPushButton::clicked, [=]()
    {
        ui->stackedWidget->setCurrentIndex(5);
    });
}

void MainWindow::AddCoursesToLec(QStringList Courses)
{
    QGridLayout* layout = new QGridLayout();
    ui->listView->setLayout(layout);

    QVector<QPushButton*> buttons2DVector(8);
    buttons2DVector.resize(8);

    for (int i = 0; i < Courses.size(); i++)
    {
        QPushButton *b = new QPushButton(Courses[i]);
        layout->addWidget(b);
        buttons2DVector[i] = b;
        QObject::connect(b, &QPushButton::clicked, [=]()
        {
            ui->stackedWidget->setCurrentIndex(5);
        });
    }
}

void MainWindow::on_pushButton_28_clicked()
{
    manager = new QNetworkAccessManager(this);
    QUrl url(QStringLiteral("https://localhost:44363/api/Questions/Download"));
    QUrlQuery query;

    query.addQueryItem("userId", "2");
    query.addQueryItem("exerciseId", "3");
    url.setQuery(query.query());
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->get(QNetworkRequest(url));


    connect(reply, &QNetworkReply::finished, this, [this, reply]()
    {
      replyFinished(reply);
    });

    qDebug() << reply->readAll();

}


void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_pushButton_27_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);
}


void MainWindow::on_pushButton_5_clicked()
{
    //ui->stackedWidget->setCurrentIndex(6);

    QString username = ui->Stu_UN_Line_Edit->text();
    QString password = ui->Stu_Pass_Line_Edit->text();
    manager = new QNetworkAccessManager(this);
    const QUrl url(QStringLiteral("https://localhost:44363/api/Course/AddCourse"));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject obj;
    obj["UserName"] = username;
    obj["Password"] = password;
    QJsonDocument doc(obj);
    QByteArray data = doc.toJson();
    QNetworkReply *reply;
    reply = manager->post(request, data);
    QObject::connect(reply, &QNetworkReply::finished, [=]()
    {
        if(reply->error() == QNetworkReply::NoError)
        {
            QString contents = QString::fromUtf8(reply->readAll());
            qDebug() << contents;
            ui->stackedWidget->setCurrentIndex(6);

            QByteArray Stu_Cour = GetCourses(contents);
            qDebug() << "Lec_Cour: " << Stu_Cour;
            //AddCoursesToLec(Lec_Cour);
        }
        else
        {
            QMessageBox::information(this, tr("File Name"),"User Name or password incorrect");
            QString err = reply->errorString();
            qDebug() << err;
        }
        reply->deleteLater();
    });

}

void MainWindow::onButtonClicked()
{
    // Perform the desired action
    m_buttonClicked = true;
}

void MainWindow::onTextChanged(const QString &text)
{
    QString enteredText = text;
    // Do something with enteredText
}

void MainWindow::on_pushButton_clicked()
{
    QPushButton* bt = new QPushButton("OK");

    QObject::connect(bt, &QPushButton::clicked, [=]()
    {
        // Show the input dialog and get the user's input
        bool ok;
        QString text = QInputDialog::getText(nullptr, "Input Dialog", "Enter the course name:", QLineEdit::Normal, "", &ok);

        // If the user clicked "OK", store the input value in a variable
        if (ok && !text.isEmpty())
        {
            QString userInput = text;
            qDebug() << "User entered: " << userInput << "\nLecturer Id: " << lec_id;
            PostCourse(userInput, lec_id);
        }
    });
    bt->show();

}

void MainWindow::on_pushButton_33_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_pushButton_31_clicked()
{
    Test();
}

void MainWindow::Test()
{
    QEventLoop eventLoop;
    QVideoWidget videoWidget;
    videoWidget.resize(640, 480);
    videoWidget.show();
    QMediaCaptureSession captureSession;
    QAudioInput audioInput;
    captureSession.setAudioInput(&audioInput);
    QCamera* camera = new QCamera;
    captureSession.setCamera(camera);
    QMediaRecorder* recorder = new QMediaRecorder(camera);
    captureSession.setRecorder(recorder);
    captureSession.setCamera(camera);
    captureSession.setVideoOutput(&videoWidget);
    camera->start();

    // setup output format for the recorder
    QMediaFormat format(QMediaFormat::MPEG4);
    format.setVideoCodec(QMediaFormat::VideoCodec::H264);
    format.setAudioCodec(QMediaFormat::AudioCodec::MP3);
    recorder->setMediaFormat(format);
    recorder->setOutputLocation(QUrl::fromLocalFile("D:/הקלטות/test.avi"));
    //on shutter button pressed
    recorder->record();

    // sometime later, or on another press

    QTimer::singleShot(60000, &eventLoop, &QEventLoop::quit); // Quit the event loop after 10 seconds
    eventLoop.exec(); // Start the event loop
    recorder->stop();
}

void MainWindow::on_pushButton_35_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

