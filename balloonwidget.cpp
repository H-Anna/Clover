#include "balloonwidget.h"

BalloonWidget::BalloonWidget(QWidget *parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint)
{
    setAttribute(Qt::WA_TranslucentBackground);

    connect(this, SIGNAL(changeBalloonSignal(const QString&)), this, SLOT(changeBalloon(const QString&)));
    connect(this, SIGNAL(changeBalloonSignal(const QString&)), this, SLOT(update()));
    connect(this, SIGNAL(printTextSignal(const QString&)), this, SLOT(printText(const QString&)));

    setupTextBrowser();
    changeBalloon(QString(R"(Z:\GhostTest/data/balloons0.png)"));
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

#include <QBitmap>

void BalloonWidget::setupTextBrowser()
{
    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    textEdit->setAttribute(Qt::WA_TranslucentBackground);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setContextMenuPolicy(Qt::NoContextMenu);
    textEdit->setFrameShape(QFrame::NoFrame);
    textEdit->resize(QSize(displayedImage.size().width()-65, displayedImage.size().height()-70));
    //textEdit->resize(120,30);
    textEdit->move(30,15);
    textEdit->setText("Hello \nLorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas lacinia eros in elit tristique porttitor. Nam a consectetur augue. Mauris maximus, tellus sit amet vulputate volutpat, tellus lectus elementum urna, non malesuada justo tellus sed magna. Integer a ultricies felis. Proin nec efficitur nisi. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Vestibulum varius, lorem sit amet varius mattis, massa enim fringilla magna, sed ornare eros nisl sit amet erat. Phasellus dapibus feugiat vehicula. Sed nec condimentum lectus. Fusce nec est dolor. Nulla non sapien justo. In scelerisque turpis nulla, eget placerat sem rutrum eu.\n"
                      "Nulla consequat nisi sit amet blandit scelerisque. Integer fermentum venenatis tellus, sit amet fermentum justo elementum aliquet. Fusce in ipsum erat. Nam nulla tellus, elementum ac venenatis eget, maximus a nisi. Etiam pretium ut nisi et ullamcorper. Ut ultrices tempus ex, molestie fringilla tellus euismod sed. Mauris id neque at tortor lacinia consequat et sed arcu.\n"
                      "Nullam nec leo sapien. Mauris quis ultrices arcu, eget hendrerit purus. Proin aliquet posuere leo, at tempor elit viverra sit amet. Nullam porta turpis rutrum sem elementum venenatis. Donec at mi sagittis, dignissim ligula ut, gravida mauris. Aliquam in velit non ligula convallis feugiat. Maecenas quis malesuada magna. Aenean elementum tellus in sem ornare convallis. Ut semper rhoncus elit, non porttitor tellus volutpat sed. Praesent fermentum commodo nunc in blandit.\n"
                      "Nam venenatis dolor at sem scelerisque pulvinar. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas ligula magna, molestie eu arcu id, ullamcorper sagittis diam. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Proin faucibus augue vel hendrerit bibendum. Maecenas fringilla consequat est et interdum. Phasellus venenatis neque justo, ac dictum sem pulvinar in. Nunc convallis auctor orci, at vulputate lectus hendrerit et. Nullam ut dui accumsan, luctus eros non, iaculis elit. Aenean fringilla purus ac lectus congue, et rutrum diam molestie. Praesent mattis libero vitae tortor volutpat sollicitudin. Cras fermentum varius neque nec tincidunt. Cras aliquam ornare ipsum, sit amet egestas erat.\n"
                      "Nam a lacus id libero faucibus vulputate. Nam suscipit tellus et dictum aliquet. Quisque purus purus, pellentesque a ultrices ut, porttitor eget dui. Quisque dignissim egestas nunc et congue. Vivamus imperdiet placerat feugiat. Aenean commodo imperdiet sem quis vestibulum. Maecenas at consectetur tellus, ut sollicitudin nisl. In et elit dolor.");

    QPalette p = textEdit->palette(); // define pallete for textEdit..
    p.setColor(QPalette::Base, QColor(255,255,255,0)); // set color "Red" for textedit base
    p.setColor(QPalette::Text, Qt::black); // set text color which is selected from color pallete
    textEdit->setPalette(p); // change textedit palette

    textEdit->show();
}
