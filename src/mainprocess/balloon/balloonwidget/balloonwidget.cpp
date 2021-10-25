#include "balloonwidget.h"

BalloonWidget::BalloonWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint),
      textSpeed(defaultTextSpeed)
{
    setWindowFlag(Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    textArea = nullptr;
    textCursor = 0;
    textHolder = new QPlainTextEdit(this);
    textHolder->hide();

    connect(textHolder, SIGNAL(textChanged()), this, SLOT(TextBrowserUpdate()));

    textTimer = new QTimer(this);
    connect(textTimer, &QTimer::timeout, this, &BalloonWidget::PrintText);
    textTimer->setInterval(textSpeed);

    balloonTimeout = new QTimer(this);
    balloonTimeout->setSingleShot(true);
    connect(balloonTimeout, &QTimer::timeout, this, &QWidget::hide);

}

BalloonWidget::~BalloonWidget()
{
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

//    if (textArea == nullptr)
//        SetupTextBrowser();

}

void BalloonWidget::SetupTextBrowser(QPoint topLeft, int width, int height)
{
    textArea = new TextArea(this);

    textArea->move(topLeft);
    textArea->resize(width, height);

    connect(textArea, SIGNAL(anchorClicked(QUrl)),
            this, SLOT(PrintAnchor(QUrl)));

    textArea->show();
}

void BalloonWidget::PrepareText(QString text)
{
    show();
    if (balloonTimeout->isActive())
        balloonTimeout->stop();

    printingText = text;
    textTimer->start();
}

void BalloonWidget::PrintText()
{
    if (textHolder != nullptr) {
        textHolder->insertPlainText(printingText.at(textCursor));
        textCursor++;

        if (textCursor >= printingText.length()) {
            textCursor = 0;
            textTimer->stop();
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
    /// Times out in 10 seconds.
    balloonTimeout->start(10000);
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

void BalloonWidget::PrintAnchor(QUrl link)
{
    qDebug() << link.toString();
    if (link.scheme() == "http" || link.scheme() == "https") {
        QDesktopServices::openUrl(link);
    }
}

QSize BalloonWidget::sizeHint() const
{
    //return baseRect.size();

    /// TODO replace this dirty little trick
    return QSize(1000,1000);
}
