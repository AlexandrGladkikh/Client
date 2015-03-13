#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    privateName(COMMONMSG),
    connection(false),
    connected(false),
    connectData(false)
{
    ui->setupUi(this);

    chatEngine = new ChatEngine(this);
    usedColors = new UsedColor;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

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

void MainWindow::SetUserColors(QString name)
{
    int r = qrand()%COLORRANGE;
    int g = qrand()%COLORRANGE;
    int b = qrand()%COLORRANGE;

    while (!usedColors->CheckColor(r, g, b))
    {
        r = qrand()%COLORRANGE;
        g = qrand()%COLORRANGE;
        b = qrand()%COLORRANGE;
    }

    colorsUsers[name] = QColor(r, g, b);
}

void MainWindow::SendMsg()
{
    if (connected)
    {
        QString msg = ui->msgEdit->GetMsg();

        QTextCursor cursor = ui->browserMsg->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->browserMsg->setTextCursor(cursor);
        time.start();
        ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                                   + QString("( ")
                                   + time.toString(Qt::TextDate)
                                   + QString(" ) ")
                                   + selfName
                                   + ": "
                                   + "</p>");
        ui->browserMsg->insertHtml(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                                   + msg
                                   + "</p>");

        cursor.movePosition(QTextCursor::End);
        ui->browserMsg->setTextCursor(cursor);

        chatEngine->WriteData(msg, privateName);

        privateName = COMMONMSG;
        ui->labelPrivate->setVisible(false);
    }
}

void MainWindow::RcvMsg()
{
    Message msg = chatEngine->GetData();

    QTextCursor cursor = ui->browserMsg->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->browserMsg->setTextCursor(cursor);

    QString textPrivateMsg;
    if (msg.privateMsg)
        textPrivateMsg = "Приватное сообщение от ";
    else
        textPrivateMsg = "";

    time.start();
    ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                           + "<font color=\""
                           + colorsUsers[msg.senderName].name()
                           + "\">"
                           + QString("( ")
                           + time.toString(Qt::TextDate)
                           + QString(" ) ")
                           + textPrivateMsg
                           + msg.senderName
                           + ": "
                           + "</font>"
                           + "</p>");
    ui->browserMsg->insertHtml("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">"
                           + msg.msg
                           + "</p>");

    cursor.movePosition(QTextCursor::End);
    ui->browserMsg->setTextCursor(cursor);
}
void MainWindow::AddUsr()
{
    QList<User> usrNameList =  chatEngine->GetNewUser();

    for (int i=0; i<usrNameList.size(); i++)
    {
        SetUserColors(usrNameList.at(i).name);
        ui->userList->AddUser(usrNameList.at(i), colorsUsers[usrNameList.at(i).name]);
    }

}

void MainWindow::RemoveUsr()
{    
    QString name = chatEngine->GetRemoveUser();

    usedColors->RemoveColor(colorsUsers[name]);
    colorsUsers.remove(name);

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
                               + COLORWARNING
                               + "\">"
                               + "Подключение к серверу"
                               + "</font>"
                               + "</p>");

        ui->connectDisconnectButton->setText(tr("Ожидание..."));

        connection = true;
        chatEngine->Connect();
    }
    else
        ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                           + "<font color=\""
                           + COLORWARNING
                           + "\">"
                           + "Данные для подключения не указаны"
                           + "</font>"
                           + "</p>");
}

void MainWindow::Disconnect()
{
    if (connected || connection)
        chatEngine->Disconnect();
    ui->connectDisconnectButton->setText(tr("Соединение"));
    ui->userList->RemoveAllUser();
    ui->msgEdit->clear();

    colorsUsers.clear();
    usedColors->Reset();

    QString text;
    if (connected)
        text = "Отключение от сервера";
    else
        text = "Ошибка подключения";

    ui->browserMsg->append(QString("<style>.msg { white-space: pre-wrap; } </style> <p class=\"msg\">")
                       + "<font color=\""
                       + COLORWARNING
                       + "\">"
                       + text
                       + "</font>"
                       + "</p>");

    connected = false;
    connection = false;
    privateName = COMMONMSG;
}

void MainWindow::SetLink()
{
    if (connected || connection)
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
    {
        User selfUser;
        selfUser.name = selfName;
        selfUser.showName = "Вы:" + selfName;
        ui->userList->AddUser(selfUser, QColor(0, 0, 0), true);
        ui->connectDisconnectButton->setText(tr("Отключение"));

        connection = false;
    }
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
        /*login = setting.loginEdit->text();
        password = setting.passwordEdit->text();
        chatEngine->SetAuth(login, password);

        host = setting.hostEdit->text();
        port = setting.portEdit->text().toInt();
        chatEngine->SetHost(host, port);*/

        connectData = true;

        WriteSettings();

        ReadSettings();
    }
}

void MainWindow::closeEvent(QCloseEvent */*event*/)
{
    WriteSettings();
}

UsedColor::UsedColor()
{
    for (int i=1; i<size; i++)
    {
        red[i] = false;
        green[i] = false;
        blue[i] = false;
    }

    red[0] = true;
    green[0] = true;
    blue[0] = true;
}

bool UsedColor::CheckColor(int r, int g, int b)
{
    if (red[r] == false && green[g] == false && blue[b] == false)
    {
        red[r] = true;
        green[g] = true;
        blue[b] = true;

        return true;
    }
    else
        return false;
}

void UsedColor::Reset()
{
    for (int i=1; i<size; i++)
    {
        red[i] = false;
        green[i] = false;
        blue[i] = false;
    }

    red[0] = true;
    green[0] = true;
    blue[0] = true;
}

void UsedColor::RemoveColor(QColor color)
{
    red[color.red()] = false;
    green[color.green()] = false;
    blue[color.blue()] = false;
}


















