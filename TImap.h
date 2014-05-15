#ifndef TIMAP_H
#define TIMAP_H

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QRegExp>
#include <QStringList>
#include <QFile>

#define IMAP_TAG        "IMAP4rev1"

class TImap
{
public:
    TImap();
    bool connectToHost(const QString& host ,quint16 port) ;
    bool login (const QString& username, const QString& password);
    bool getFoldersList();
    bool getMessages(const QString& folder = "INBOX");
    bool fetch (int messageId);
    bool checkFolder();

private:
    QSslSocket socket;
    QStringList folders;
    QFile file;


};

#endif // TIMAP_H
