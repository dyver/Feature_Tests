/****************************************************************************
** Form interface generated from reading ui file 'mydialog.ui'
**
** Created: Чт. авг. 29 16:27:00 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    MyDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~MyDialog();

    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QPushButton* buttonHelp;

protected:
    QVBoxLayout* Layout5;
    QSpacerItem* Spacer1;

protected slots:
    virtual void languageChange();

};

#endif // MYDIALOG_H
