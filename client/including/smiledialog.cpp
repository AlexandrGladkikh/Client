#include "smiledialog.h"

SmileDialog::SmileDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(QStringLiteral("Выбор смайла"));
    table = new SmileTable(this);
    table->FillingTable();
    setFixedSize(QSize(table->width(), table->height()));
    QObject::connect(table, SIGNAL(SmileNameFound(QString)), this, SLOT(SelectedSmile(QString)));
}

QString SmileDialog::GetNameSmile()
{
    return nameSmile;
}

void SmileDialog::SelectedSmile(QString name)
{
    nameSmile = name;
    accept();
}
