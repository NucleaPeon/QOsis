#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QHash>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMenu>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QAction>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QTreeView>
#include <QtGui/QStandardItemModel>
#include <QtGui/QCloseEvent>

#include "about.h"
#include "preferences.h"

#include <qosis.h>

namespace Ui {
class MainWindow;
const static QIcon ICON_BOOK = QIcon();
const static QIcon ICON_CHAPTER = QIcon();
const static QIcon ICON_VERSE = QIcon();
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
    /*!
     * \brief setupOsisFile takes the osis path (now recorded in hash) and renders it to view
     * \param path
     * \param fully_render boolean that if true, will create all verse tree nodes, otherwise will create them only when chapter is opened.
     *
     * Using the QStandardItemModel, we build a tree of:
     *  - book
     *      + books within the book
     *          + chapters within book
     *              + verses within book
     *
     */
    void setupOsisFile(const QString path, bool fully_render = false);

    Ui::MainWindow *ui;
    QMenu *mainMenu;
    QMenuBar *mainMenuBar;
    QAction *aboutAction;
    QAction *preferencesAction;
    About *aboutWindow;
    Preferences *preferencesWindow;
    QStatusBar *statusBar;
    QStandardItemModel* _osis_view_model;
    QItemSelectionModel* _selection_model;

    QHash<QString, QOsis*> _osis_hash;
};

#endif // MAINWINDOW_H
