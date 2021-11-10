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
    explicit HotspotWidget(VariableStore* varStore, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    int affection;
    int clicks;



signals:
    void hotspotTalkSignal(QString scheme, QString key);
};

#endif // HOTSPOTWIDGET_H
