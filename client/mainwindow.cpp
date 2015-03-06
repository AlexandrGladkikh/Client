#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    privateName(COMMONMSG),
    colorMsg(COLORRED),
    connected(false),
    connectData(false)
{
    ui->setupUi(this);

    chatEngine = new ChatEngine(this);

    CreateActions();
    CreateMenus();

    setWindowTitle("Клиент");

    ReadSettings();

    connect(ui->msgEdit, SIGNAL(ReadyData()), this, SLOT(SendMsg()));
    connect(ui->connectDisconnectButton, SIGNAL(clicked()), this, SLOT(SetLink()));
    connect(ui->choiceSmile, SIGNAL(clicked()), this, SLOT(ChoiceSmile()));
    connect(ui->userList, SIGNAL(SelectedName(QString)), this, SLOT(SetPrivateMsgName(QString)));

    connect(chatEngine, SIGNAL(ReadyData()), this, SLOT(RcvMsg()));
    connect(chatEngine, SIGNAL(NewUser()), this, SLOT(AddUsr()));
    connect(chatEngine ,SIGNAL(RemoveUser()), this, SLOT(RemoveUsr()));
    connect(chatEngine, SIGNAL(Connected(bool)), this, SLOT(AvailableConnect(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadSettings()
{
    QSettings settings("Pet Project", "Client");

    restoreGeometry(settings.value("geometry").toByteArray());

    login = settings.value("login", "noname").toString();

    password = settings.value("password", "noname").toString();

    host = settings.value("host", "").toString();
    port = settings.value("port", 0).toInt();

    chatEngine->SetHost(host, port);
    chatEngine->SetAuth(login, password);

    selfName = login;

    if (host != "")
        connectData = true;
}

void MainWindow::WriteSettings()
{
    QSettings settings("Pet Project", "Client");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("login", login);
    settings.setValue("password", password);
    settings.setValue("host", host);
    settings.setValue("port", port);
}

void MainWindow::CreateActions()
{
    setting = new QAction(tr("Настройки"), this);

    connect(setting, SIGNAL(triggered()), this, SLOT(ShowSetSetting()));
}

void MainWindow::CreateMenus()
{
    fileMenu = menuBar()->addMenu(tr("Файл"));
    fileMenu->addAction(setting);
}

void MainWindow::SendMsg()
{
    if (connected)
    {
        QString msg = ui->msgEdit->GetMsg();
        if (colorMsg == COLORRED)
            colorMsg = COLORBLUE;
        else
            colorMsg = COLORRED;

        time.start();
        QTextCursor cursor = ui->browserMsg->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->browserMsg->setTextCursor(cursor);
        ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                                   + "<font color=\""
                                   + colorMsg
                                   + "\">"
                                   + QString("( ")
                                   + time.toString(Qt::TextDate)
                                   + QString(" ) ")
                                   + selfName
                                   + ": "
                                   + "</p>");
        ui->browserMsg->insertHtml(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                                   + msg
                                   + "</p>");

        chatEngine->WriteData(msg, privateName);

        privateName = COMMONMSG;
        ui->labelPrivate->setVisible(false);
    }
}

void MainWindow::RcvMsg()
{
    Message msg = chatEngine->GetData();
    if (colorMsg == COLORRED)
        colorMsg = COLORBLUE;
    else
        colorMsg = COLORRED;

    time.start();

    QTextCursor cursor = ui->browserMsg->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->browserMsg->setTextCursor(cursor);
    if (msg.privateMsg)
        ui->browserMsg->append("Приватное сообщение");
    else
        ui->browserMsg->append("");
    ui->browserMsg->insertHtml(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                           + "<font color=\""
                           + colorMsg
                           + "\">"
                           + QString("( ")
                           + time.toString(Qt::TextDate)
                           + QString(" ) ")
                           + msg.senderName
                           + ": "
                           + "</p>");
    ui->browserMsg->insertHtml("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">"
                           + msg.msg
                           + "</p>");
}
void MainWindow::AddUsr()
{
    QList<User> usrNameList =  chatEngine->GetNewUser();

    for (int i=0; i< usrNameList.size(); i++)
        ui->userList->AddUser(usrNameList.at(i));
}

void MainWindow::RemoveUsr()
{
    QString name = chatEngine->GetRemoveUser();
    ui->userList->RemoveUser(name);
    if (privateName == name)
    {
        ui->msgEdit->clear();
        ui->msgEdit->setTextColor(Qt::black);
        ui->labelPrivate->setVisible(false);
        privateName = COMMONMSG;
    }
}

void MainWindow::ChoiceSmile()
{
    SmileDialog choiceSmile;

    QRect rect = this->geometry();
    rect.setLeft(rect.left() + rect.width()/2);
    rect.setTop(rect.top() + rect.height()/2);

    choiceSmile.setGeometry(rect);

    if (choiceSmile.exec())
    {
        QString name = choiceSmile.GetNameSmile();
        ui->msgEdit->AddSmile(name);
    }
}

void MainWindow::Connect()
{
    if (connectData)
    {
        ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                               + "<font color=\""
                               + COLORRED
                               + "\">"
                               + "Подключение к серверу"
                               + "</p>");

        ui->connectDisconnectButton->setText(tr("Ожидание..."));

        chatEngine->Connect();
    }
    else
        ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                           + "<font color=\""
                           + COLORRED
                           + "\">"
                           + "Данные для подключения не указаны"
                           + "</p>");
}

void MainWindow::Disconnect()
{
    if (connected)
        chatEngine->Disconnect();
    ui->connectDisconnectButton->setText(tr("Соединение"));

    ui->userList->RemoveAllUser();

    ui->msgEdit->clear();

    QString text;
    if (connected)
        text = "Отключение от сервера";
    else
        text = "Ошибка подключения";

    ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                       + "<font color=\""
                       + COLORRED
                       + "\">"
                       + text
                       + "</p>");

    connected = false;
    privateName = COMMONMSG;
}

void MainWindow::SetLink()
{
    if (connected)
        Disconnect();
    else
        Connect();
}

void MainWindow::SetPrivateMsgName(QString name)
{
    if (privateName == name)
    {
        ui->msgEdit->clear();
        ui->labelPrivate->setVisible(false);

        privateName = COMMONMSG;
    }
    else
    {
        ui->msgEdit->clear();
        ui->labelPrivate->setText("приватное для " + name.mid(0, name.indexOf("<")));
        ui->labelPrivate->setVisible(true);

        privateName = name;
    }
}

void MainWindow::AvailableConnect(bool connectAvailable)
{
    connected = connectAvailable;

    if (connected == false)
    {
        Disconnect();
    }
    else
        ui->connectDisconnectButton->setText(tr("Отключение"));
}

void MainWindow::ShowSetSetting()
{
    SetSetting setting(login, password, host, port);
    QRect rect = this->geometry();
    rect.setLeft(rect.left() + rect.width()/2);
    rect.setTop(rect.top() + rect.height()/2);

    setting.setGeometry(rect);

    if (setting.exec())
    {
        login = setting.loginEdit->text();
        password = setting.passwordEdit->text();
        chatEngine->SetAuth(login, password);

        host = setting.hostEdit->text();
        port = setting.portEdit->text().toInt();
        chatEngine->SetHost(host, port);

        connectData = true;

        WriteSettings();
    }
}

void MainWindow::closeEvent(QCloseEvent */*event*/)
{
    WriteSettings();
}




















