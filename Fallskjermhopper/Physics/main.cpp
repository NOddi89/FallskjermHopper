#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QtQml>
#include "ode.h"
#include "simpleprojectile.h"
#include "dragprojectile.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // qmlRegisterType<ODE>("mycode", 1, 0, "ODE");
    qmlRegisterType<SimpleProjectile>("mycode", 1, 0, "SimpleProjectile");
    qmlRegisterType<DragProjectile>("mycode", 1, 0, "DragProjectile");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
