#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore/QDebug>

using namespace QOSIS;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _osis(NULL),
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

    this->ui->osisTextView->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    _osis_view_model = new QStandardItemModel();

    this->ui->osisTreeView->setModel(_osis_view_model);
    this->ui->osisTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    _selection_model = this->ui->osisTreeView->selectionModel();
    connect(_selection_model, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(selectionChange(QItemSelection,QItemSelection)));
    connect(this->ui->osisTreeView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectionClicked(QModelIndex)));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    bool do_close = true;
    if (do_close) {
        event->accept();
    } else  {
        event->ignore();
    }
}

void MainWindow::aboutToClose()
{
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
    foreach(const QString path, fileNames)
        loadFile(path);
}

void MainWindow::selectionChange(QItemSelection selected, QItemSelection deselected)
{
    Q_UNUSED(deselected)
    int p = -1;
    QString text;
    text.reserve(this->_selection_model->selectedIndexes().count());
    foreach(QModelIndex idx, this->_selection_model->selectedIndexes()) {
        p = parents(idx);
        if (p == MainWindow::Verse) {
            // Display in text pane. This may not be efficient for spanning
            // multiple chapters or books, but it's proof of concept.
            QOsisStructure* structure = _osis->reader()->getOsisData();
            QOsisBook* book = structure->book(idx.parent().parent().data().toString());
            QOsisChapter* chap = book->chapter(idx.parent().row()+1);
            QOsisVerse* verse = chap->verse(idx.row()+1);
            text.append(QString("%1\n\n").arg(verse->verse()));
        }
    }
    this->ui->osisTextView->setPlainText(text);
}

void MainWindow::selectionClicked(QModelIndex selected)
{
}


void MainWindow::loadFile(const QString path)
{
    if (_osis != NULL) {
        qDebug("File path already has been loaded");
        return; // TODO: Maybe show the loaded file in the ui (focus/view)
    }
    QFile file(path);
    if (! file.exists()) {
        QString warning = QString("File does not exist: %1").arg(path);
        qWarning(warning.toLatin1());
        return;
    }
    _osis = new QOsis(path);
    this->setupOsisFile(path);
}

void MainWindow::setupOsisFile(const QString path)
{
    QOsisReader* reader = _osis->reader();
    QOsisStructure* structure = reader->getOsisData();
    foreach(const QString str, structure->books()) {
        QStandardItem* item = new QStandardItem(Ui::ICON_BOOK, str);
        item->setEditable(false);
        item->setData(str);
        this->_osis_view_model->appendRow(item);
        foreach(int chapter, structure->book(str)->chapters()) {
            QString itemName = QString("Chapter %1").arg(chapter);
            QStandardItem* chapterItem = new QStandardItem(Ui::ICON_CHAPTER, itemName);
            chapterItem->setEditable(false);
            chapterItem->setData(chapter);
            item->appendRow(chapterItem);
            // This QSI handles fully rendering. If true, it will be a verse, or if false,
            // we listen to chapter and render verses when chapter is expanded.
            foreach(int verse, structure->book(str)->chapter(chapter)->verses()) {
                QString verseName = QString("Verse %1").arg(verse);
                QStandardItem *verseItem = new QStandardItem(Ui::ICON_VERSE, verseName);
                verseItem->setEditable(false);
                verseItem->setData(verse);
                chapterItem->appendRow(verseItem);
            }
        }
    }
}

int MainWindow::parents(QModelIndex index)
{
    int parents = 0;
    while (index.parent().isValid()) {
        parents += 1;
        index = index.parent();
    }
    return parents;
}
