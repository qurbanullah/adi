#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QFile>
#include <QPalette>
#include <QFont>

#include "include/AvouchInstaller.h" // Assuming this path is correct

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(adi);

    QApplication app(argc, argv);

#ifndef QT_NO_TRANSLATION
    QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName, QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
        app.installTranslator(translator);
#endif

    // Change the text color to white
    QPalette p = app.palette();
    p.setColor(QPalette::Text, Qt::white);
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::ButtonText, Qt::white);
    p.setColor(QPalette::BrightText, Qt::white);
    app.setPalette(p);

    AvouchInstaller wizard;
    // Change the background color (can be done in the stylesheet)
    // wizard.setStyleSheet("background-color: #0b2732;");

    // Add stylesheet to the application
    QFile file(":/qss/default.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        wizard.setStyleSheet(styleSheet);
        file.close();
    } else {
        qWarning("Failed to open stylesheet file!");
    }

    wizard.show();
    // wizard.setWindowState(Qt::WindowMaximized);
    return app.exec();
}