#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QHash>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QFileDialog>
#include <QtGui/QCloseEvent>

#include "about.h"
#include "preferences.h"

#include <qosis.h>

namespace Ui {
class MainWindow;
}

/*!
 * \brief The MainWindow class shows and configures the main application
 *
 * qosis-gui's purpose is to load, view and show import/export functions that can
 * be utilized from the libqosis library.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void aboutToClose();
    void openText();

private:
    void setup();
    void loadFile(const QString path);

    Ui::MainWindow *ui;
    QMenu *mainMenu;
    QMenuBar *mainMenuBar;
    QAction *aboutAction;
    QAction *preferencesAction;
    About *aboutWindow;
    Preferences *preferencesWindow;
    QStatusBar *statusBar;

    QHash<QString, QOsisReader*> _osis_hash;
};

#endif // MAINWINDOW_H
