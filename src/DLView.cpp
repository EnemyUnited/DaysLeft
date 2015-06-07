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

#include "DLView.h"
#include <QHeaderView>
#include <QDebug>

DLView::DLView(QWidget *parent) : QTableView(parent) {
	dlModel = new DLModel();
	setModel(dlModel);

	dlDelegate = new DLDelegate();
	setItemDelegate(dlDelegate);

	setEditTriggers(QAbstractItemView::DoubleClicked |
					QAbstractItemView::SelectedClicked);

	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setSelectionBehavior(QTableView::SelectRows);
	setSortingEnabled(true);
}

DLView::~DLView() {
	delete dlModel;
	delete dlDelegate;
}

DLModel *DLView::getModel() const {
	return dlModel;
}

void DLView::keyReleaseEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Delete) {
		QModelIndexList selectedRows = selectionModel()->selectedRows();
		if (selectedRows.size() > 0)
			dlModel->removeRows(selectedRows.first().row(),
								selectedRows.size(),
								selectedRows.first().parent());
	}
	event->accept();
}
