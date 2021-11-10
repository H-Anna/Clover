#include "balloonwidget.h"

BalloonWidget::BalloonWidget(VariableStore* _varStore, QWidget *parent):
    varStore(_varStore),
    QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint),
      textSpeed(defaultTextSpeed),
      timeout(defaultBTimeout)
{
    setWindowFlag(Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    textArea = nullptr;
    textCursor = 0;
    textHolder = new QPlainTextEdit(this);
    textHolder->hide();

    connect(textHolder, &QPlainTextEdit::textChanged,
            this, &BalloonWidget::TextBrowserUpdate);

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
    disconnect(textTimer, &QTimer::timeout,
            this, &BalloonWidget::PrintText);

    disconnect(balloonTimeout, &QTimer::timeout, this, &QWidget::hide);

    balloonTimeout->stop();
    delete balloonTimeout;

    textTimer->stop();
    delete textTimer;

    delete textArea;
    delete textHolder;
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
    if (textHolder != nullptr) {
        textHolder->insertPlainText(printingText.at(textCursor));
        textCursor++;

        if (textCursor >= printingText.length()) {
            emit finishedTextPrintSignal();
        }
    } else {
        qDebug() << "ERROR - BalloonWidget - textHolder = nullptr, can't print (printText).";
    }

}

void BalloonWidget::ChangeBalloon(const QString &path, QPoint TL, QPoint BR)
{
    displayedImage = QPixmap(path);
    int width = BR.x() - TL.x();
    int height = BR.y() - TL.y();

    textHolder->clear();
    textArea->deleteLater();

    SetupTextBrowser(TL, width, height);

    update();
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
}

void BalloonWidget::SetTimeout(unsigned int newTimeout)
{
    timeout = newTimeout;
}

void BalloonWidget::TextBrowserUpdate()
{
    if (textArea != nullptr) {

        textArea->setHtml(textHolder->toPlainText());
        textArea->moveCursor(QTextCursor::End);

    }
    else
        qDebug() << "ERROR - BalloonWidget - textArea = nullptr, can't print (textBrowserUpdate).";
}

QSize BalloonWidget::sizeHint() const
{
    //return baseRect.size();

    /// TODO replace this dirty little trick
    return QSize(1000,1000);
}

void BalloonWidget::ClearBalloon()
{

}
