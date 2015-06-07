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

#ifndef DLVIEW_H
	#define DLVIEW_H

	#include "DLModel.h"
	#include "DLDelegate.h"

	#include <QTableView>
	#include <QKeyEvent>

	class DLView : public QTableView {
		Q_OBJECT

		public:
			DLView(QWidget *parent = 0);
			~DLView();

			DLModel *getModel() const;

			void keyReleaseEvent(QKeyEvent *event);

		private:
			DLModel *dlModel;
			DLDelegate *dlDelegate;

	};
#endif // DLVIEW_H
