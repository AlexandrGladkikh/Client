#include "chatclient.h"

ChatClient::ChatClient(QWidget *parent) : QWidget(parent), ui(new Ui::chat), privateName(COMMONMSG), colorMsg(COLORRED), connected(false)
{
    chatEngine = new ChatEngine(this);

    ui->setupUi(this);

    horiz = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Fixed);
    vert = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Fixed);

    layout.addItem(horiz, 1, 0);
    layout.addItem(vert, 0, 1);
    layout.addWidget(ui->widget, 1, 1);

    setLayout(&layout);

    /*rectChat = geometry();
    rectMsgEdit = ui->msgEdit->geometry();
    rectBrowserMsg = ui->browserMsg->geometry();
    rectConnectDisconnectButton = ui->connectDisconnectButton->geometry();
    rectChoiceSmile = ui->choiceSmile->geometry();
    rectUserList = ui->userList->geometry();*/

    connect(ui->msgEdit, SIGNAL(ReadyData()), this, SLOT(SendMsg()));
    connect(ui->connectDisconnectButton, SIGNAL(clicked()), this, SLOT(Connect()));
    connect(ui->choiceSmile, SIGNAL(clicked()), this, SLOT(ChoiceSmile()));
    connect(ui->userList, SIGNAL(SelectedName(QString)), this, SLOT(SetPrivateMsgName(QString)));

    connect(chatEngine, SIGNAL(ReadyData()), this, SLOT(RcvMsg()));
    connect(chatEngine, SIGNAL(NewUser()), this, SLOT(AddUsr()));
    connect(chatEngine ,SIGNAL(RemoveUser()), this, SLOT(RemoveUsr()));
    connect(chatEngine, SIGNAL(Connected(bool)), this, SLOT(AvailableConnect(bool)));
}

ChatClient::~ChatClient()
{
    delete ui;
}

void ChatClient::SetSetting(QString hst, quint32 prt, QString logn, QString pass)
{
    chatEngine->SetHost(hst, prt);
    chatEngine->SetAuth(logn, pass);

    selfName = logn;
}

/*void ChatClient::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();

    int diffHeight = size.height() - rectChat.height();
    int diffWidth = size.width() - rectChat.width();

    ui->msgEdit->setGeometry(QRect(rectMsgEdit.left(), rectMsgEdit.top() + diffHeight, rectMsgEdit.width() + diffWidth, rectMsgEdit.height()));

    ui->browserMsg->setGeometry(QRect(rectBrowserMsg.left(), rectBrowserMsg.top(), rectBrowserMsg.width() + diffWidth, rectBrowserMsg.height() + diffHeight));

    ui->connectDisconnectButton->setGeometry(QRect(rectConnectDisconnectButton.left() + diffWidth, rectConnectDisconnectButton.top() + diffHeight, rectConnectDisconnectButton.width(), rectConnectDisconnectButton.height()));

    ui->choiceSmile->setGeometry(QRect(rectChoiceSmile.left(), rectChoiceSmile.top() + diffHeight, rectChoiceSmile.width(), rectChoiceSmile.height()));

    ui->userList->setGeometry(QRect(rectUserList.left() + diffWidth, rectUserList.top(), rectUserList.width(), rectUserList.height() + diffHeight));
}*/

void ChatClient::SendMsg()
{
    if (connected)
    {
        QString msg = ui->msgEdit->GetMsg();
        if (colorMsg == COLORRED)
            colorMsg = COLORBLUE;
        else
            colorMsg = COLORRED;

        time.start();
        ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                                   + "<font color=\""
                                   + colorMsg
                                   + "\">"
                                   + QString("( ")
                                   + time.toString(Qt::TextDate)
                                   + QString(" ) ")
                                   + selfName
                                   + ": ");
        ui->browserMsg->insertHtml(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                                   + msg
                                   + "</p>");

        chatEngine->WriteData(msg, privateName);

        privateName = COMMONMSG;
        ui->msgEdit->setTextColor(Qt::black);
    }
}

void ChatClient::RcvMsg()
{
    Message msg = chatEngine->GetData();
    if (colorMsg == COLORRED)
        colorMsg = COLORBLUE;
    else
        colorMsg = COLORRED;

    time.start();
    ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                           + "<font color=\""
                           + colorMsg
                           + "\">"
                           + QString("( ")
                           + time.toString(Qt::TextDate)
                           + QString(" ) ")
                           + msg.senderName
                           + ": ");

    ui->browserMsg->insertHtml("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">"
                               + msg.msg
                               + "</p>");
}
void ChatClient::AddUsr()
{
    QStringList usrNameLisr =  chatEngine->GetNewUser();

    for (int i=0; i< usrNameLisr.size(); i++)
    ui->userList->AddUser(usrNameLisr.at(i));
}

void ChatClient::RemoveUsr()
{
    QString name = chatEngine->GetRemoveUser();
    ui->userList->RemoveUser(name);
    if (privateName == name)
    {
        ui->msgEdit->clear();
        ui->msgEdit->setTextColor(Qt::black);
        privateName = COMMONMSG;
    }
}

void ChatClient::ChoiceSmile()
{
    SmileDialog choiceSmile;

    if (choiceSmile.exec())
    {
        QString name = choiceSmile.GetNameSmile();
        ui->msgEdit->AddSmile(name);
    }
}

void ChatClient::Connect()
{
    chatEngine->Connect();

    ui->connectDisconnectButton->setText(tr("Отключение"));

    disconnect(ui->connectDisconnectButton, SIGNAL(clicked()), this, SLOT(Connect()));
    connect(ui->connectDisconnectButton, SIGNAL(clicked()), this, SLOT(Disconnect()));
}

void ChatClient::Disconnect()
{
    chatEngine->Disconnect();
    connected = false;
    ui->connectDisconnectButton->setText(tr("Соединение"));

    ui->userList->RemoveAllUser();

    ui->msgEdit->clear();
    ui->msgEdit->setTextColor(Qt::black);
    privateName = COMMONMSG;

    disconnect(ui->connectDisconnectButton, SIGNAL(clicked()), this, SLOT(Disconnect()));
    connect(ui->connectDisconnectButton, SIGNAL(clicked()), this, SLOT(Connect()));
}

void ChatClient::SetPrivateMsgName(QString name)
{
    if (privateName == name)
    {
        ui->msgEdit->clear();
        ui->msgEdit->setTextColor(Qt::black);
        privateName = COMMONMSG;
    }
    else
    {
        ui->msgEdit->clear();
        ui->msgEdit->setTextColor(COLORPINK);

        privateName = name;
    }
}

void ChatClient::AvailableConnect(bool connectAvailable)
{
    connected = connectAvailable;
}




























