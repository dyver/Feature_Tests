#include <QApplication>
#include  <QStyleFactory>

#include <QDialog>
#include <QtWidgets>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog : public QDialog {
    Q_OBJECT
    public:
FindDialog(QWidget* parent = 0) : QDialog(parent) {
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

    signals:
        void findNext(const QString& str, Qt::CaseSensitivity cs);
        void findPrevious(const QString& str, Qt::CaseSensitivity cs);
    private slots:
void findClicked() {
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked()) {
        emit findPrevious(text, cs);
    } else {
        emit findNext(text, cs);
    }
}

void enableFindButton(const QString& text) {
    findButton->setEnabled(!text.isEmpty());
}

void createActions() {
    newAction = new QAction(tr("&New"), this);
    newAction->setShortcut(tr("Ctrl+N"));
    newAction->setStatusTip(tr("Create a new file"));
    connect(newAction, &QAction::triggered, this, &FindDialog::close);
    addAction(newAction);
}

    private:
        QLabel* label;
        QLineEdit* lineEdit;
        QCheckBox* caseCheckBox;
        QCheckBox* backwardCheckBox;
        QPushButton* findButton;
        QPushButton* closeButton;
        QAction* newAction;
};

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  //QApplication::setStyle(new Style);
  QApplication::setStyle(QStyleFactory::create("windows"));
  FindDialog* dialog = new FindDialog;
  dialog->show();
  return app.exec();
}

#include "main.moc"
