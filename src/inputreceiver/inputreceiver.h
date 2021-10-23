#ifndef INPUTRECEIVER_H
#define INPUTRECEIVER_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QKeyEvent>

class InputReceiver: public QWidget
{
    Q_OBJECT
public:
    InputReceiver(QWidget* parent = nullptr);

    // QWidget interface
protected:
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseReleaseEvent(QMouseEvent *event) override;
//    void mouseDoubleClickEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
//    void keyReleaseEvent(QKeyEvent *event) override;
//    void enterEvent(QEvent *event) override;
//    void leaveEvent(QEvent *event) override;
};

#endif // INPUTRECEIVER_H
