#include "smileitem.h"

SmileItem::SmileItem(QWidget *parent) : QLabel(parent)
{
    setMouseTracking(true);
}

void SmileItem::enterEvent(QEvent */*event*/)
{
    update();
}

void SmileItem::leaveEvent(QEvent */*event*/)
{
    update();
}
