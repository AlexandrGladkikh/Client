#include "useritem.h"

UserItem::UserItem(QListWidget *parent) : QListWidgetItem(parent)
{

}

void UserItem::AddName(User name)
{
    userName = name;

    setText(userName.showName);
}

QString UserItem::GetName()const
{
    return userName.name;
}
