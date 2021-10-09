#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <QTextBrowser>
#include <QObject>
#include <QWidget>

class TextArea: public QTextBrowser
{
    Q_OBJECT;
public:
    TextArea(QWidget *parent);
};

#endif // TEXTAREA_H
