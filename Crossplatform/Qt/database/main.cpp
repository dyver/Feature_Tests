#include <QtWidgets>
#include <QtSql>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    auto db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("my database");
    db.setUserName("me");
    db.setHostName("host");
    db.setPassword("12345");

    if (not db.open()) {
        qDebug() << db.lastError();
    }

    QSqlQuery query;

    QString drop = "DROP TABLE base;";
    if (not query.exec(drop)) {
        qDebug() << "Unable to drop table";
    }

    QString create = "CREATE TABLE base ("
        "number INTEGER PRIMARY KEY NOT NULL, "
        "name VARCHAR(15), "
        "value VARCHAR(20) "
        ");";
    if (not query.exec(create)) {
        qDebug() << "Unable to create table";
    }

    QString addData = "INSERT INTO base (number, name, value) "
        "VALUES(%1, '%2', '%3');";
    addData = addData.arg("1", "Vinny", "12345");
    if (not query.exec(addData)) {
        qDebug() << "Unable to add data";
    }

    auto text = new QTextEdit;
    text->setReadOnly(true);

    QString select = "SELECT * FROM base";
    auto tables = db.tables();
    for (auto& table : tables) {
        text->insertHtml(QString("<h3>Table: <i>%1</i></h3>").arg(table));
        if (not query.exec(select)) {
            qDebug() << "Unable to select";
            continue;
        }
        auto record = query.record();
        while (query.next()) {
            auto number = query.value(record.indexOf("number")).toInt();
            auto name = query.value(record.indexOf("name")).toString();
            auto value = query.value(record.indexOf("value")).toString();
            text->insertHtml(QString("<br>Number: <i>%1</i>").arg(number));
            text->insertHtml(QString("<br>Name: <i>%1</i>").arg(name));
            text->insertHtml(QString("<br>Value: <i>%1</i>").arg(value));
            text->insertHtml(QString("<hr>"));
        }
        for (int i = 0; i < record.count(); ++i) {
            qDebug() << record.field(i);
        }
    }

    QTableView view;
    QSqlQueryModel model;
    model.setQuery(select);
    if (model.lastError().isValid()) {
        qDebug() << model.lastError();
    }
    view.setModel(&model);

    auto layout = new QVBoxLayout;

    layout->addWidget(text);
    layout->addWidget(&view);

    auto widget = new QWidget;
    widget->setLayout(layout);
    widget->show();

    return app.exec();
}
