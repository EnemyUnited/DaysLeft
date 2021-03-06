/****************************************************************************
**
** Copyright (c) 2015, Rafat Rashid <enemyunited@gmail.com>
**
** Permission to use, copy, modify, and/or distribute this software for any
** purpose with or without fee is hereby granted, provided that the above
** copyright notice and this permission notice appear in all copies.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
** WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
** ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
** WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
** ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
** OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
**
****************************************************************************/

#include "MainWindow.h"
#include "constants.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QApplication>
#include <QTextEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("DaysLeft " APPVERSTR);
    createMenus();

    dlView = new DLView(this);
    setCentralWidget(dlView);

    QSettings settings("DaysLeft", "DaysLeft");
    resize(settings.value("winSize", QSize(320, 300)).toSize());
}

MainWindow::~MainWindow() {
}

// Create File and Help menus
void MainWindow::createMenus() {
    // File menu actions
    QAction *newListAct = new QAction("&New Empty List", this);
    newListAct->setShortcut(QKeySequence("Ctrl+N"));
    connect(newListAct, SIGNAL(triggered()), this, SLOT(onNewListAction()));

    QAction *openNewListAct = new QAction("&Open New List...", this);
    openNewListAct->setShortcut(QKeySequence("Ctrl+O"));
    connect(openNewListAct, SIGNAL(triggered()), this, SLOT(onOpenNewListAction()));

    QAction *appendToListAct = new QAction("&Append to Current List...", this);
    appendToListAct->setShortcut(QKeySequence("Shift+A"));
    connect(appendToListAct, SIGNAL(triggered()), this, SLOT(onAppendToListAction()));

    saveListAct = new QAction("&Save List", this);
    saveListAct->setShortcut(QKeySequence("Ctrl+S"));
    saveListAct->setEnabled(false);
    connect(saveListAct, SIGNAL(triggered()), this, SLOT(onSaveListAction()));

    QAction *saveListAsAct = new QAction("Save List &As...", this);
    saveListAsAct->setShortcut(QKeySequence("Shift+S"));
    connect(saveListAsAct, SIGNAL(triggered()), this, SLOT(onSaveListAsAction()));

    for (int i=0; i<MAX_RECENT_FILES; i++) {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(onOpenRecentFileAction()));
    }

    // Create File menu
    QMenu *fileMenu = new QMenu("&File", this);
    fileMenu->addAction(newListAct);
    fileMenu->addAction(openNewListAct);
    fileMenu->addAction(appendToListAct);
    fileMenu->addAction(saveListAct);
    fileMenu->addAction(saveListAsAct);

    recentFilesSep = fileMenu->addSeparator();
    for (int i=0; i<MAX_RECENT_FILES; i++)
        fileMenu->addAction(recentFileActs[i]);
    updateRecentFileActions();

    // Help menu actions
    QAction *dlHelpAct = new QAction("DaysLeft Help", this);
    connect(dlHelpAct, SIGNAL(triggered()), this, SLOT(onDLHelpAction()));

    QAction *aboutAppAct = new QAction("About App", this);
    connect(aboutAppAct, SIGNAL(triggered()), this, SLOT(onAboutAppAction()));

    QAction *aboutQtAct = new QAction("About Qt", this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // Create Help menu
    QMenu *helpMenu = new QMenu("&Help", this);
    helpMenu->addAction(dlHelpAct);
    helpMenu->addAction(aboutAppAct);
    helpMenu->addAction(aboutQtAct);

    // Add menus to menuBar
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);
}

