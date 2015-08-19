#include <QApplication>
#include <QtQml>
#include "Utils.h"
#include "Settings.h"
#include "Interpreter.h"
#include "SproutDb.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<Interpreter>("Greenery.Lib", 1, 0, "Interpreter");

    Utils utils;
    Settings settings;
    SproutDb sproutDb;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("SETTINGS", &settings);
    engine.rootContext()->setContextProperty("SPROUT_DB", &sproutDb);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
