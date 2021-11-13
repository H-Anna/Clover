#ifndef BALLOONWIDGET_H
#define BALLOONWIDGET_H

#include <textarea.h>

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QElapsedTimer>

#include <QDebug>

class BalloonWidget: public QWidget
{
    Q_OBJECT
public:
    BalloonWidget(VariableStore* _varStore, QWidget *parent = nullptr);
    ~BalloonWidget();
    QSize sizeHint() const override;

    void AppendHtml(const QString &text);
    void ClearBalloon();
    void PrintContents();

    //QPlainTextEdit* textHolder;

signals:
    void balloonLoadedSignal();
    void finishedTextPrintSignal();

public slots:
    void PrepareText(QString text);
    void ChangeBalloon(const QString& path, QPoint TL, QPoint BR);
    void ChangeTextSpeed(unsigned int newSpeed);
    void PrepareTimeout();
    void SetTimeout(unsigned int newTimeout);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPoint dragPosition;
    QPixmap displayedImage;

    TextArea* textArea;

    const unsigned int defaultTextSpeed = 50;
    const unsigned int defaultBTimeout = 20000;

    unsigned int timeout;
    unsigned int textCursor;
    unsigned int textSpeed;
    QTimer* textTimer;
    QString printingText;

    QTimer* balloonTimeout;

    VariableStore* varStore;

    void SetupTextBrowser(QPoint topLeft, int width, int height);

private slots:
    void PrintText();

//    void TextBrowserUpdate();
};

#endif // BALLOONWIDGET_H
