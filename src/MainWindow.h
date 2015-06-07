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

	class MainWindow : public QMainWindow {
		Q_OBJECT

		public:
			MainWindow(QWidget *parent = 0);
			~MainWindow();

		private:
			void createMenus();
			void closeEvent(QCloseEvent *event);
			void onOpenAction(bool appendToList);

            QAction *saveListAct;

            // Remember most recently opened file
            QString openedFile;

			// Widgets
			DLView *dlView;

		private slots:
			// File Menu
			void onOpenNewListAction();
			void onOpenAppendToListAction();
			void onSaveListAction();
			void onSaveListAsAction();

			// Help Menu
			void onDLHelpAction();
			void onAboutAppAction();
	};
#endif // MAINWINDOW_H
