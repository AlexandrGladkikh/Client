#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QString>

#define STARTDATA "text-indent"
#define ENDPOS    "</p>"

class TextEdit : public QTextEdit
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = 0);
    void AddSmile(QString smile);
    QString GetMsg();

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void ReadyData();
};

#endif // TEXTEDIT_H
