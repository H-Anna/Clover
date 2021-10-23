#ifndef HOTSPOTWIDGET_H
#define HOTSPOTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class HotspotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HotspotWidget(QWidget *parent = nullptr);

signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // HOTSPOTWIDGET_H
