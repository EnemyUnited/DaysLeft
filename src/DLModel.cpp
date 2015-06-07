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

#include "DLModel.h"
#include "constants.h"

#include <QDebug>
#include <QSize>
#include <QFile>
#include <QDomDocument>

DLModel::DLModel(QObject *parent) : QAbstractTableModel(parent) {
    eventList = new QList<DLEvent>();
}

DLModel::~DLModel() {
    eventList->clear();
    delete eventList;
}

void DLModel::clearList() {
    beginResetModel();
    eventList->clear();
    endResetModel();
}

// Returns 1 more than the number of events in the list.
// The last row of the table allows the user to enter a new event.
int DLModel::rowCount(const QModelIndex &/*parent*/) const {
    return eventList->size()+1;
}

int DLModel::columnCount(const QModelIndex &/*parent*/) const {
    return 3;
}

QVariant DLModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // Display the column names in the table header row
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0:
                return QString("Event Name");
            case 1:
                return QString("Date");
            case 2:
                return QString("Days Left");
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

// Inserting a new event or editing an existing one in the model
bool DLModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::EditRole) {
        int row = index.row(), col = index.column();

        // Inserting a new event, by editing the name or date column
        if (row == eventList->size()) {
            beginInsertRows(index.parent(), row+1, row+1);
            if (col == 0)
                eventList->append(DLEvent(value.toString(), QDate::currentDate()));
            else if (col == 1)
                eventList->append(DLEvent("Name", value.toDate()));
            endInsertRows();
        }
        // Editing an existing event by editing its name or date
        else {
            if (col == 0) {
                const QString eventName = value.toString();
                (*eventList)[row].setName(eventName);
            }
            else if (col == 1) {
                const QDate date = value.toDate();
                (*eventList)[row].setDate(date);
            }
        }
        return true;
    }
    return false;
}

// Retrieving events from the model, used to render data in the table
QVariant DLModel::data(const QModelIndex &index, int role) const {
    int row = index.row(), col = index.column();
    bool lastRow = row == eventList->size();

    if (role == Qt::DisplayRole) {
        if (lastRow) {
            if (col == 0) return QString("Add Name");
            else if (col == 1) return QString("Add Date");
            else return QString();
        }
        else {
            DLEvent dlEvent = eventList->at(row);
            if (col == 0) return dlEvent.getName();
            else if (col == 1) return dlEvent.getDate().toString();
            else if (col == 2) return dlEvent.getDaysLeft();
        }
    }
    else if (role == Qt::TextAlignmentRole) {
        if (lastRow) return Qt::AlignCenter;
        else {
            if (col == 0) return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
            else return Qt::AlignCenter;
        }
    }
    else if (role == Qt::EditRole) {
        if (lastRow) {
            if (col == 0) return QString();
            else if (col == 1) return QDate::currentDate();
        }
        else {
            if (col == 0) return eventList->at(row).getName();
            else if (col == 1) return eventList->at(row).getDate();
        }
    }

    return QVariant();
}

// Insert multiple events to model
bool DLModel::insertRows(int row, int count, const QModelIndex &parent) {
    // always insert before last row of table
    if (row == eventList->size()+1)
        row--;

    beginInsertRows(parent, row, row+count-1);
    for (int i=0; i<count; i++)
        eventList->insert(row, DLEvent());
    endInsertRows();

    return true;
}

// Remove multiple events from model
bool DLModel::removeRows(int row, int count, const QModelIndex &parent) {
    // don't delete the last row
    if (row+count-1 == eventList->size())
        count--;

    if (count > 0) {
        beginRemoveRows(parent, row, row+count-1);

        for (int i=0; i<count; i++)
            if (row < eventList->size())
                eventList->removeAt(row);

        endRemoveRows();
    }
    return true;
}

// Sort the event list by name, date, or days left
void DLModel::sort(int column, Qt::SortOrder order) {
    beginResetModel();
    if (column == 0) { // sort by name
        if (order == Qt::AscendingOrder)
            std::sort(eventList->begin(), eventList->end(), DLEvent::cmpNameAscending);
        else
            std::sort(eventList->begin(), eventList->end(), DLEvent::cmpNameDescending);
    }
    else if (column == 1) { // sort by date
        if (order == Qt::AscendingOrder)
            std::sort(eventList->begin(), eventList->end(), DLEvent::cmpDateAscending);
        else
            std::sort(eventList->begin(), eventList->end(), DLEvent::cmpDateDescending);
    }
    else if (column == 2) { // sort by days left
        if (order == Qt::AscendingOrder)
            std::sort(eventList->begin(), eventList->end(), DLEvent::cmpDaysLeftAscending);
        else
            std::sort(eventList->begin(), eventList->end(), DLEvent::cmpDaysLeftDescending);
    }
    endResetModel();
}

// Define table cell properties. The 'Days Left' is not editable.
// Allow drag and drop (to enable reordering of events).
Qt::ItemFlags DLModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags defaultFlags = QAbstractTableModel::flags(index);
    if (index.column() != 2) defaultFlags |= Qt::ItemIsEditable;

    if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
     else
         return Qt::ItemIsDropEnabled | defaultFlags;
}

Qt::DropActions DLModel::supportedDragActions() const {
    return Qt::MoveAction;
}

QStringList DLModel::mimeTypes() const {
    QStringList types;
    types << "application/vnd.text.list";
    return types;
}

QMimeData *DLModel::mimeData(const QModelIndexList &indexes) const {
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }

    mimeData->setData("application/vnd.text.list", encodedData);
    return mimeData;
}

bool DLModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int /*column*/, const QModelIndex &parent) {
    qDebug() << "Action: " << action;
    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("application/vnd.text.list"))
            return false;

    int beginRow;
    if (row != -1)
        beginRow = row;
    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());

    QByteArray encodedData = data->data("application/vnd.text.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList newItems;

    int rows = 0;
    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        newItems << text;
        rows++;
    }

    insertRows(beginRow, rows, QModelIndex());
    foreach (const QString &text, newItems) {
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx, text);
        beginRow++;
    }

    return true;
}

// Populate event list with contents from an XML file
bool DLModel::readEventsFromFile(const QString &filePath, bool appendToList) {
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly))
        return false;

    QDomDocument doc("DaysLeft");
    bool success = doc.setContent(&file);
    file.close();

    if (!success) return false;

    beginResetModel();
    if (!appendToList)
        eventList->clear();

    QDomElement docElem = doc.documentElement();
    QDomNode node = docElem.firstChild();

    while (!node.isNull()) {
        docElem = node.toElement();
        if (!docElem.isNull()) {
            eventList->append(DLEvent(docElem.attribute("name"),
                                      QDate(docElem.attribute("year").toInt(),
                                            docElem.attribute("month").toInt(),
                                            docElem.attribute("day").toInt())));
        }
        node = node.nextSibling();
    }
    endResetModel();

    return true;
}

// Write current event list to an XML file
bool DLModel::writeEventsToFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
        return false;

    QDomDocument doc;
    QDomElement root = doc.createElement("DaysLeft");
    root.setAttribute("version", APPVERSTR);
    doc.appendChild(root);

    foreach (DLEvent dlEvent, *eventList) {
        QDate date = dlEvent.getDate();
        QDomElement docElem = doc.createElement("event");

        docElem.setAttribute("name", dlEvent.getName());
        docElem.setAttribute("month", date.month());
        docElem.setAttribute("day", date.day());
        docElem.setAttribute("year", date.year());

        root.appendChild(docElem);
    }

    QTextStream out(&file);
    doc.save(out, 2);
    file.close();

    return true;
}
