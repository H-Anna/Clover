#ifndef HOTSPOTWIDGET_H
#define HOTSPOTWIDGET_H

#include <hotspot.h>
#include <variablestore.h>

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

    // QWidget interface
public:
};

#endif // HOTSPOTWIDGET_H
