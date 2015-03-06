#include "userlist.h"

UserList::UserList(QWidget *parent) : QListWidget(parent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
}

void UserList::RemoveUser(QString name)
{
    delete userList[name];
    userList.remove(name);
}

void UserList::RemoveAllUser()
{
    QMapIterator<QString, QListWidgetItem*> it(userList);

    while(it.hasNext())
    {
        it.next();
        delete userList[it.key()];
    }
}

void UserList::AddUser(User name)
{
    UserItem *item;
    item = new UserItem(this);
    item->AddName(name);

    addItem(item);
    userList[name.name] = item;
}

void UserList::mouseDoubleClickEvent(QMouseEvent */*event*/)
{
    if (currentItem() != NULL)
        emit SelectedName(((UserItem*)currentItem())->GetName());
}
