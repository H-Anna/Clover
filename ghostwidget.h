#ifndef GHOSTWIDGET_H
#define GHOSTWIDGET_H

#include <QCoreApplication>
#include <QWidget>
#include <QAction>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QDebug>

class GhostWidget : public QWidget
{
    Q_OBJECT

public:
    GhostWidget(QWidget *parent = nullptr);
    ~GhostWidget();

    QPixmap displayedImage;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPoint dragPosition;

};
#endif // GHOSTWIDGET_H
