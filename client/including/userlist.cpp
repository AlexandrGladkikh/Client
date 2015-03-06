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
    QMapIterator<QString, UserItem*> it(userList);

    delete selfItem;
    while(it.hasNext())
    {
        it.next();
        delete userList[it.key()];
    }
}

void UserList::AddUser(User name, QColor color, bool selfName)
{
    UserItem *item;
    item = new UserItem(this);
    item->setTextColor(color);
    item->AddName(name);

    addItem(item);
    if (selfName)
        selfItem = item;
    else
        userList[name.name] = item;
}

void UserList::mouseDoubleClickEvent(QMouseEvent */*event*/)
{
    if (currentItem() != NULL && ((UserItem*)currentItem()) != selfItem)
        emit SelectedName(((UserItem*)currentItem())->GetName());
}
