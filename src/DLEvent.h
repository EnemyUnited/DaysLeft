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

#ifndef DLEVENT_H
	#define DLEVENT_H

	#include <QString>
	#include <QDate>

    // Defines a single 'Days Left' event
	class DLEvent {
		public:
			DLEvent();
			DLEvent(const QString &name, const QDate &date);

			QString getName() const;
			QDate getDate() const;

			void setName(const QString &newName);
			void setDate(const QDate &newDate);

			int getDaysLeft() const;

            // Comparator methods needed for sorting a list of events
			static bool cmpNameAscending(const DLEvent &event1, const DLEvent &event2);
			static bool cmpNameDescending(const DLEvent &event1, const DLEvent &event2);

			static bool cmpDateAscending(const DLEvent &event1, const DLEvent &event2);
			static bool cmpDateDescending(const DLEvent &event1, const DLEvent &event2);

			static bool cmpDaysLeftAscending(const DLEvent &event1, const DLEvent &event2);
			static bool cmpDaysLeftDescending(const DLEvent &event1, const DLEvent &event2);

		private:
            QString name; // event name
            QDate date;   // when the event occurs
	};
#endif // DLEVENT_H
