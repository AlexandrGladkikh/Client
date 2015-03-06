#ifndef USERLIST_H
#define USERLIST_H

#include <QListWidget>
#include <QMap>
#include <QMapIterator>
#include <QString>
#include <QColor>
#include "userdata.h"
#include "useritem.h"

class UserList : public QListWidget
{
    Q_OBJECT

private:
    QMap<QString, UserItem*> userList;
    UserItem *selfItem;


public:
    UserList(QWidget *parent);
    void RemoveUser(QString name);
    void RemoveAllUser();
    void AddUser(User name, QColor color, bool selfName = false);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void SelectedName(QString name);
};

#endif // USERLIST_H
