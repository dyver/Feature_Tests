#include <QtWidgets>

#include <findDialog.h>

FindDialog::FindDialog(QWidget* parent) : QDialog(parent) {
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("E&xit"));

    connect(lineEdit, &QLineEdit::textChanged, this, &FindDialog::enableFindButton);
    connect(findButton, &QPushButton::clicked, this, &FindDialog::findClicked);
    connect(closeButton, &QPushButton::clicked, this, &FindDialog::close);

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());

    createActions();

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/woodbackground.png")));
    setPalette(palette);
    QPixmap pixmap(":/images/woodbutton.png");
    QColor color(192, 128, 64);
    QPalette palette1;
    for (int i = 0; i < QPalette::NColorGroups; ++i) {
        palette.setBrush(QPalette::ColorGroup(i), QPalette::Button, QBrush(color, pixmap));
        palette.setBrush(QPalette::ColorGroup(i), QPalette::Base, QBrush(color, pixmap));
        findButton->setPalette(palette);
        closeButton->setPalette(palette);
        caseCheckBox->setPalette(palette);
        backwardCheckBox->setPalette(palette);
        palette1.setBrush(QPalette::ColorGroup(i), QPalette::Base, QBrush(color));
        lineEdit->setPalette(palette1);
    }
}

void FindDialog::findClicked() {
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void FindDialog::enableFindButton(const QString& text) {
    findButton->setEnabled(!text.isEmpty());
}

void FindDialog::createActions() {
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, &QAction::triggered, this, &FindDialog::close);
    addAction(newAction);
}
