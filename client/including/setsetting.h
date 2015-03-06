#ifndef SETSETTING_H
#define SETSETTING_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SetSetting : public QDialog
{
    Q_OBJECT

private:

    QLabel *loginLabel;
    QLabel *passwordLabel;
    QLabel *hostLabel;
    QLabel *portLabel;

    QPushButton *okButton;
    QPushButton *cancelButton;

    QHBoxLayout *layoutHtop;
    QHBoxLayout *layoutHbottom;
    QVBoxLayout *layoutVleft;
    QVBoxLayout *layoutVright;
    QVBoxLayout *layoutVcentral;

    void CreateLayout();

public:
    SetSetting(QString login = "", QString password = "", QString host = "", quint32 port = 0, QWidget *parent = 0);

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QLineEdit *hostEdit;
    QLineEdit *portEdit;
};

#endif // SETSETTING_H
























