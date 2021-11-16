#include "ghostwidget.h"

GhostWidget::GhostWidget(VariableStore* _varStore, unsigned int _layerCount, QWidget *parent):
    varStore(_varStore),
    QWidget(parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint),
    layerCount(_layerCount)
{
    //setWindowFlag(Qt::SubWindow);
    setAttribute(Qt::WA_TranslucentBackground);
    setAutoFillBackground(false);
    setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));

    setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *quitAction = new QAction(tr("E&xit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));

    connect(quitAction, &QAction::triggered,
            qApp, &QCoreApplication::quit);

    addAction(quitAction);

    auto screen = QGuiApplication::primaryScreen();
    screen->availableGeometry();
    startPoint = screen->availableGeometry().center();

    pixmaps.reserve(layerCount);

    connect(this, SIGNAL(randomTalkSignal()),
            _varStore->GetMember("TalkManager"), SLOT(RandomTalk()));

    connect(this, SIGNAL(anchorTalkSignal(QString,QString)),
            _varStore->GetMember("TalkManager"), SLOT(AnchorTalk(QString,QString)));

}

GhostWidget::~GhostWidget()
{
    for (auto &it: hotspots) {
        delete it;
    }
}

void GhostWidget::SetSurface(QVector<QString> images)
{
    //TODO drawmethod?

    pixmaps.clear();
    pixmaps.reserve(layerCount);
    for (unsigned int i = 0; i < images.length(); i++) {

        if (images.at(i) == "")
            pixmaps.append(QPixmap(0,0));
        else
            pixmaps.append(images.at(i));

    }

    baseRect = pixmaps.at(0).rect();

    update();
}

void GhostWidget::SetHotspots(QVector<Hotspot *> hs)
{
    for (auto &it: hotspots) {
        delete it;
    }

    hotspots.clear();

    for (auto &it: hs) {
        auto tmp = new HotspotWidget(varStore, it->GetVariables(), this);

        tmp->move(it->getTopLeft());
        int width = it->getBottomRight().x() - it->getTopLeft().x();
        int height = it->getBottomRight().y() - it->getTopLeft().y();
        tmp->resize(width, height);
        tmp->setCursor(QCursor(it->getCursor()));

        hotspots.append(tmp);
    }

    update();
}

void GhostWidget::SetAnimation(QString image, unsigned int layer, Frame::DrawMethod dm)
{

    switch (dm) {

    case Frame::DrawMethod::Base: {
        // TODO
    }
    case Frame::DrawMethod::Clip: {
        // TODO
    }
    case Frame::DrawMethod::Overlay: {
        pixmaps.append(QPixmap(image));
        break;
    }
    case Frame::DrawMethod::Insert: {
        if (layer > pixmaps.length())
            layer = pixmaps.length();
        pixmaps.insert(layer, QPixmap(image));
        break;
    }
    case Frame::DrawMethod::Replace: {

        int diff = layer - pixmaps.length();
        if (diff < 0) {

            pixmaps.replace(layer, QPixmap(image));

        } else {
            while (diff > 0) {
                pixmaps.append(QPixmap(0,0));
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
        //event->accept();
    }
}

void GhostWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        //event->accept();
    }
}

void GhostWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        //dragPosition = event->globalPos() - frameGeometry().topLeft();
        emit anchorTalkSignal("key", "MENU");
        //event->accept();
    }
}

void GhostWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < pixmaps.length(); i++) {

        /// Comparing two QPixmaps directly results in a QCursor error... for some reason.

        if (pixmaps.at(i).operator QVariant() != QPixmap(0,0).operator QVariant()) {

            painter.drawPixmap(QPoint(0,0), pixmaps.at(i));
        }
    }
}

void GhostWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->text().toLower() == "t") {
        emit randomTalkSignal();
        //event->accept();
    }
    grabKeyboard();
}

QSize GhostWidget::sizeHint() const
{
    //return baseRect.size();

    /// TODO replace this dirty little trick
    return QSize(1000,1000);
}



