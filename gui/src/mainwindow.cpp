#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QDebug>

using namespace QOSIS;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setup();
}

MainWindow::~MainWindow()
{
	delete this->aboutAction;
    delete this->aboutWindow;
    delete this->preferencesAction;
    delete this->preferencesWindow;
    delete this->mainMenu;
    delete this->mainMenuBar;
    delete this->statusBar;
    delete ui;
}

void MainWindow::setup()
{
    this->aboutAction = new QAction(0);
    this->aboutAction->setMenuRole(QAction::AboutRole);
    this->aboutWindow = new About();
    this->preferencesAction = new QAction(0);
    this->preferencesAction->setMenuRole(QAction::PreferencesRole);
    this->preferencesWindow = new Preferences();
    ui->setupUi(this);
    this->mainMenuBar = new QMenuBar(0);
    this->mainMenu = new QMenu(0);
    this->mainMenuBar->addMenu(this->mainMenu);
    this->mainMenu->addAction(this->aboutAction);
    this->mainMenu->addAction(this->preferencesAction);

    connect(this->aboutAction, SIGNAL(triggered()), this->aboutWindow, SLOT(show()));
    connect(this->preferencesAction, SIGNAL(triggered()), this->preferencesWindow, SLOT(show()));

    this->statusBar = new QStatusBar();
    this->setStatusBar(this->statusBar);

    this->statusBar->showMessage("Ready.");
    this->setWindowTitle(tr("QOsis Text Application"));

    // CONNECTIONS
    connect(this->ui->btnQuit, SIGNAL(clicked()), this, SLOT(aboutToClose()));
    connect(this->ui->btnOpen, SIGNAL(clicked()), this, SLOT(openText()));

    _osis_hash = QHash<QString, QOsis*>();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    bool do_close = true;
    if (do_close) {
        event->accept();
    } else  {
        event->ignore();
    }
}

void MainWindow::aboutToClose()
{
    qDebug() << Q_FUNC_INFO;
    this->close(); // Automtically calls closeEvent() to see if this is successful
}

void MainWindow::openText()
{
    QFileDialog dialog(this);
    dialog.setWindowTitle(tr("Open OSIS Text Files"));
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(tr("OSIS Text Files (*.xml)"));

    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
    qDebug() << fileNames;
    foreach(const QString path, fileNames)
        loadFile(path);
}


void MainWindow::loadFile(const QString path)
{
    qDebug() << Q_FUNC_INFO << path;
    if (_osis_hash.contains(path)) {
        qDebug("File path already has been loaded");
        return; // TODO: Maybe show the loaded file in the ui (focus/view)
    }
    QFile file(path);
    if (! file.exists()) {
        QString warning = QString("File does not exist: %1").arg(path);
        qWarning(warning.toLatin1());
        return;
    }
    QOsis* osis = new QOsis(path);
    _osis_hash.insert(path, osis);
    this->setupOsisFile(path);
}

void MainWindow::setupOsisFile(const QString path, bool fully_render)
{
    qDebug() << Q_FUNC_INFO << path << fully_render;
    QOsisReader* reader = _osis_hash.value(path)->reader();
    qDebug() << reader->isValidPath() << "is a valid path";
    QOsisStructure* structure = reader->getOsisData();
    qDebug() << structure->title();
}
