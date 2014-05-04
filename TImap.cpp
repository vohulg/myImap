#include "TImap.h"

TImap::TImap()
{
}

bool TImap::connectToHost( const QString& host, quint16 port)
{

    socket.connectToHostEncrypted(host, port);
    if (!socket.waitForEncrypted())
        return (false);

    QByteArray response =  socket.readLine();
    if (!response.startsWith("* OK"))
        return (false);

    return (true);

}

bool TImap::login (const QString& username, const QString& password)
{
   QString cmd = QString("%1 LOGIN %2 %3\r\n").arg(IMAP_TAG).arg(username).arg(password);
  cmd = "IMAP4rev1 LOGIN testov-79@mail.ru testtest\r\n";

   socket.write(cmd.toLatin1());
   if (!socket.waitForEncrypted())
       return (false);

   return true;




}
