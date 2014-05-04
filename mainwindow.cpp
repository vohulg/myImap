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


    qDebug() << socket.readAll().data();

    socket.write("IMAP4rev1 LIST imap.mail.ru %\r\n");
    socket.waitForReadyRead();

    // qDebug() << socket.readAll().data();

    /*
    QRegExp rx("\\((.*)\\)\\s+\"(.*)\"\\s+\"(.*)\"");
    while (!d->isResponseEnd(response = d->readLine())) {
        if (rx.indexIn(response) != -1)
            folders.append(rx.cap(3));
    }

    return(folders);
     */

QStringList folders;
QRegExp rx("\\((.*)\\)\\s+\"(.*)\"\\s+\"(.*)\"");
QByteArray line;
   while(1)
   {
       line = socket.readLine();

      if (line == "IMAP4rev1 OK LIST done\r\n")
          break;


      if (rx.indexIn(line) != -1)
          folders.append(rx.cap(3));
      line.clear();

   }


    QByteArray response = socket.readAll().data();
    qDebug() << socket.readAll().data();



    socket.write("IMAP4rev1 SELECT MyFoldr\r\n");
    socket.waitForReadyRead();
      qDebug() << socket.readAll().data();

    /*

    while (socket.waitForReadyRead())
    {
        qDebug() << socket.readAll().data();
        socket.write("IMAP4rev1 LIST '' '*'\r\n");


        while (socket.waitForReadyRead())
            qDebug() << socket.readAll().data();

    }
    */


                 //IMAP4rev1 LOGIN testov-79@mail.ru testtest


    //socket->write(QString("%1\r\n").arg(data).toLatin1());
    //THIMAP41 LOGIN testov-79@mail.ru testtest

}

MainWindow::~MainWindow()
{
    delete ui;
}
