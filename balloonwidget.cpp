#include "balloonwidget.h"

BalloonWidget::BalloonWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint)
{
    setAttribute(Qt::WA_TranslucentBackground);

    connect(this, SIGNAL(changeBalloonSignal(const QString&)), this, SLOT(changeBalloon(const QString&)));
    connect(this, SIGNAL(changeBalloonSignal(const QString&)), this, SLOT(update()));
    connect(this, SIGNAL(prepareTextSignal(const QString&)), this, SLOT(prepareText(const QString&)));

    changeBalloon(QString(R"(D:\D_Programs\GitHub\GhostTest\data\balloons0.png)"));
    textBrowser = nullptr;
    textIdx = 0;

    textTimer = new QTimer(this);
    connect(textTimer, &QTimer::timeout, this, &BalloonWidget::printText);
    textTimer->setInterval(10);
}

BalloonWidget::~BalloonWidget()
{

}

void BalloonWidget::printText()
{
    textBrowser->insertPlainText(printingText.at(textIdx));
    textIdx++;

    if (textIdx >= printingText.length()) {
        textIdx = 0;
        textTimer->stop();
    }
}

void BalloonWidget::changeBalloon(const QString &path)
{
    displayedImage = QPixmap(path);
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
    textBrowser->setAttribute(Qt::WA_TranslucentBackground);
    textBrowser->setFocusPolicy(Qt::WheelFocus);
    textBrowser->setContextMenuPolicy(Qt::NoContextMenu);
    textBrowser->setFrameShape(QFrame::NoFrame);
    textBrowser->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    textBrowser->setMouseTracking(false);
    textBrowser->resize(QSize(displayedImage.size().width()-65, displayedImage.size().height()-70));
    textBrowser->move(30,15);

    QPalette p = textBrowser->palette();
    p.setColor(QPalette::Base, QColor(255,255,255,0));
    p.setColor(QPalette::Text, Qt::black);
    textBrowser->setPalette(p);

    textBrowser->show();
    emit prepareTextSignal("Hello \nLorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas lacinia eros in elit tristique porttitor. Nam a consectetur augue. Mauris maximus, tellus sit amet vulputate volutpat, tellus lectus elementum urna, non malesuada justo tellus sed magna. Integer a ultricies felis. Proin nec efficitur nisi. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.");

}

void BalloonWidget::prepareText(const QString &text)
{
    printingText = text;
    textTimer->start();
}
