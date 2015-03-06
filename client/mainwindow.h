#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QTextCursor>
#include "including/textedit.h"
#include "including/userlist.h"
#include "including/ui_mainwindow.h"
#include "including/smiledialog.h"
#include "including/chatengine.h"
#include "including/setsetting.h"

namespace Ui {
class MainWindow;
}

#define COLORRED    "#B22222"
#define COLORBLUE   "#6495ED"
#define COLORPINK   "#FF1493"
#define COLORBLACK  "#000000"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void LoadSetting();
    void SaveSetting();

private:
    Ui::MainWindow *ui;
    ChatEngine *chatEngine;

    QString privateName;
    QString colorMsg;
    QString selfName;

    QString login;
    QString password;
    QString host;
    quint32 port;

    QTime time;

    QMenu *fileMenu;
    QAction *setting;

    bool connected;
    bool connectData;

    void ReadSettings();
    void WriteSettings();
    void CreateActions();
    void CreateMenus();

private slots:
    void SendMsg();
    void RcvMsg();
    void AddUsr();
    void RemoveUsr();
    void ChoiceSmile();
    void Connect();
    void Disconnect();
    void SetLink();
    void SetPrivateMsgName(QString name);
    void AvailableConnect(bool connectAvailable);
    void ShowSetSetting();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
