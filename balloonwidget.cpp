#include "balloonwidget.h"

BalloonWidget::BalloonWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint)
{
    setAttribute(Qt::WA_TranslucentBackground);

    connect(this, SIGNAL(changeBalloonSignal(const QString&)), this, SLOT(changeBalloon(const QString&)));
    connect(this, SIGNAL(changeBalloonSignal(const QString&)), this, SLOT(update()));
    connect(this, SIGNAL(printTextSignal(const QString&)), this, SLOT(printText(const QString&)));

    setupTextBrowser();
    changeBalloon(QString(R"(D:\D_Programs\GitHub\GhostTest\data\balloons0.png)"));
//    printText(QString("Lorem Ipsum is simply dummy text of the printing and typesetting industry. "
//                                "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and "
//                                "scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, "
//                                "remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, "
//                                "and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum."));

//    emit changeBalloonSignal(QString(R"(D:\D_Programs\GitHub\GhostTest\data\balloons0.png)"));
//    emit printTextSignal(QString("Lorem Ipsum is simply dummy text of the printing and typesetting industry. "
//                            "Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and "
//                            "scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, "
//                            "remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, "
//                            "and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum."));
}

BalloonWidget::~BalloonWidget()
{

}

void BalloonWidget::printText(const QString &text)
{
    textEdit->setText(text);
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

    setupTextBrowser();

}

void BalloonWidget::setupTextBrowser()
{
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    textEdit->setAttribute(Qt::WA_TransparentForMouseEvents);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setContextMenuPolicy(Qt::NoContextMenu);
    textEdit->resize(displayedImage.size());
    textEdit->move(0,0);
    textEdit->setText("Hello");

    QPalette p = textEdit->palette(); // define pallete for textEdit..
    p.setColor(QPalette::Base, Qt::TransparentMode); // set color "Red" for textedit base
    p.setColor(QPalette::Text, Qt::black); // set text color which is selected from color pallete
    textEdit->setPalette(p); // change textedit palette

    textEdit->show();
}
