#include "mainwindow.h"
#include <QApplication>
//#include <QStringList>
//#include <QtGlobal>
//#include <QDebug>



/*#include "imapmailbox.h"
#include "imapmessage.h"
#include "imapaddress.h"
#include "imap.h"*/

#define IMAP_HOST           "imap.gmail.com"
#define IMAP_PORT           (993)
#define IMAP_USE_SSL        (true)

#define IMAP_USERNAME       "USERNAME@gmail.com"
#define IMAP_PASSWORD       "PASSWORD"
#define IMAP_LOGIN_TYPE     (Imap::LoginPlain)

#define IMAP_MAIN_ABORT(func, message)     \
    { qDebug() << func << message; return(1); }


int main(int argc, char *argv[])
{

   QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}



