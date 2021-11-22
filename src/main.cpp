#include <workinstance.h>

#if defined(_WIN32) && defined(QT_NO_DEBUG)
    #include <windows.h>
#endif

int main(int argc, char *argv[])
{

#if defined(_WIN32) && defined(QT_NO_DEBUG)
    FreeConsole();
#endif

    QApplication a(argc, argv);

    WorkInstance wi(&a);

    return a.exec();
}
