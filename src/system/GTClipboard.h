/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef _HI_GT_CLIPBOARD_H_
#define _HI_GT_CLIPBOARD_H_

#include "GTGlobals.h"

namespace HI {

class HI_EXPORT GTClipboard {
public:
    // fails if can't get clipboard or clipboard doesn't contain text data
    static QString text(GUITestOpStatus &os);

    static void setText(GUITestOpStatus &os, QString text);

    static void setUrls(GUITestOpStatus &os, const QList<QString>& urls);

    static void clear(GUITestOpStatus &os);
};

} //namespace

#endif