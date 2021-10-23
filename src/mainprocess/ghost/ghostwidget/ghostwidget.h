#ifndef GHOSTWIDGET_H
#define GHOSTWIDGET_H

#include <frame.h>

#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QWidget>
#include <QAction>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QDebug>

class GhostWidget : public QWidget
{
    Q_OBJECT;

public:
    GhostWidget(unsigned int _layerCount = 1, QWidget *parent = nullptr);
    ~GhostWidget();

    void SetSurface(QVector<QString> images);

    QPixmap displayedImage;
    QVector<QPixmap> pixmaps;

public slots:
    void SetAnimation(QString image, unsigned int layer, Frame::DrawMethod dm);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPoint dragPosition;
    QRect baseRect;

    QPoint startPoint;
    unsigned int layerCount;

};
#endif // GHOSTWIDGET_H
