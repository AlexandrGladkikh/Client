#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void TextEdit::AddSmile(QString smile)
{
    insertHtml("<img src=:/images/" + smile + "/>");
}

QString TextEdit::GetMsg()
{
    QString text = toHtml();
    QString msg;

    clear();
    setTextColor(Qt::black);

    int startData = 0;
    int endData = 0;

    while (1)
    {
        startData = text.indexOf(STARTDATA, endData)+18;
        endData = text.indexOf(ENDPOS, endData);

        if (endData == -1)
            break;

        msg.append(text.mid(startData, endData - startData));
        endData++;
    }

    return msg;
}

void TextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        if (!toPlainText().isEmpty())
            emit ReadyData();
    }
    else
    {
        if (textColor() != QColor(Qt::black))
            setTextColor(Qt::black);
        QTextEdit::keyPressEvent(event);
    }
}
