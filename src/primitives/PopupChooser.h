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

#ifndef _HI_GT_RUNNABLES_POPUP_CHOOSER_FILLER_H_
#define _HI_GT_RUNNABLES_POPUP_CHOOSER_FILLER_H_

#include "GTGlobals.h"
#include "utils/GTUtilsDialog.h"

namespace HI {

class HI_EXPORT PopupChooser : public Filler {
        friend class PopupChecker;
        friend class PopupCheckerByText;
    public:
        PopupChooser(GUITestOpStatus &_os, const QStringList &_namePath, GTGlobals::UseMethod _useMethod = GTGlobals::UseKey) //UseKey need for Ubuntu
            :Filler(_os, GUIDialogWaiter::WaitSettings(QString(), GUIDialogWaiter::Popup)), namePath(_namePath), useMethod(_useMethod){}
        virtual void commonScenario();
    protected:
        QStringList namePath;
        GTGlobals::UseMethod useMethod;

    private:
        static void clickEsc(GUITestOpStatus &_os);
    };

class HI_EXPORT PopupChooserByText : public Filler {
    public:
        PopupChooserByText(GUITestOpStatus &_os, const QStringList &_namePath, GTGlobals::UseMethod _useMethod = GTGlobals::UseKey, Qt::MatchFlag _matchFlag = Qt::MatchExactly) //UseKey need for Ubuntu
            :Filler(_os, GUIDialogWaiter::WaitSettings(QString(), GUIDialogWaiter::Popup)), namePath(_namePath), useMethod(_useMethod), matchFlag(_matchFlag){}
        virtual void commonScenario();
    protected:
        QStringList namePath;
        GTGlobals::UseMethod useMethod;
        Qt::MatchFlag matchFlag;
    };

class HI_EXPORT PopupChecker : public Filler {
    public:
        enum CheckOption{
            NotExists = 0,
            Exists = 1,
            IsEnabled = 2 | Exists,
            IsDisabled = 4 | Exists,
            IsChecable = 8 | Exists,
            IsChecked = 16 | Exists | IsChecable
        };
        Q_DECLARE_FLAGS(CheckOptions, CheckOption)
        PopupChecker(GUITestOpStatus &os, CustomScenario *scenario);
        PopupChecker(GUITestOpStatus &_os, const QStringList &_namePath, CheckOptions _options = CheckOptions(IsEnabled),
                     GTGlobals::UseMethod _useMethod = GTGlobals::UseKey) //UseKey need for Ubuntu
            :Filler(_os, GUIDialogWaiter::WaitSettings(QString(), GUIDialogWaiter::Popup)), namePath(_namePath), options(_options), useMethod(_useMethod){}
        virtual void commonScenario();
    protected:
        QStringList namePath;
        CheckOptions options;
        GTGlobals::UseMethod useMethod;
    };
    Q_DECLARE_OPERATORS_FOR_FLAGS(PopupChecker::CheckOptions)

class HI_EXPORT PopupCheckerByText : public Filler {
    public:
        PopupCheckerByText(GUITestOpStatus &os, CustomScenario *scenario);
        PopupCheckerByText(GUITestOpStatus &os,
                           const QStringList &namePath,
                           PopupChecker::CheckOptions options = PopupChecker::CheckOptions(PopupChecker::IsEnabled),
                           GTGlobals::UseMethod useMethod = GTGlobals::UseKey);  //UseKey need for Ubuntu
        PopupCheckerByText(GUITestOpStatus &os, const QList<QStringList> &namePaths,
                           PopupChecker::CheckOptions _options = PopupChecker::CheckOptions(PopupChecker::IsEnabled),
                           GTGlobals::UseMethod useMethod = GTGlobals::UseKey);

        virtual void commonScenario();
    protected:
        QList<QStringList> textPaths;
        PopupChecker::CheckOptions options;
        GTGlobals::UseMethod useMethod;
    };
}

#endif
