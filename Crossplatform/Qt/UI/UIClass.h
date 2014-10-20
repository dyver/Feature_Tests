#ifndef UI_CLASS_H
#define UI_CLASS_H

#include <QtWidgets>

class UIClass : public QDialog {
    Q_OBJECT
    public:
        UIClass(QDialog* parent = nullptr);
    signals:
        void findNext(const QString& str, Qt::CaseSensitivity cs);
        void findPrevious(const QString& str, Qt::CaseSensitivity cs);
    private slots:
        void findClicked();
        void enableFindButton(const QString& text);
    private:
        QLabel* label = nullptr;
        QLineEdit* lineEdit = nullptr;
        QCheckBox* caseCheckBox = nullptr;
        QCheckBox* backwardCheckBox = nullptr;
        QPushButton* findButton = nullptr;
        QPushButton* closeButton = nullptr;
};

#endif // UI_CLASS_H
