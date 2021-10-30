#ifndef GHOSTWIDGET_H
#define GHOSTWIDGET_H

#include <frame.h>
#include <hotspotwidget.h>
#include <hotspot.h>

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
    Q_OBJECT

public:
    GhostWidget(unsigned int _layerCount = 1, QWidget *parent = nullptr);
    ~GhostWidget();
    QSize sizeHint() const override;

    void SetSurface(QVector<QString> images);
    void SetHotspots(QVector<Hotspot*> hs);

public slots:
    void SetAnimation(QString image, unsigned int layer, Frame::DrawMethod dm);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPoint dragPosition;
    QRect baseRect;

    QPixmap displayedImage;
    QVector<QPixmap> pixmaps;

    QPoint startPoint;
    unsigned int layerCount;

    QVector<HotspotWidget*> hotspots;

signals:
    void randomTalkSignal();

};
#endif // GHOSTWIDGET_H
