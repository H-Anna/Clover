#include "balloonwidget.h"

BalloonWidget::BalloonWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint)
{
    setWindowFlag(Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);

    /// TODO: implement "change balloon" tag
    connect(this, SIGNAL(changeBalloonSignal(const QString&)), this, SLOT(changeBalloon(const QString&)));
    connect(this, SIGNAL(changeBalloonSignal(const QString&)), this, SLOT(update()));

    changeBalloon(QString(R"(D:\D_Programs\GitHub\GhostTest\data\balloons0.png)"));
    textBrowser = nullptr;
    textCursor = 0;
    textHolder = new QPlainTextEdit(this);
    textHolder->hide();

    connect(textHolder, SIGNAL(textChanged()), this, SLOT(textBrowserUpdate()));

    textTimer = new QTimer(this);
    connect(textTimer, &QTimer::timeout, this, &BalloonWidget::printText);
    textTimer->setInterval(50);

    emit balloonLoadedSignal();

}

BalloonWidget::~BalloonWidget()
{
    delete textTimer;
    delete textBrowser;
    delete textHolder;
}

void BalloonWidget::printBalloonContents()
{
    if (textHolder != nullptr)
        qDebug() << "INFO - BalloonWidget - textHolder contains:";
        qDebug() << textHolder->toPlainText();
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

    if (textBrowser == nullptr)
        setupTextBrowser();

}

void BalloonWidget::setupTextBrowser()
{
    textBrowser = new QTextBrowser(this);
    textBrowser->setReadOnly(true);
    textBrowser->setAcceptRichText(true);
    textBrowser->setAttribute(Qt::WA_TranslucentBackground);
    textBrowser->setOpenLinks(false);
    textBrowser->setContextMenuPolicy(Qt::NoContextMenu);
    textBrowser->setFrameShape(QFrame::NoFrame);
    textBrowser->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    textBrowser->setMouseTracking(false);
    textBrowser->resize(QSize(displayedImage.size().width()-65, displayedImage.size().height()-70));
    textBrowser->move(30,15);

    connect(textBrowser, SIGNAL(anchorClicked(const QUrl &)), this, SLOT(PrintAnchor(const QUrl &)));

    QPalette p = textBrowser->palette();
    p.setColor(QPalette::Base, QColor(255,255,255,0));
    p.setColor(QPalette::Text, Qt::black);
    textBrowser->setPalette(p);

    textBrowser->show();
}

void BalloonWidget::prepareText(const QString &text)
{
    printingText = text;
    textTimer->start();
}

void BalloonWidget::printText()
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

void BalloonWidget::changeBalloon(const QString &path)
{
    displayedImage = QPixmap(path);
}

void BalloonWidget::textBrowserUpdate()
{
    if (textBrowser != nullptr) {
        textBrowser->setHtml(textHolder->toPlainText());
        textBrowser->moveCursor(QTextCursor::End);
    }
    else
        qDebug() << "ERROR - BalloonWidget - textBrowser = nullptr, can't print (textBrowserUpdate).";
}

void BalloonWidget::PrintAnchor(const QUrl &link)
{
    qDebug() << link.toString();
    if (link.scheme() == "http" || link.scheme() == "https") {
        QDesktopServices::openUrl(link);
    }
}
