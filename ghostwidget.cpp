#include "ghostwidget.h"

GhostWidget::GhostWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
{
    setWindowFlag(Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    /// TODO: implement change surface
    connect(this, SIGNAL(changeSurfaceSignal(const QString&)), this, SLOT(changeSurface(const QString&)));
    connect(this, SIGNAL(changeSurfaceSignal(const QString&)), this, SLOT(update()));

    QAction *quitAction = new QAction(tr("E&xit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);

    changeSurface(QString(R"(D:\D_Programs\GitHub\GhostTest\data\surface1501.png)"));

    emit ghostLoadedSignal();
}

GhostWidget::~GhostWidget()
{
}

void GhostWidget::changeSurfaceSlot(int id)
{
    //TODO

    qDebug() << "INFO - GhostWidget - Change to surface" << id;
}

void GhostWidget::changeSurfaceSlot(const QString &alias)
{
    //TODO

    qDebug() << "INFO - GhostWidget - Change to surface with alias" << alias;
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
    QRect target(QPoint(0,0), displayedImage.size());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(QPoint(0,0), displayedImage, target);
}

void GhostWidget::changeSurface(const QString &path)
{
    show();
    displayedImage = QPixmap(path);
}



