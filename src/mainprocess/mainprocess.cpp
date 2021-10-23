#include "mainprocess.h"

MainProcess::MainProcess(VariableStore *_vs, unsigned int _layerCount, QVector<Surface *> defSurf, QVector<BalloonSurface *> defBall):
    vs(_vs),
    ghost(new Ghost(defSurf, _layerCount)),
    balloon(new Balloon(defBall)),
    currentTC(nullptr),
    tokenCursor(0)
{

    ghostBalloonsMap.insert(ghost->GetID(ghost->GetInScope()),
                            QList<unsigned int>({ balloon->GetID(balloon->GetInScope()) }) );

    /// --------IMPORTANT SIGNALS--------

    /// Each time this signal fires, evaluate the next token

    connect(this, SIGNAL(finishedTokenEvaluationSignal()),
            this, SLOT(EvaluateTokens()));

    connect(this, SIGNAL(printTextSignal(const QString&)),
            balloon, SIGNAL(printTextSignal(const QString&)));

    connect(balloon, SIGNAL(finishedTextPrintSignal()),
            this, SIGNAL(finishedTokenEvaluationSignal()));

    connect(this, SIGNAL(changeScopeSignal(unsigned int)),
            ghost, SLOT(ChangeScope(unsigned int)));

    connect(this, SIGNAL(changeScopeSignal(unsigned int)),
            balloon, SLOT(ChangeScope(unsigned int)));

    connect(this, SIGNAL(endOfTokensSignal()),
            balloon, SIGNAL(timeoutSignal()));


    /// ------------LAMBDA MAP------------

    BuildTagLambdaMap();
}

MainProcess::~MainProcess()
{

    delete ghost;
    delete balloon;

    delete currentTC;

    QMapIterator t(tagLambdaMap);
    while (t.hasNext()) {
        t.next();
        delete &t.value();
    }

    tagLambdaMap.clear();
}

void MainProcess::EvaluateTokens()
{
    if (currentTC == nullptr)
        return;

    auto token = currentTC->GetNextToken();

    qDebug().noquote() << QString("INFO - MainProcess - Token: \"%1\"  ||  Type: %2").arg(token->GetContents(),
                                                                        QMetaEnum::fromType<Token::TokenType>().valueToKey(token->GetType()));

    switch (token->GetType()) {
        case Token::CommandTag:
        {
            ExecuteCommand(token);
            break;
        }

        case Token::HtmlTag:
        {
            balloon->AppendHtml(token->GetContents());
            emit finishedTokenEvaluationSignal();
            break;
        }

        case Token::PlainText:
        {
            emit printTextSignal(token->GetContents());
            break;
        }

        case Token::End:
        {
            /// DO NOT EMIT finishedTokenEvaluationSignal OR ELSE IT WILL LOOP FOREVER
            //balloon->PrintBalloonContents();
            qDebug() << "INFO - MainProcess - All tokens have been passed.";
            emit endOfTokensSignal();

            break;
        }

        default:
        {
            qDebug() << QString("WARNING - MainProcess - Unexpected token type %1").arg(
                            QMetaEnum::fromType<Token::TokenType>().valueToKey(token->GetType()));
            qDebug().noquote() << "Token parameters: " << token->GetParams() << "  ||  Token contents: " << token->GetContents();

            emit finishedTokenEvaluationSignal();
            break;
        }

    }
}

void MainProcess::SaveTokenCollection(TokenCollection &tc)
{
    currentTC = &tc;
}

Ghost *MainProcess::GetGhost() const
{
    return ghost;
}

Balloon *MainProcess::GetBalloon() const
{
    return balloon;
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

    tagLambdaMap = QMap<QString, tagLambdaPtr>();

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

    tagLambdaMap.insert("speed", [](MainProcess& mp, const QStringList& params){

        bool canConvert;
        int spd = params.at(0).toInt(&canConvert);

        if (canConvert) {
            mp.balloon->ChangeTextSpeed(spd);

        } else {
            qDebug() << "ERROR - MainProcess - Couldn't convert parameter to int, skipping token.";
        }

        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("b",[](MainProcess& mp, const QStringList& params){

        if (params.count() > 1) {
            qDebug() << "WARNING - MainProcess - Balloon change tag has multiple parameters. Skipping token.";
        } else {
            emit mp.applyBalloonSignal(params);
        }

        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("s",[](MainProcess& mp, const QStringList& params){

        if (params.count() > 1) {
            qDebug() << "WARNING - MainProcess - Surface change tag has multiple parameters. Skipping token.";
        } else {
            emit mp.applySurfaceSignal(params);
        }

        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("i",[](MainProcess& mp, const QStringList& params){

        if (params.count() > 1) {
            qDebug() << "WARNING - MainProcess - Animation change tag has multiple parameters. Skipping token.";
        } else {
            emit mp.applyAnimationSignal(params, mp.ghost->GetCurrentSurface());
        }

        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("p",[](MainProcess& mp, const QStringList& params){

        if (params.count() > 1) {
            qDebug() << "ERROR - MainProcess - Scope change tag has multiple parameters. Skipping token.";
        } else {

            bool canConvert;
            unsigned int id = params.at(0).toInt(&canConvert);

            if (!canConvert) {
                qDebug() << "ERROR - MainProcess - Scope change tag can't be converted to int. Skipping token.";
            } else {
                emit mp.changeScopeSignal(id);
            }
        }

        emit mp.finishedTokenEvaluationSignal(); });

    tagLambdaMap.insert("get",[](MainProcess& mp, const QStringList& params){

        if (params.count() != 1) {

            qDebug() << "ERROR - MainProcess - Get variable tag only accepts 1 parameter. Skipping token.";
            emit mp.finishedTokenEvaluationSignal();

        } else {
            auto val = mp.vs->GetVariable(params.at(0));

            if (!val.isValid()) {
                qDebug().noquote() << QString("WARNING - MainProcess - GET value of %1 is EMPTY").arg(params.at(0));
            }

            qDebug().noquote() << QString("INFO - MainProcess - GET value of %1 is %2").arg(params.at(0), val.toString());

            emit mp.printTextSignal(val.toString());

        }

        });

    tagLambdaMap.insert("set",[](MainProcess& mp, const QStringList& params){

        if (params.count() != 2) {

            qDebug() << "ERROR - MainProcess - Set variable tag only accepts 2 parameters. Skipping token.";

        } else {

            ///TODO replace this

            mp.vs->SetVariable(params.at(0), params.at(1));
            qDebug().noquote() << QString("INFO - MainProcess - SET value of %1 to %2")
                                  .arg(params.at(0), mp.vs->GetVariable(params.at(0)).toString());

        }

        emit mp.finishedTokenEvaluationSignal(); });

    /// TODO: does every single lambda function have to emit FTE? This makes it possible for other
    /// objects to block MainProcess until they're finished, but it's very redundant. Also
    /// makes it possible for a semantic error (forgetting to emit FTE) to happen.
}

void MainProcess::ExecuteCommand(const Token *token)
{
    auto tag = token->GetContents();

    if (tagLambdaMap.contains(tag)) {
        auto params = token->GetParams();
        tagLambdaMap.value(tag)(*this, params);

    } else {
        qDebug().noquote() << QString("WARNING - MainProcess - CommandTag %1 is not part of tagLambdaMap. Skipping token.").arg(tag);
        emit finishedTokenEvaluationSignal();
    }
}


