#ifndef SMILEDIALOG_H
#define SMILEDIALOG_H

#include <QDialog>
#include <QString>
#include <QSize>
#include "smiletable.h"

class SmileDialog : public QDialog
{
    Q_OBJECT

private:
    SmileTable *table;
    QString nameSmile;

public:
    SmileDialog(QWidget *parent = 0);
    QString GetNameSmile();

public slots:
    void SelectedSmile(QString name);
};

#endif // SMILEDIALOG_H