void MainWindow::updateRecentFileActions() {
    QSettings settings("DaysLeft", "DaysLeft");
    QStringList filePaths = settings.value("recentFilePaths").toStringList();
    int numRecentFiles = filePaths.size();

    for (int i=0; i<numRecentFiles; i++) {
        QString fileName = QFileInfo(filePaths[i]).fileName();
        recentFileActs[i]->setText("&"+QString::number(i+1)+" "+fileName);
        recentFileActs[i]->setData(filePaths[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int i=numRecentFiles; i<MAX_RECENT_FILES; i++)
        recentFileActs[i]->setVisible(false);

    recentFilesSep->setVisible(numRecentFiles > 0);
}

// Load event list from an XML file.
// param appendToList: Appends to current list if true. Wipes otherwise.
void MainWindow::onOpenAction(bool appendToList) {
    QSettings settings("DaysLeft", "DaysLeft");
    QString myPath = settings.value("lastFilePath", QVariant(QDir::homePath())).toString();
    QString filePath = QFileDialog::getOpenFileName(this, "Open File", myPath, "XML files (*.xml)");
    openFile(filePath, appendToList);
}

void MainWindow::openFile(const QString &filePath, bool appendToList) {
    // Test to see if we can open the file
    if (!filePath.isEmpty()) {
        QFileInfo fileInfo(filePath);

        if (!fileInfo.isDir()) {
            QSettings settings("DaysLeft", "DaysLeft");
            settings.setValue("lastFilePath", QVariant(filePath));

            // Once opened, load the events from the file
            if (dlView->getModel()->readEventsFromFile(filePath, appendToList)) {
                setOpenedFile(filePath);
                saveListAct->setEnabled(true);
            }
            else QMessageBox::warning(this, "Warning", "Invalid file chosen.");
        }
        else QMessageBox::warning(this, "Warning", "Selection is a directory and cannot be opened.");
    }
}

// Remember currently opened file and update recently opened file list.
void MainWindow::setOpenedFile(const QString &filePath) {
    openedFile = filePath;

    QSettings settings("DaysLeft", "DaysLeft");
    QStringList filePaths = settings.value("recentFilePaths").toStringList();

    filePaths.removeOne(filePath);
    if (filePaths.size() == MAX_RECENT_FILES)
        filePaths.removeLast();
    filePaths.prepend(filePath);

    settings.setValue("recentFilePaths", filePaths);
    updateRecentFileActions();
}

// Triggered when the app is closed
void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings settings("DaysLeft", "DaysLeft");
    settings.setValue("winSize", size());

    QWidget::closeEvent(event);
}

/*** File menu actions ***/

// Remove any events in current list and create a new, empty list.
void MainWindow::onNewListAction() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Action", "Remove events in current list and create a new, empty list?");

    if (reply == QMessageBox::Yes)
        dlView->getModel()->clearList();
}

// Load event list from an XML file. Will wipe existing list.
void MainWindow::onOpenNewListAction() {
    onOpenAction(false);
}

// Load event list from an XML file.
// Will append the data to the end of the current event list.
void MainWindow::onAppendToListAction() {
    onOpenAction(true);
}

// Save current list to the previously opened/saved XML file.
// Existing file contents will be overwritten.
void MainWindow::onSaveListAction() {
    if (!dlView->getModel()->writeEventsToFile(openedFile))
        QMessageBox::warning(this, "Warning", "Unable to save events to file."
                             " Use 'SaveAs' to save to a different file.");
}

// Save current list to an XML file that the user selects.
// Existing file contents will be overwritten.
void MainWindow::onSaveListAsAction() {
    QSettings settings("DaysLeft", "DaysLeft");
    QString myPath = settings.value("lastFilePath", QVariant(QDir::homePath())).toString();

    QString filePath = QFileDialog::getSaveFileName(this, tr("Save As"), myPath, "XML files (*.xml)");
    if (!filePath.isEmpty()) {
        settings.setValue("lastFilePath", QVariant(filePath));

        if (dlView->getModel()->writeEventsToFile(filePath)) {
            openedFile = filePath;
            saveListAct->setEnabled(true);
        }
        else QMessageBox::warning(this, "Warning", "Unable to save events to file.");
    }
}

void MainWindow::onOpenRecentFileAction() {
    QAction *action = qobject_cast<QAction *>(sender());
    if (action) {
        QMessageBox::StandardButton appendToList =
                QMessageBox::question(this, "Append?", "Append to current list?");
        openFile(action->data().toString(), appendToList==QMessageBox::Yes);
    }
}

// Displays the help html page in a modal window.
void MainWindow::onDLHelpAction() {
    QFile file(":/resources/helpPage.html");
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, "Warning", "Unable to open help page.");
        return;
    }

    QTextStream in(&file);
    QString htmlText = in.readAll();
    file.close();

    QTextEdit *helpPage = new QTextEdit();
    helpPage->setReadOnly(true);
    helpPage->setWindowTitle("DaysLeft " APPVERSTR " Help");
    helpPage->setHtml(htmlText);
    helpPage->resize(590, 510);
    helpPage->show();
}

void MainWindow::onAboutAppAction() {
    QMessageBox::about(this, "DaysLeft " APPVERSTR,
                       "<div style='background-color: #FFF; text-align: center'>"
                            "<table style='background-color: #FFF'><tr><td width='160px'>"
                            "<b>Developed by:</b> Rafat Rashid<br>"
                            "<b>Version:</b> " APPVERSTR " (" APPDATESTR ")<br><br>"
                            "<a href='http://individual.utoronto.ca/rafatrashid/'>http://individual.utoronto.ca/rafatrashid/</a>"
                            "</td></tr></table></div>");
}
