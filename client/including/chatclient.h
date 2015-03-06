#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <QWidget>
#include <QRect>
#include <QSettings>
#include <QString>
#include <QTime>
#include <QGridLayout>
#include <QSpacerItem>
#include "chatengine.h"
#include "smiledialog.h"

#define COLORRED    "#B22222"
#define COLORBLUE   "#6495ED"
#define COLORPINK   "#FF1493"
#define COLORBLACK  "#000000"

class ChatClient : public QWidget
{
    Q_OBJECT

private:
    ChatEngine *chatEngine;
    //Ui::chat *ui;

    QString privateName;

    QString colorMsg;

    bool connected;

    QTime time;

    QString selfName;

    QGridLayout layout;
    QSpacerItem *horiz;
    QSpacerItem *vert;

    /*QRect rectChat;
    QRect rectMsgEdit;
    QRect rectBrowserMsg;
    QRect rectConnectDisconnectButton;
    QRect rectChoiceSmile;
    QRect rectUserList;*/

public:
    ChatClient(QWidget *parent = 0);
    ~ChatClient();
    void SetSetting(QString hst, quint32 prt, QString logn, QString pass);

/*protected:
    void resizeEvent(QResizeEvent * event);*/

private slots:
    void SendMsg();
    void RcvMsg();
    void AddUsr();
    void RemoveUsr();
    void ChoiceSmile();
    void Connect();
    void Disconnect();
    void SetPrivateMsgName(QString name);
    void AvailableConnect(bool connectAvailable);

};

#endif // CHATCLIENT_H
