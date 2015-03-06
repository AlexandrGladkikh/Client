#ifndef USERITEM_H
#define USERITEM_H

#include <QListWidgetItem>
#include <QString>
#include "userdata.h"

class UserItem : public QListWidgetItem
{
    //Q_OBJECT

private:
    User userName;

public:
    UserItem(QListWidget *parent = 0);
    void AddName(User name);
    QString GetName() const;
};

#endif // USERITEM_H
