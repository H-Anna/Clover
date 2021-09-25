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

signals:
    void changeSurfaceSignal(const QString& path);

public slots:
    //void changeSurface();
    void changeSurfaceSlot(int id);
    void changeSurfaceSlot(const QString& alias);

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
