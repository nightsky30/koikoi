#include "koikoi.h"
#include <QApplication>

/*
* Main Function
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    KoiKoi window;
    window.show();

    return app.exec();
}
