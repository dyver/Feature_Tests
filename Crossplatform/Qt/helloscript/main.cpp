#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QTranslator>
#include <QtScript>
#include <iostream>

int main(int argc, char *argv[])
{
    //Q_INIT_RESOURCE(helloscript);

    QApplication app(argc, argv);

    QScriptEngine engine;

    QTranslator translator;
    bool res = translator.load("helloscript_ru");
    qDebug() << "Source code translator" << (res ? "Yes!" : "No!");
    QApplication::installTranslator(&translator);
    QTranslator translator1;
    res = translator1.load("helloscript1_ru");
    qDebug() << "Script translator" << (res ? "Yes!" : "No!");
    QApplication::installTranslator(&translator1);
    engine.installTranslatorFunctions();

    qDebug() << QObject::tr("Hello Script");

    QPushButton button;
    QScriptValue scriptButton = engine.newQObject(&button);
    engine.globalObject().setProperty("button", scriptButton);

    QString fileName(":/helloscript.js");
    QFile scriptFile(fileName);
    scriptFile.open(QIODevice::ReadOnly);
    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();
    scriptFile.close();

    QScriptValue result = engine.evaluate(contents, fileName);

    if (result.isError()) {
        QMessageBox::critical(0, QObject::tr("Hello Script"),
                              QString::fromLatin1("%0:%1: %2")
                              .arg(fileName)
                              .arg(result.property("lineNumber").toInt32())
                              .arg(result.toString()));
        return -1;
    }

    return app.exec();
}
