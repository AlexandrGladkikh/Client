#ifndef CHATENGINE_H
#define CHATENGINE_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QList>
#include <QMap>
#include "userdata.h"

#define MSGSTART            "<message>"
#define MSGEND              "</message>"
#define NAMERCVSTART        "<nameRcv>"
#define NAMERCVEND          "</nameRcv>"
#define NAMESNDSTART        "<nameSnd>"
#define NAMESNDEND          "</nameSnd>"
#define DATASTART           "<data>"
#define DATAEND             "</data>"
#define EVENTSTART          "<event>"
#define EVENTEND            "</event>"
#define IDNODESTART         "<idNode>"
#define IDNODEEND           "</idNode>"
#define LOGINSTART          "<login>"
#define LOGINEND            "</login>"
#define PASSSTART           "<pass>"
#define PASSEND             "</pass>"
#define PRIVATEMSGSTART     "<prvtMsg>"
#define PRIVATEMSGEND       "</prvtMsg>"

#define ADDNEWUSER          "addnewusr"
#define REMOVEUSER          "removeusr"

#define COMMONMSG           "commonmsg"

struct Message
{
    bool privateMsg;
    QString msg;
    QString senderName;
};

class ChatEngine : public QWidget
{
Q_OBJECT

private:
    QTcpSocket *sock;
    QTime time;

    Message message;

    QList<User> listNewUsers;

    QMap<QString, int> userList;

    QString RemoveUsrName;

    QString host;
    quint16 port;

    QString login;
    QString password;

    int errornum;

    void ParserData(QString baf);
    void GetNewUserList(QString baf);
    void GetRemoveUserList(QString baf);
    void GetNewMsg(QString baf);

public:
    ChatEngine(QWidget *parent = 0, QString hst = "", quint16 prt = 0, QString logn = "", QString pass = "");
    void SetHost(QString hst, quint32 prt);
    void SetAuth(QString logn, QString pass);
    Message GetData();
    QList<User> GetNewUser();
    QString GetRemoveUser();
    void WriteData(QString data, QString name);

private slots:
    void ReadData();
    void ErrorConnected(QAbstractSocket::SocketError errnum);
    void AvailableConnected();

public slots:
    void Connect();
    void Disconnect();

signals:
    void ReadyData();
    void NewUser();
    void RemoveUser();
    void Connected(bool);
};

#endif // CHATENGINE_H
