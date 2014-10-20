#include <UIClass.h>
#include <ui_Form.h>
#include <UIAggregateClass.h>
#include <UIInheritedClass.h>
#include <UILoader.h>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    auto uiClass = new UIClass;
    uiClass->show();

    auto directFormWidget = new QDialog;
    Ui::Form form;
    form.setupUi(directFormWidget);
    form.lineEdit->setText(QObject::tr("direct - no slots"));
    directFormWidget->setWindowTitle("Form");
    directFormWidget->show();

    auto uiAggregateClass = new UIAggregateClass;
    uiAggregateClass->show();

    auto uiInheritedClass = new UIInheritedClass;
    uiInheritedClass->show();

    auto uiLoader = new UILoader;
    uiLoader->show();

    return app.exec();
}
