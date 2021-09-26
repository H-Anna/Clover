#include "mainprocess.h"

MainProcess::MainProcess(TalkManager &tm)
{
    ghostWidgets = QList<GhostWidget*>();
    balloonWidgets = QList<BalloonWidget*>();

    ghostInScope = new GhostWidget();
    ghostWidgets.append(ghostInScope);

    balloonInScope = new BalloonWidget();
    balloonWidgets.append(balloonInScope);

    ghostWidgets.at(0)->show();
    balloonWidgets.at(0)->show();

    /// --------IMPORTANT SIGNALS--------

    /// On receiving a token from the TM, evaluate it

    connect(&tm, SIGNAL(TokenReadySignal(const QString&)),
            this, SLOT(EvaluateToken(const QString&)));

    /// On having evaluated a token, ask for more

    connect(this, SIGNAL(finishedTokenEvaluationSignal()),
            &tm, SLOT(GetNextToken()));

    /// ---------------------------------

    /// -----------TAG SIGNALS-----------

    /// Tag signals can be connected and disconnected.
    /// This is to make everything easier when eventually, scope tags are introduced.
    ///
    /// TODO: scope tags.
    ///
    /// TODO: if you have multiple characters in your ghost, switching scope will disconnect signals from one,
    /// and connect to another. I have no idea how CPU- or memory-intensive this process is, but when I find out
    /// I will evaluate other options, such as passing a parameter to help evaluate which widget should be
    /// listening to a particular signal.
    ///
    /// TODO: When switching scope, DISCONNECT pointer signals, CHANGE pointer, then RECONNECT signals
    ///
    /// TODO: SEMANTIC ERROR: connecting a new signal but forgetting to disconnect it. How to get around this?

    ConnectTagSignals(*ghostInScope);
    ConnectTagSignals(*balloonInScope);

    /// ------------LAMBDA MAP------------

    /// Also making sure the TalkManager and MainProcess use the same tag regex.

    tagRegex = tm.GetTagRegex();
    BuildTagLambdaMap();
}

MainProcess::~MainProcess()
{
    /// Disconnect all signals before pointer destruction

    while (!ghostWidgets.isEmpty()) {
        auto w = ghostWidgets.takeFirst();
        DisconnectTagSignals(*w);
        delete w;
    }

    while (!balloonWidgets.isEmpty()) {
        auto w = balloonWidgets.takeFirst();
        DisconnectTagSignals(*w);
        delete w;
    }

    delete ghostInScope;
    delete balloonInScope;

    for (auto &it: tagLambdaMap.values()) {
        delete &it;
    }

    tagLambdaMap.clear();
}

void MainProcess::EvaluateToken(const QString &token)
{
    QString tag;
    QStringList params = QStringList();

    auto match = tagRegex.match(token);

    /// Command tag
    if (match.hasMatch()) {

        /// Take tag (key in map) and see if there's any parameters

        tag = match.captured(1);
        auto _p = match.captured(2);

        if (!_p.isNull()) {
            auto _list = _p.split(',', Qt::SkipEmptyParts);

            for (auto &it: _list)
                it = it.trimmed();

            params = _list;
        }

        /// Choose lambda to execute based on tag, using a map...

        if (tagLambdaMap.contains(tag)) {

            tagLambdaMap[tag](*this, params);

        } else {

            /// ...or print WARNING to console if the tag is not defined.
            /// TODO: use exceptions instead?

            qDebug() << "WARNING - MainProcess - Tag not defined in tagLambdaMap.";
            printUndefinedTag(tag, params);
            emit finishedTokenEvaluationSignal();
        }
    }

    /// If no tag was detected, it's just plaintext, so display it.

    else {
        /// Prints to balloon. Waits for finishedTextPrintSignal!
        emit printTextSignal(token);
    }
}

void MainProcess::printUndefinedTag(const QString &tag, const QStringList &params)
{
    qDebug() << "Undefined tag:" << tag << "Parameters:" << params;
}

