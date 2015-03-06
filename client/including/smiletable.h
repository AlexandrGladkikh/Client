#ifndef SMILETABLE_H
#define SMILETABLE_H

#include <QTableWidget>
#include <QHeaderView>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QSize>
#include "smileitem.h"

#define NONE    "none"

class SmileTable : public QTableWidget
{
    Q_OBJECT

private:
    static const int columnCount = 8;
    static const int rowCount = 8;
    static const int COUNTSMILE = 62;
    static const int SMILESIZE = 20;
    static const int CELLSIZE = 26;

    QString SmileName[rowCount][columnCount];

    QPixmap arraySmilePixmap[COUNTSMILE];
    SmileItem arraySmileLabel[columnCount*rowCount];

public:
    SmileTable(QWidget *parent = 0);
    void FillingTable();

protected:
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void SmileSelected();

signals:
    void SmileNameFound(QString name);
};

#endif // SMILETABLE_H
