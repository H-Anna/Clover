#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <QTextBrowser>
#include <QWidget>
#include <QMouseEvent>
#include <QPlainTextEdit>

#include <variablestore.h>

class TextArea: public QTextBrowser
{
    Q_OBJECT
public:
    TextArea(VariableStore* varStore, QWidget *parent);
    ~TextArea();

    QPlainTextEdit* textHolder;

private:

    void TextBrowserUpdate();
private slots:
    void EvaluateAnchor(QUrl url);

signals:
    void anchorTalkSignal(QString scheme, QString path);
    //void keyTalkSignal(QString k);
    void openUrlSignal(QUrl url);
    void stopPrintingSignal();

    // QWidget interface
protected:
    //void mouseReleaseEvent(QMouseEvent *event) override { qDebug() << event->type(); };
};

#endif // TEXTAREA_H
