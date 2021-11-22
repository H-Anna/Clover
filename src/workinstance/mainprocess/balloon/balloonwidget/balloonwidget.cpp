#include "balloonwidget.h"

BalloonWidget::BalloonWidget(VariableStore* _varStore, QWidget *parent):
    varStore(_varStore),
    displayedImage(QPixmap()),
    QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint | Qt::BypassWindowManagerHint),
    textSpeed(defaultTextSpeed),
    timeout(defaultBTimeout)
{
#ifdef QT_NO_DEBUG
    setAttribute(Qt::WA_TranslucentBackground);
#endif
    //setWindowFlag(Qt::SubWindow);

    textArea = nullptr;
    textCursor = 0;

    textTimer = new QTimer(this);
    connect(textTimer, &QTimer::timeout,
            this, &BalloonWidget::PrintText);

    connect(this, &BalloonWidget::finishedTextPrintSignal,
            textTimer, &QTimer::stop);

    textTimer->setInterval(textSpeed);

    balloonTimeout = new QTimer(this);
    balloonTimeout->setSingleShot(true);
    connect(balloonTimeout, &QTimer::timeout,
            this, &QWidget::hide);

}

BalloonWidget::~BalloonWidget()
{
//    disconnect(textTimer, &QTimer::timeout,
//            this, &BalloonWidget::PrintText);

//    disconnect(balloonTimeout, &QTimer::timeout, this, &QWidget::hide);

    balloonTimeout->stop();
    delete balloonTimeout;

    textTimer->stop();
    delete textTimer;

    delete textArea;
}

void BalloonWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void BalloonWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void BalloonWidget::paintEvent(QPaintEvent *)
{
    QRect target(QPoint(0,0), displayedImage.size());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPixmap(QPoint(0,0), displayedImage, target);

}

void BalloonWidget::SetupTextBrowser(QPoint topLeft, int width, int height)
{
    textArea = new TextArea(varStore, this);

    textArea->move(topLeft);
    textArea->resize(width, height);

    textArea->show();
}

void BalloonWidget::PrepareText(QString text)
{
    show();

    printingText = text;
    textCursor = 0;
    textTimer->start();
    qDebug() << "INFO - BalloonWidget - Text prepared";
}

void BalloonWidget::PrintText()
{
    if (textArea != nullptr) {
        textArea->textHolder->insertPlainText(printingText.at(textCursor));
        textCursor++;

        if (textCursor >= printingText.length()) {
            emit finishedTextPrintSignal();
        }
    }
    else
    {
        qDebug() << "ERROR - BalloonWidget - textArea = nullptr, can't print (PrintText).";
    }
}

void BalloonWidget::ChangeBalloon(const QString &path, QPoint TL, QPoint BR)
{
    displayedImage = QPixmap(path);
    int width = BR.x() - TL.x();
    int height = BR.y() - TL.y();

    textArea->deleteLater();

    SetupTextBrowser(TL, width, height);

    update();
    resize(displayedImage.size());
}

void BalloonWidget::ChangeTextSpeed(unsigned int newSpeed)
{
    textSpeed = newSpeed;
    textTimer->setInterval(textSpeed);
}

void BalloonWidget::PrepareTimeout()
{
    if (timeout > 0)
        balloonTimeout->start(timeout);

    ///TODO delete the below code

    qDebug() << textArea->textHolder->toPlainText();
}

void BalloonWidget::SetTimeout(unsigned int newTimeout)
{
    timeout = newTimeout;
}

QSize BalloonWidget::sizeHint() const
{
    /// TODO replace this dirty little trick
    return QSize(100,100);
}

void BalloonWidget::AppendHtml(const QString &text)
{
    if (textArea != nullptr)
    {
        show();
        textArea->textHolder->insertPlainText(text);
    }
}

void BalloonWidget::ClearBalloon()
{
    if (textArea != nullptr)
        textArea->textHolder->clear();
}

void BalloonWidget::PrintContents()
{
    if (textArea != nullptr)
        qDebug() << "INFO - BalloonWidget - textHolder contains:" << textArea->textHolder->toPlainText();

}
