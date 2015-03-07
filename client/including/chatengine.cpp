#include "chatengine.h"
#include <QDebug>

ChatEngine::ChatEngine(QWidget *parent, QString hst, quint16 prt, QString logn, QString pass) : QWidget(parent)
{
    sock = new QTcpSocket(this);

    host = hst;
    port = prt;

    login = logn;
    password = pass;

    userList[COMMONMSG] = -1;

    QObject::connect(sock, SIGNAL(readyRead()), this, SLOT(ReadData()));
    QObject::connect(sock, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ErrorConnected(QAbstractSocket::SocketError)));
    QObject::connect(sock, SIGNAL(connected()), this, SLOT(AvailableConnected()));
}

void ChatEngine::ParserData(QString baf)
{
    if (baf.indexOf(DATASTART) != -1)
        GetNewMsg(baf);
    else if (baf == ADDNEWUSER )
        return;
    else if (baf.indexOf(ADDNEWUSER) != -1)
        GetNewUserList(baf);
    else if (baf.indexOf(REMOVEUSER) != -1)
        GetRemoveUserList(baf);
}

void ChatEngine::GetNewUserList(QString baf)
{
    listNewUsers.clear();

    QString usersStr = baf.mid(9);
    QStringList usersList = usersStr.split(',', QString::SkipEmptyParts);

    for (int i=0; i<usersList.size(); i++)
    {
        QStringList userData = usersList.at(i).split('.');
        userList[userData.at(0) + '<' + userData.at(1) + '>'] = userData.at(1).toInt();

        User user;
        user.showName = userData.at(0);
        user.name = userData.at(0) + '<' + userData.at(1) + '>';
        listNewUsers.append(user);
    }

    emit NewUser();
}

void ChatEngine::GetRemoveUserList(QString baf)
{
    RemoveUsrName = baf.mid(10);
    userList.remove(RemoveUsrName);
    emit RemoveUser();
}

void ChatEngine::GetNewMsg(QString baf)
{
    int startPos = baf.indexOf(NAMESNDSTART) + 9;
    int endPos = baf.indexOf(NAMESNDEND);
    message.senderName = baf.mid(startPos, endPos - startPos);

    startPos = baf.indexOf(PRIVATEMSGSTART) + 9;
    endPos = baf.indexOf(PRIVATEMSGEND);

    if (baf.mid(startPos, endPos - startPos).toInt() == -1)
        message.privateMsg = false;
    else
        message.privateMsg = true;

    startPos = baf.indexOf(DATASTART) + 6;
    endPos = baf.indexOf(DATAEND);
    message.msg.clear();
    message.msg.append(baf.mid(startPos, endPos - startPos));

    emit ReadyData();
}

void ChatEngine::SetHost(QString hst, quint32 prt)
{
    host = hst;
    port = prt;
}

void ChatEngine::SetAuth(QString logn, QString pass)
{
    login = logn;
    password = pass;
}

Message ChatEngine::GetData()
{
    return message;
}

QList<User> ChatEngine::GetNewUser()
{
    return listNewUsers;
}

QString ChatEngine::GetRemoveUser()
{
    return RemoveUsrName;
}

void ChatEngine::WriteData(QString data, QString name)
{
    if (userList.find(name) != userList.end())
    {
        QString str;
        str.append(QString(MSGSTART)
                   + NAMERCVSTART +  QString::number(userList[name]) + NAMERCVEND
                   + NAMESNDSTART + login + NAMESNDEND
                   + EVENTSTART + "add" + EVENTEND
                   + DATASTART + data + DATAEND
                   + IDNODESTART + QString::number(5) + IDNODEEND
                   + MSGEND);

        sock->write(str.toStdString().c_str());
    }
}

void ChatEngine::ReadData()
{
    char baf[1000];
    quint64 len= sock->read(baf, 1000);
    baf[len] = '\0';
    QString baff;
    baff.append(baf);
    ParserData(baff);
}

void ChatEngine::ErrorConnected(QAbstractSocket::SocketError num)
{
    qDebug() << num;
    emit Connected(false);
}

void ChatEngine::AvailableConnected()
{
    QString str;
    str.append(LOGINSTART + login + LOGINEND
               + PASSSTART + password + PASSEND);

    sock->write(str.toStdString().c_str());

    emit Connected(true);
}

void ChatEngine::Connect()
{
    sock->abort();
    sock->connectToHost(host, port);
}

void ChatEngine::Disconnect()
{
    sock->disconnectFromHost();
}







































