#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "include/AvouchInstaller.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(adi);

    QApplication app(argc, argv);

#ifndef QT_NO_TRANSLATION
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        app.installTranslator(translator);
#endif


    AvouchInstaller wizard;
    wizard.show();
    //wizard.setWindowState(Qt::WindowMaximized);
    return app.exec();
}
