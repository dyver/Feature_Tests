#ifndef UI_INHERITED_CLASS_H
#define UI_INHERITED_CLASS_H

#include <ui_Form.h>

class UIInheritedClass : public QDialog, public Ui::Form {
    Q_OBJECT
    public:
        UIInheritedClass(QDialog* parent = nullptr);
    signals:
        void findNext(const QString& str, Qt::CaseSensitivity cs);
        void findPrevious(const QString& str, Qt::CaseSensitivity cs);
    private slots:
        void findClicked();
        void enableFindButton(const QString& text);
};

#endif // UI_INHERITED_CLASS_H
