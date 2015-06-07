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

#ifndef MAINWINDOW_H
    #define MAINWINDOW_H

    #include <QMainWindow>
    #include "DLView.h"

    #define MAX_RECENT_FILES 5

    class MainWindow : public QMainWindow {
        Q_OBJECT

        public:
            MainWindow(QWidget *parent = 0);
            ~MainWindow();

        private:
            void createMenus();
            void updateRecentFileActions();
            void onOpenAction(bool appendToList);

            void openFile(const QString &filePath, bool appendToList);
            void setOpenedFile(const QString &filePath);

            void closeEvent(QCloseEvent *event);

        private slots:
            // File Menu
            void onNewListAction();
            void onOpenNewListAction();
            void onAppendToListAction();
            void onSaveListAction();
            void onSaveListAsAction();
            void onOpenRecentFileAction();

            // Help Menu
            void onDLHelpAction();
            void onAboutAppAction();

        private:
            // Central widget
            DLView *dlView;

            QAction *saveListAct;
            QAction *recentFilesSep;
            QAction *recentFileActs[MAX_RECENT_FILES];

            // Remember most recently opened file
            QString openedFile;
    };
#endif // MAINWINDOW_H