void MainProcess::BuildTagLambdaMap()
{
    /// This part fills me with existential dread...
    /// With typedef in the header, we create a type for a function that takes in a MainProcess& and
    /// a const QStringList& as parameters and returns nothing. It is called "tagLambdaPtr".
    /// Then we assign this type as the value type for the QMap we build and then we can
    /// insert key-value pairs where the value is the function with the qualities described.
    /// I don't fully understand how it works, why it works and how I made it work.
    ///
    /// PLEASE DON'T CHANGE IT UNLESS YOU KNOW WHAT YOU'RE DOING.

    typedef void (*tagLambdaPtr)(MainProcess&, const QStringList&);

    tagLambdaMap = QMap<QString, tagLambdaPtr>();

    /// There are two ways you can go about this.
    ///
    /// - Function calls: simple to understand but may block thread and cause app to freeze. Use carefully.
    ///                     REMEMBER to emit finishedTokenEvaluationSignal afterwards.
    ///
    /// - Signal emission: asynchronous, preferable.
    /// How to use:
    ///     1. Create a private signal for your purpose within sender (this) class.
    ///         1.a Optional: Also create a public signal for your purpose within receiver class (eg. GhostWidget).
    ///     2. Create a public slot within receiver class.
    ///     3. Connect sender's signal to receiver's slot.
    ///         3.a Optional: OR connect sender's signal to receiver's signal, then receiver's signal to receiver's slot.
    ///     4. Implement slot functionality.
    ///     5. Create a public "finished" signal in receiver.
    ///     6. Connect "finished" to this class's finishedTokenEvaluationSignal. You MUST connect them within THIS class.

    /// Function call examples
    tagLambdaMap.insert("wait", [](MainProcess& mp, const QStringList& params){
        QTimer::singleShot(params.at(0).toInt(), &mp, &MainProcess::finishedTokenEvaluationSignal); });

    /// You can omit "params" if you don't use it in your lambda to get rid of warnings.
    tagLambdaMap.insert("clr", [](MainProcess& mp, const QStringList&){
        mp.balloonInScope->clearBalloonText();
        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("hide", [](MainProcess& mp, const QStringList&){
        mp.ghostInScope->hide();
        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("show", [](MainProcess& mp, const QStringList&){
        mp.ghostInScope->show();
        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("s",[](MainProcess& mp, const QStringList& params){

        if (params.count() > 1) {
            qDebug() << "WARNING - MainProcess - Surface change tag has multiple parameters, UNHANDLED CASE. No signal emitted.";
            return;
        }

        QString str = params[0];
        bool canConvertToInt;
        str.toInt(&canConvertToInt);

        if (canConvertToInt) {
            mp.ghostInScope->changeSurfaceSlot(str.toInt());
        } else {
            mp.ghostInScope->changeSurfaceSlot(str);
        }

        emit mp.finishedTokenEvaluationSignal(); });

}

void MainProcess::ConnectTagSignals(const GhostWidget &w)
{
    connect(this, SIGNAL(changeSurfaceSignal(int)),
            &w, SLOT(changeSurfaceSlot(int)));

    connect(this, SIGNAL(changeSurfaceSignal(const QString&)),
            &w, SLOT(changeSurfaceSlot(const QString&)));
}

void MainProcess::ConnectTagSignals(const BalloonWidget &w)
{
    connect(this, SIGNAL(printTextSignal(const QString&)),
            &w, SLOT(prepareText(const QString&)));

    /// On receiving certain signals, emit signal for asking for tokens.
    /// Chaining signals together is useful!

    connect(&w, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTokenEvaluationSignal()));
}

void MainProcess::DisconnectTagSignals(const GhostWidget &w)
{
    disconnect(this, SIGNAL(changeSurfaceSignal(int)),
            &w, SLOT(changeSurfaceSlot(int)));

    disconnect(this, SIGNAL(changeSurfaceSignal(const QString&)),
            &w, SLOT(changeSurfaceSlot(const QString&)));
}

void MainProcess::DisconnectTagSignals(const BalloonWidget &w)
{
    disconnect(this, SIGNAL(printTextSignal(const QString&)),
            &w, SLOT(prepareText(const QString&)));

    disconnect(&w, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTokenEvaluationSignal()));
}


