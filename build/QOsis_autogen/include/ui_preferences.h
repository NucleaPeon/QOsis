/********************************************************************************
** Form generated from reading UI file 'preferences.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCES_H
#define UI_PREFERENCES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Preferences
{
public:

    void setupUi(QWidget *Preferences)
    {
        if (Preferences->objectName().isEmpty())
            Preferences->setObjectName(QStringLiteral("Preferences"));
        Preferences->resize(400, 300);

        retranslateUi(Preferences);

        QMetaObject::connectSlotsByName(Preferences);
    } // setupUi

    void retranslateUi(QWidget *Preferences)
    {
        Preferences->setWindowTitle(QApplication::translate("Preferences", "Preferences", 0));
    } // retranslateUi

};

namespace Ui {
    class Preferences: public Ui_Preferences {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCES_H
