#include "ghostwidget.h"

GhostWidget::GhostWidget(unsigned int _layerCount, QWidget *parent):
    QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
    layerCount(_layerCount)
{
    setWindowFlag(Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    QAction *quitAction = new QAction(tr("E&xit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);

    pixmaps.reserve(layerCount);

    //move(width()-100, height()-100);
}

GhostWidget::~GhostWidget()
{
}

void GhostWidget::SetSurface(QVector<QString> images)
{
    //TODO drawmethod

    pixmaps.clear();
    pixmaps.reserve(layerCount);
    for (unsigned int i = 0; i < layerCount; i++) {

        if (i >= images.length() || images.at(i) == "")
            pixmaps.append(QPixmap());
        else
            pixmaps.append(images.at(i));

    }
    baseSize = pixmaps.at(0).size();
    update();
}

void GhostWidget::SetAnimation(QString image, unsigned int layer, DrawMethod dm)
{

    switch (dm) {

    case DrawMethod::Base: {
        // TODO
    }
    case DrawMethod::Clip: {
        // TODO
    }
    case DrawMethod::Overlay: {
        pixmaps.append(QPixmap(image));
        break;
    }
    case DrawMethod::Insert: {
        if (layer > pixmaps.length())
            layer = pixmaps.length();
        pixmaps.insert(layer, QPixmap(image));
        break;
    }
    case DrawMethod::Replace: {

        int diff = layer - pixmaps.length();
        if (diff < 0) {

            pixmaps.replace(layer, QPixmap(image));

        } else {
            while (diff > 0) {
                pixmaps.append(QPixmap());
                diff--;
            }

            pixmaps.append(QPixmap(image));
        }
        break;
    }
    default: {
        qDebug() << "ERROR - GhostWidget - SetAnimation encountered an unhandled DrawMethod, specified image will not draw.";
        return;
    }

    }



    update();
}

void GhostWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void GhostWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void GhostWidget::paintEvent(QPaintEvent *)
{
    //QRect target(QPoint(0,0), displayedImage.size());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.drawPixmap(QPoint(0,0), displayedImage, target);
    //painter.drawPixmap(QPoint(0,0), pixmaps.at(0));

    for (auto &it: pixmaps) {
        if (it != QPixmap()) {
            painter.drawPixmap(QPoint(0,0), it);
        }
    }


}


