#ifndef MYTEXTBROWSER_H
#define MYTEXTBROWSER_H

#include <QTextBrowser>

class MyTextBrowser: public QTextBrowser
{
public:
    MyTextBrowser(QObject* parent = nullptr);
};

#endif // MYTEXTBROWSER_H
