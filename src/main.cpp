#include <workinstance.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WorkInstance wi(&a);

    return a.exec();
}
