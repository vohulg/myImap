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

   socket.write(cmd.toLatin1());
   if (!socket.waitForReadyRead())
       return (false);

   return true;

}

bool TImap::getFoldersList()
{
   QString cmd = QString("%1 LIST / *\r\n").arg(IMAP_TAG);

   socket.write(cmd.toLatin1());
   if (!socket.waitForReadyRead())
       return (false);

   QRegExp rx("\\((.*)\\)\\s+\"(.*)\"\\s+\"(.*)\"");
   QByteArray line;
   QString endString = QString("%1 OK LIST done\r\n").arg(IMAP_TAG);

      while(1)
      {
          line = socket.readLine();

         if (line == endString)
             break;


         if (rx.indexIn(line) != -1)
             folders.append(rx.cap(3));
         line.clear();

      }

return (true);
}

bool TImap::getMessages(const QString& folder)
{

    QString cmd = QString("%1 SELECT %2\r\n").arg(IMAP_TAG).arg(folder);
     socket.write(cmd.toLatin1());
     if (!socket.waitForReadyRead())
         return (false);

     qDebug() << socket.readAll().data() << "--------------------------------------";


     //----------выводит номера сообщений-----------------------------------------//
/*
     cmd = QString("%1 SEARCH UNSEEN\r\n").arg(IMAP_TAG);
     socket.write(cmd.toLatin1());

     if (!socket.waitForReadyRead())
              return (false);

      qDebug() << socket.readAll().data();
      */

      //---------------------------------------------------//

      fetch(9);
      return true;


}

bool TImap::fetch (int messageId)
{
    QString cmd = QString("%1 FETCH %2 RFC822.HEADER\r\n").arg(IMAP_TAG).arg(messageId);
    socket.write(cmd.toLatin1());
    if (!socket.waitForReadyRead())
        return (false);

     qDebug() << "---------fetch----------\n" << socket.readAll().data();

}



