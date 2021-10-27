#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <QTextBrowser>
#include <QWidget>

#include <variablestore.h>

class TextArea: public QTextBrowser
{
    Q_OBJECT;
public:
    TextArea(QWidget *parent);

private slots:
    void EvaluateAnchor(QUrl url);

signals:
    void anchorTalkSignal(QString a);
    void openUrlSignal(QUrl url);
};

#endif // TEXTAREA_H
