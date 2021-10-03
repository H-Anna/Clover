#include "mainprocess.h"

MainProcess::MainProcess(SurfaceManager *_sm)
    :
    ghost(new Ghost()),
    balloon(new Balloon()),
    currentTC(nullptr),
    tokenCursor(0),
    sm(_sm)
{

    ghostBalloonsMap.insert(ghost->GetID(ghost->GetInScope()),
                            QList<int>({ balloon->GetID(balloon->GetInScope()) }) );

    /// --------IMPORTANT SIGNALS--------

    /// Each time this signal fires, evaluate the next token

    connect(this, SIGNAL(finishedTokenEvaluationSignal()),
            this, SLOT(EvaluateTokens()));

    connect(this, SIGNAL(printTextSignal(const QString&)),
            balloon, SIGNAL(printTextSignal(const QString&)));

    connect(balloon, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTokenEvaluationSignal()));


    /// ------------LAMBDA MAP------------

    BuildTagLambdaMap();
}

MainProcess::~MainProcess()
{

    delete ghost;
    delete balloon;

    delete currentTC;

    for (auto &it: tagLambdaMap.values()) {
        delete &it;
    }

    tagLambdaMap.clear();
    delete sm;
}

void MainProcess::EvaluateTokens()
{
    if (currentTC == nullptr)
        return;

    auto token = currentTC->GetNextToken();

    qDebug().noquote() << "INFO - MainProcess - Token:" << token.getContents() << " Type:" << token.getType();

    switch (token.getType()) {
        case Token::CommandTag:
        {
            ExecuteCommand(token);
            break;
        }

        case Token::HtmlTag:
        {
            balloon->AppendHtml(token.getContents());
            emit finishedTokenEvaluationSignal();
            break;
        }

        case Token::PlainText:
        {
            emit printTextSignal(token.getContents());
            break;
        }

        case Token::End:
        {
            /// DO NOT EMIT finishedTokenEvaluationSignal OR ELSE IT WILL LOOP FOREVER
            balloon->PrintBalloonContents();
            qDebug() << "INFO - MainProcess - All tokens have been passed.";

            break;
        }

        default:
        {
            qDebug() << "WARNING - MainProcess - Unexpected token type" << token.getType();
            qDebug().nospace() << "Token parameters: " << token.getParams() << "  ||  Token contents: " << token.getContents();

            emit finishedTokenEvaluationSignal();
            break;
        }

    }
}

void MainProcess::SaveTokenCollection(TokenCollection &tc)
{
    currentTC = &tc;
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
        mp.balloon->ClearBalloon();
        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("hide", [](MainProcess& mp, const QStringList&){
        mp.ghost->Hide();
        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("show", [](MainProcess& mp, const QStringList&){
        mp.ghost->Show();
        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("s",[](MainProcess& mp, const QStringList& params){

        if (params.count() > 1) {
            qDebug() << "WARNING - MainProcess - Surface change tag has multiple parameters, UNHANDLED CASE. Skipping to next token.";
            emit mp.finishedTokenEvaluationSignal();
            return;
        }

        QString str = params[0];
        bool canConvertToInt;
        str.toInt(&canConvertToInt);

        Surface* s;
        if (canConvertToInt) {

            s = mp.sm->GetSurface(str.toInt());
        } else {

            s = mp.sm->GetSurface(str);
        }

        if (s == nullptr) {
            qDebug().nospace() << "WARNING - MainProcess - No surface found with param " << str << ", skipping to next token.";
            emit mp.finishedTokenEvaluationSignal();
            return;
        }

        mp.ghost->ChangeSurface(s->GetImage());

        emit mp.finishedTokenEvaluationSignal(); });

    /// TODO: does every single lambda function have to emit FTE? This makes it possible for other
    /// objects to block MainProcess until they're finished, but it's very redundant. Also
    /// makes it possible for a semantic error (forgetting to emit FTE) to happen.
}

void MainProcess::ExecuteCommand(const Token &token)
{
    auto tag = token.getContents();

    if (tagLambdaMap.keys().contains(tag)) {
        auto params = token.getParams();
        tagLambdaMap[tag](*this, params);

    } else {
        qDebug() << "WARNING - MainProcess - CommandTag" << tag << "is not part of tagLambdaMap. Skipping to next token.";
        emit finishedTokenEvaluationSignal();
    }
}


