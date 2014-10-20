#include <QtWidgets>

#include <UIClass.h>

UIClass::UIClass(QDialog* parent) : QDialog(parent) {
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    lineEdit->setText(tr("Class"));
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);

    closeButton = new QPushButton(tr("E&xit"));

    connect(lineEdit, &QLineEdit::textChanged, this, &UIClass::enableFindButton);
    connect(findButton, &QPushButton::clicked, this, &UIClass::findClicked);
    connect(closeButton, &QPushButton::clicked, this, &UIClass::close);

    auto topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    auto leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    auto rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    auto mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Form"));
    setFixedHeight(sizeHint().height());
}

void UIClass::findClicked() {
    auto text = lineEdit->text();
    auto cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void UIClass::enableFindButton(const QString& text) {
    findButton->setEnabled(!text.isEmpty());
}
