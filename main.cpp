#include "toolsmenuwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolsMenuWidget w;
    w.show();
    return a.exec();
}
