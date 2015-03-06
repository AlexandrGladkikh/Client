#ifndef SMILEITEM_H
#define SMILEITEM_H

#include <QLabel>
#include <QPalette>
#include "userdata.h"

class SmileItem : public QLabel
{
    Q_OBJECT

public:
    SmileItem(QWidget *parent = 0);

protected:
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);
};

#endif // SMILEITEM_H
