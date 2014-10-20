#ifndef UI_AGGREGATE_CLASS_H
#define UI_AGGREGATE_CLASS_H

#include <ui_Form.h>

class UIAggregateClass : public QDialog {
    Q_OBJECT
    public:
        UIAggregateClass(QDialog* parent = nullptr);
    signals:
        void findNext(const QString& str, Qt::CaseSensitivity cs);
        void findPrevious(const QString& str, Qt::CaseSensitivity cs);
    private slots:
        void findClicked();
        void enableFindButton(const QString& text);
    private:
        Ui::Form form;
};

#endif // UI_AGGREGATE_CLASS_H
