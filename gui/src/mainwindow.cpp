#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QDebug>

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
}

void MainWindow::loadFile(const QString path)
{
    qDebug() << Q_FUNC_INFO << path;
    QFile file(path);
    if (! file.exists()) {
        QString warning = QString("File does not exist: %1").arg(path);
        qWarning(warning.toLatin1());
        return;
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << file.readAll();
        file.close();
    }
}
