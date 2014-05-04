#ifndef TIMAP_H
#define TIMAP_H

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QRegExp>
#include <QStringList>

#define IMAP_TAG        "IMAP4rev1"

class TImap
{
public:
    TImap();
    bool connectToHost(const QString& host ,quint16 port) ;
    bool login (const QString& username, const QString& password);

private:
    QSslSocket socket;
};

#endif // TIMAP_H