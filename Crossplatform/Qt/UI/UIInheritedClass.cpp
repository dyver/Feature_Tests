#include <UIInheritedClass.h>

UIInheritedClass::UIInheritedClass(QDialog* parent) : QDialog(parent) {
    setupUi(this);
    setWindowTitle("Form");
    lineEdit->setText(tr("Inherited"));
    connect(lineEdit, &QLineEdit::textChanged, this, &UIInheritedClass::enableFindButton);
    connect(findButton, &QPushButton::clicked, this, &UIInheritedClass::findClicked);
}

void UIInheritedClass::findClicked() {
    auto text = lineEdit->text();
    auto cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void UIInheritedClass::enableFindButton(const QString& text) {
    findButton->setEnabled(!text.isEmpty());
}
