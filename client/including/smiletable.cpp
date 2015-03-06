#include "smiletable.h"

SmileTable::SmileTable(QWidget *parent) : QTableWidget(parent)
{
    setColumnCount(columnCount);
    setRowCount(rowCount);
    verticalHeader()->hide();
    horizontalHeader()->hide();
    setSelectionMode(QAbstractItemView::SingleSelection);
    horizontalHeader()->setDefaultSectionSize(CELLSIZE);
    verticalHeader()->setDefaultSectionSize(CELLSIZE);
    setShowGrid(false);
    setFixedSize(QSize(CELLSIZE*columnCount+2, CELLSIZE*rowCount+2));
    setFocusPolicy(Qt::NoFocus);
    setStyleSheet("QTableWidget::item::selected {background: rgba(130, 176, 246, 80);}");//#61B7CF;
    setMouseTracking(true);

    QObject::connect(this, SIGNAL(cellClicked(int,int)), this, SLOT(SmileSelected()));
}

void SmileTable::FillingTable()
{
    QString name;
    QPixmap pixmap;

    for (int i=0; i < COUNTSMILE ; i++)
    {
        name = ":/images/" + QString::number(i) + ".png";
        if (!pixmap.load(name))
            exit(1);
        arraySmilePixmap[i] = pixmap.scaled(QSize(SMILESIZE, SMILESIZE), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        arraySmileLabel[i].setPixmap(arraySmilePixmap[i]);
        arraySmileLabel[i].setAlignment(Qt::AlignCenter);
    }

    for (int i=0; i < rowCount; i++)
        for (int j=0; j < columnCount; j++)
        {
            setCellWidget(i, j, &arraySmileLabel[i*columnCount + j]);

            if (i*columnCount+j >= COUNTSMILE)
                SmileName[i][j] = NONE;
            else
                SmileName[i][j] = QString::number(i*columnCount + j) + ".png";
        }


}

void SmileTable::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    setCurrentCell(point.y()/CELLSIZE, point.x()/CELLSIZE);
}

void SmileTable::SmileSelected()
{
    QString name;
    name = SmileName[currentRow()][currentColumn()];

    if (name != NONE)
        emit SmileNameFound(name);
}
