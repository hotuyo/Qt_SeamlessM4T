#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
  QApplication *app;
  app = dynamic_cast<QApplication*>(QApplication::instance());
  if(app) {
      return 0;
  } else {
    app = new QApplication(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:Main/main.qml"_qs);
    engine.addImportPath(":/");
    engine.addImportPath("qrc:/");
    engine.load(url);
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app->exec();
  }
}
