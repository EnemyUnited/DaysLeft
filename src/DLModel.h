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

#ifndef DLMODEL_H
	#define DLMODEL_H

	#include "DLEvent.h"
	#include <QAbstractTableModel>
	#include <QList>
	#include <QMimeData>

	class DLModel : public QAbstractTableModel {
		Q_OBJECT

		public:
			DLModel(QObject *parent = 0);
			~DLModel();

			void clearList();

			int rowCount(const QModelIndex &parent) const;
			int columnCount(const QModelIndex &parent) const;

			QVariant headerData(int section, Qt::Orientation orientation, int role) const;

			bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
			QVariant data(const QModelIndex &index, int role) const;

			bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
			bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

			void sort(int column, Qt::SortOrder order);

			Qt::ItemFlags flags(const QModelIndex &index) const;
			Qt::DropActions supportedDragActions() const;

			QStringList mimeTypes() const;
			QMimeData *mimeData(const QModelIndexList &indexes) const;
			bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

			bool readEventsFromFile(QString &filePath, bool appendToList = true);
			bool writeEventsToFile(QString &filePath);

		private:
			QList<DLEvent> *eventList;
	};
#endif // DLMODEL_H
