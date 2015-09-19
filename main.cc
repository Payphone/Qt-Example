#include <QtGui>
#include <QWindowsVistaStyle>
#include "application.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);

    Application application; 
    QApplication::setStyle(new QWindowsVistaStyle());
    application.show();

    return app.exec();
}
