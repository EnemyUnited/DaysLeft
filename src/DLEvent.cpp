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

#include "DLEvent.h"

DLEvent::DLEvent() {
	name = "Name";
	date = QDate::currentDate();
}

DLEvent::DLEvent(const QString &name, const QDate &date) {
	this->name = name;
	this->date = date;
}

QString DLEvent::getName() const {
	return name;
}

QDate DLEvent::getDate() const {
	return date;
}

void DLEvent::setName(const QString &newName) {
	name = newName;
}

void DLEvent::setDate(const QDate &newDate) {
	date = newDate;
}

int DLEvent::getDaysLeft() const {
	return QDate::currentDate().daysTo(date);
}

bool DLEvent::cmpNameAscending(const DLEvent &event1, const DLEvent &event2) {
	return event1.getName() < event2.getName();
}

bool DLEvent::cmpNameDescending(const DLEvent &event1, const DLEvent &event2) {
	return event1.getName() > event2.getName();
}

bool DLEvent::cmpDateAscending(const DLEvent &event1, const DLEvent &event2) {
	return event1.getDate() < event2.getDate();
}

bool DLEvent::cmpDateDescending(const DLEvent &event1, const DLEvent &event2) {
	return event1.getDate() > event2.getDate();
}

bool DLEvent::cmpDaysLeftAscending(const DLEvent &event1, const DLEvent &event2) {
	return event1.getDaysLeft() < event2.getDaysLeft();
}

bool DLEvent::cmpDaysLeftDescending(const DLEvent &event1, const DLEvent &event2) {
	return event1.getDaysLeft() > event2.getDaysLeft();
}
