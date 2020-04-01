#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "BGraphics/BGraphicsScene.h"

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    // Select between OpenGL and OpenGL ES (Angle)
    //QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
#endif

    // macos 10.15 use 'thread' render loop, app will be crash
    qputenv("QSG_RENDER_LOOP", "basic");

    QGuiApplication a(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<BGraphicsScene>("BGraphicsScene", 1, 0, "BGraphicsScene");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return a.exec();
}
