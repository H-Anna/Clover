#ifndef GHOSTWIDGET_H
#define GHOSTWIDGET_H

#include <iostream>

#include <QCoreApplication>
#include <QWidget>
#include <QAction>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

class GhostWidget : public QWidget
{
    Q_OBJECT

public:
    GhostWidget(QWidget *parent = nullptr);
    ~GhostWidget();

signals:
    void changeSurfaceSignal(const QString& path);
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPoint dragPosition;
    QPixmap displayedImage;
private slots:
    void changeSurface(const QString& path);

};
#endif // GHOSTWIDGET_H
