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

#include "DLDelegate.h"
#include "DLModel.h"

#include <QLineEdit>
#include <QDateEdit>

DLDelegate::DLDelegate(QObject *parent) : QStyledItemDelegate(parent) {
}

// This is called when a table cell enters edit mode
QWidget *DLDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (index.column() == 0) {
        QLineEdit *lineEdit = new QLineEdit(parent);
        lineEdit->setFrame(false);
        return lineEdit;
    }
    else if (index.column() == 1) {
        QDateEdit *dateEdit = new QDateEdit(parent);
        dateEdit->setFrame(false);
        dateEdit->setCalendarPopup(true);
        return dateEdit;
    }
    else return QStyledItemDelegate::createEditor(parent, option, index);
}

// This is called to load data into the editor that it should show upon creation
void DLDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    const DLModel *dlModel = static_cast<const DLModel *>(index.model());

    if (index.column() == 0) {
        QString eventName = dlModel->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        lineEdit->setText(eventName);
    }
    else if (index.column() == 1) {
        QDate date = dlModel->data(index, Qt::EditRole).toDate();
        QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
        dateEdit->setDate(date);
    }
    else QStyledItemDelegate::setEditorData(editor, index);
}

// This is called to update the model's data after editing is done
void DLDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    DLModel *dlModel = static_cast<DLModel *>(model);

    if (index.column() == 0) {
        QLineEdit *lineEdit = static_cast<QLineEdit *>(editor);
        dlModel->setData(index, lineEdit->text(), Qt::EditRole);
    }
    else if (index.column() == 1) {
        QDateEdit *dateEdit = static_cast<QDateEdit *>(editor);
        dlModel->setData(index, dateEdit->date(), Qt::EditRole);
    }
    else QStyledItemDelegate::setModelData(editor, model, index);
}

// Where the editor widget gets drawn and its size
void DLDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const {
    editor->setGeometry(option.rect);
}
