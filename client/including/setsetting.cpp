#include "setsetting.h"

SetSetting::SetSetting(QString login, QString password, QString host, quint32 port, QWidget *parent) : QDialog(parent)
{
    setFixedSize(300, 150);
    setWindowTitle("Настройки");

    loginLabel = new QLabel("Логин", this);
    passwordLabel = new QLabel("Пароль", this);
    hostLabel = new QLabel("ip адрес", this);
    portLabel = new QLabel("порт", this);

    loginEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    hostEdit = new QLineEdit(this);
    portEdit = new QLineEdit(this);

    loginEdit->setText(login);
    passwordEdit->setText(password);
    hostEdit->setText(host);
    if (port != 0)
        portEdit->setText(QString::number(port));

    okButton = new QPushButton("ок", this);
    cancelButton = new QPushButton("выход", this);

    layoutHtop = new QHBoxLayout/*(this)*/;
    layoutHbottom = new QHBoxLayout/*(this)*/;

    layoutVleft = new QVBoxLayout/*(this)*/;
    layoutVright = new QVBoxLayout/*(this)*/;
    layoutVcentral = new QVBoxLayout/*(this)*/;

    CreateLayout();

    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
    connect(okButton, SIGNAL(clicked()), SLOT(accept()));
}

void SetSetting::CreateLayout()
{
    layoutVleft->addWidget(loginLabel);
    layoutVleft->addWidget(passwordLabel);
    layoutVleft->addWidget(hostLabel);
    layoutVleft->addWidget(portLabel);

    layoutVright->addWidget(loginEdit);
    layoutVright->addWidget(passwordEdit);
    layoutVright->addWidget(hostEdit);
    layoutVright->addWidget(portEdit);

    layoutHtop->addLayout(layoutVleft);
    layoutHtop->addLayout(layoutVright);

    layoutHbottom->addWidget(okButton);
    layoutHbottom->addWidget(cancelButton);

    layoutVcentral->addLayout(layoutHtop);
    layoutVcentral->addLayout(layoutHbottom);

    setLayout(layoutVcentral);
}
















