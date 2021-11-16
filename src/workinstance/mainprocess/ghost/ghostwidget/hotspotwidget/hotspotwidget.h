#ifndef HOTSPOTWIDGET_H
#define HOTSPOTWIDGET_H

#include <hotspot.h>
#include <variablestore.h>

#include <algorithm>

#include <QObject>
#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class HotspotWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HotspotWidget(VariableStore* varStore, QList<HotspotVariable*> _variables, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    QList<HotspotVariable*> variables;

signals:
    void incrementSignal(QString key);
    void hotspotTalkSignal(QString scheme, QString key);
};

#endif // HOTSPOTWIDGET_H
