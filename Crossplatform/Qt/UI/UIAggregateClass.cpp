#include <UIAggregateClass.h>

UIAggregateClass::UIAggregateClass(QDialog* parent) : QDialog(parent) {
    form.setupUi(this);
    setWindowTitle("Form");
    form.lineEdit->setText(tr("Aggregate"));
    connect(form.lineEdit, &QLineEdit::textChanged, this, &UIAggregateClass::enableFindButton);
    connect(form.findButton, &QPushButton::clicked, this, &UIAggregateClass::findClicked);
}

void UIAggregateClass::findClicked() {
    auto text = form.lineEdit->text();
    auto cs = form.caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (form.backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void UIAggregateClass::enableFindButton(const QString& text) {
    form.findButton->setEnabled(!text.isEmpty());
}
