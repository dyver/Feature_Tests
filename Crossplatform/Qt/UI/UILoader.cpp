#include <QtWidgets>
#include <QtUiTools>

#include <UILoader.h>

UILoader::UILoader(QDialog* parent) : QDialog(parent) {
    auto loader = new QUiLoader(this);
    QFile file(":/Form.ui");
    auto form = loader->load(&file);
    if (form) {
        resize(form->size());
        label = form->findChild<QLabel*>("label");
        lineEdit = form->findChild<QLineEdit*>("lineEdit");
        lineEdit->setText(tr("Loader"));
        label->setBuddy(lineEdit);
        caseCheckBox = form->findChild<QCheckBox*>("caseCheckBox");
        backwardCheckBox = form->findChild<QCheckBox*>("backwardCheckBox");
        findButton = form->findChild<QPushButton*>("findButton");
        closeButton = form->findChild<QPushButton*>("closeButton");
    }

    connect(lineEdit, &QLineEdit::textChanged, this, &UILoader::enableFindButton);
    connect(findButton, &QPushButton::clicked, this, &UILoader::findClicked);
    connect(closeButton, &QPushButton::clicked, this, &UILoader::close);

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

void UILoader::findClicked() {
    auto text = lineEdit->text();
    auto cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void UILoader::enableFindButton(const QString& text) {
    findButton->setEnabled(!text.isEmpty());
}
