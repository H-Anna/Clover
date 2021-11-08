#include <workinstance.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WorkInstance wi(a.applicationDirPath());

    return a.exec();
}
