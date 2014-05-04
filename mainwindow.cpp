#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("KL");

    TImap imap;

    if(!imap.connectToHost("imap.mail.ru", 993))
        qDebug() << "Not connected";

    QString username = "testov-79@mail.ru";
     QString pass = "testtest";

    if(!imap.login(username,  pass))
        qDebug() << "Not loged";

    if(!imap.getFoldersList())
        qDebug() << "Not get folders list";


    if(!imap.getMessages())
        qDebug() << "Not get messages";






}

MainWindow::~MainWindow()
{
    delete ui;
}
