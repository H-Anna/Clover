#include "ghostwidget.h"

GhostWidget::GhostWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint)
{
    setWindowFlag(Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(this, SIGNAL(changeSurfaceSignal(const QString&)), this, SLOT(changeSurface(const QString&)));
    connect(this, SIGNAL(changeSurfaceSignal(const QString&)), this, SLOT(update()));

    QAction *quitAction = new QAction(tr("E&xit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    addAction(quitAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);

    emit changeSurfaceSignal(QString(R"(D:\D_Programs\GitHub\GhostTest\data\surface1501.png)"));

    qDebug() << "INFO - GhostWidget - The ghost has appeared.";
}

GhostWidget::~GhostWidget()
{
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
    displayedImage = QPixmap(path);
}


