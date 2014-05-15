#include "TImap.h"

TImap::TImap()
{
    file.setFileName("imap-letter.EML");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        qDebug() << "File not created";
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

     cmd = QString("%1 SEARCH ALL\r\n").arg(IMAP_TAG);
     socket.write(cmd.toLatin1());

     if (!socket.waitForReadyRead())
              return (false);

      qDebug() << socket.readAll().data();

     //---------------------------------------------------//

      fetch(1);
      return true;
}

bool TImap::fetch (int messageId)
{
    // RFC822.HEADER - получение всех заголовков
    //QString cmd = QString("%1 FETCH %2 BODY[TEXT]\r\n").arg(IMAP_TAG).arg(messageId);
    //QString cmd = QString("%1 FETCH %2 RFC822.HEADER\r\n").arg(IMAP_TAG).arg(messageId);
    QString cmd = QString("%1 FETCH %2 bodystructure\r\n").arg(IMAP_TAG).arg(messageId);



    socket.write(cmd.toLatin1());
    if (!socket.waitForReadyRead())
        return (false);

    //qDebug() << socket.readAll() << "====================";


    QByteArray line = socket.readLine().trimmed();
    while (socket.canReadLine())
    {
        /*
        if (line.startsWith("*") || line.startsWith(")") || line.startsWith("\n") )
        {
            line = socket.readLine().trimmed();
            continue;
        }
        */
        file.write(line);
        line = socket.readLine().trimmed();
        file.write("\n");
    }


    //---------- запись основного тела письма---------------------------------//

    cmd = QString("%1 FETCH %2 BODY[2.2]\r\n").arg(IMAP_TAG).arg(messageId);

    socket.write(cmd.toLatin1());
    if (!socket.waitForReadyRead())
        return (false);

    line = socket.readLine().trimmed();
    while (socket.canReadLine())
    {
        if (    line.startsWith("*")
                || line.startsWith(")")
                || line == ("")
                || line.startsWith("This is a multi-part message"))
        {
            line = socket.readLine().trimmed();
            continue;
        }
        file.write(line);
        line = socket.readLine().trimmed();
        file.write("\n");
    }

    //--------------------------------------------


   file.close();




    // qDebug() << "---------fetch----------\n" << socket.readAll().data();



}



