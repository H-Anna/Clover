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

    void changeSurface(const QString& path);

signals:
    void ghostLoadedSignal();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPoint dragPosition;
    QPixmap displayedImage;
private slots:

};
#endif // GHOSTWIDGET_H
