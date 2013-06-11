#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class FindDialog : public QDialog
{
    Q_OBJECT
    public:
        FindDialog(QWidget *parent = 0);
    signals:
        void findNext(const QString &str, Qt::CaseSensitivity cs);
        void findPrevious(const QString &str, Qt::CaseSensitivity cs);
    private slots:
        void findClicked();
        void enableFindButton(const QString &text);
        void createActions();
        void createToolBars();
    private:
        QLabel *label;
        QLineEdit *lineEdit;
        QCheckBox *caseCheckBox;
        QCheckBox *backwardCheckBox;
        QPushButton *findButton;
        QPushButton *closeButton;
        QAction *newAction;
        //QToolBar *toolBar;
};

#endif
