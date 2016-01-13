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

#include "drivers/GTKeyboardDriver.h"
#include "drivers/GTMouseDriver.h"
#include "primitives/GTScrollBar.h"
#include "primitives/GTWidget.h"

namespace HI {
#define GT_CLASS_NAME "GTScrollBar"

#define GT_METHOD_NAME "getScrollBar"
QScrollBar* GTScrollBar::getScrollBar(GUITestOpStatus &os, const QString &scrollBarSysName) {
    QString scrollBarTypeCheck = "QScrollBar";
    QScrollBar *scrollBar = static_cast<QScrollBar*>(GTWidget::findWidget(os, scrollBarSysName));
    GT_CHECK_RESULT(0 == scrollBarTypeCheck.compare(scrollBar->metaObject()->className()), "No such scrollbar: " + scrollBarSysName, NULL); //the found widget is not a qscrollbar
    return scrollBar;
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "pageUp"
void GTScrollBar::pageUp(GUITestOpStatus &os, QScrollBar *scrollbar, GTGlobals::UseMethod useMethod) {
    GT_CHECK(scrollbar != NULL, "scrollbar is NULL");
    switch (useMethod) {
        case GTGlobals::UseMouse:
            GTMouseDriver::moveTo(os, GTScrollBar::getAreaOverSliderPosition(os, scrollbar));
            GTMouseDriver::click(os);
            break;

        case GTGlobals::UseKey:
            GTMouseDriver::moveTo(os, GTScrollBar::getSliderPosition(os, scrollbar));
            GTMouseDriver::click(os);
            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["pageUp"]);
            break;

        default:
            break;
    }
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "pageDown"
void GTScrollBar::pageDown(GUITestOpStatus &os, QScrollBar *scrollbar, GTGlobals::UseMethod useMethod) {
    GT_CHECK(scrollbar != NULL, "scrollbar is NULL");
    switch (useMethod) {
        case GTGlobals::UseMouse:
            GTMouseDriver::moveTo(os, GTScrollBar::getAreaUnderSliderPosition(os, scrollbar));
            GTMouseDriver::click(os);
            break;

        case GTGlobals::UseKey:
            GTMouseDriver::moveTo(os, GTScrollBar::getSliderPosition(os, scrollbar));
            GTMouseDriver::click(os);
            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["pageDown"]);
            break;

        default:
            break;
    }
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "lineUp"
void GTScrollBar::lineUp(GUITestOpStatus &os, QScrollBar *scrollbar, GTGlobals::UseMethod useMethod) {
    GT_CHECK(scrollbar != NULL, "scrollbar is NULL");
    switch (useMethod) {
        case GTGlobals::UseMouse:
            GTMouseDriver::moveTo(os, GTScrollBar::getUpArrowPosition(os, scrollbar));
            GTMouseDriver::click(os);
            break;

        case GTGlobals::UseKey:
            GTMouseDriver::moveTo(os, GTScrollBar::getSliderPosition(os, scrollbar));
            GTMouseDriver::click(os);
            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["up"]);
            break;

        default:
            break;
    }
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "lineDown"
void GTScrollBar::lineDown(GUITestOpStatus &os, QScrollBar *scrollbar, GTGlobals::UseMethod useMethod) {
    GT_CHECK(scrollbar != NULL, "scrollbar is NULL");
    switch (useMethod) {
        case GTGlobals::UseMouse:
            GTMouseDriver::moveTo(os, GTScrollBar::getDownArrowPosition(os, scrollbar));
            GTMouseDriver::click(os);
            break;

        case GTGlobals::UseKey:
            GTMouseDriver::moveTo(os, GTScrollBar::getSliderPosition(os, scrollbar));
            GTMouseDriver::click(os);
            GTKeyboardDriver::keyClick(os, GTKeyboardDriver::key["down"]);
            break;

        default:
            break;
    }
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "moveSliderWithMouseUp"
void GTScrollBar::moveSliderWithMouseUp(GUITestOpStatus &os, QScrollBar *scrollbar, int nPix) {
    GT_CHECK(scrollbar != NULL, "scrollbar is NULL");
    GTMouseDriver::moveTo(os, GTScrollBar::getSliderPosition(os, scrollbar));
    QPoint newPosition;
    if (Qt::Horizontal == scrollbar->orientation()) {
        newPosition = QPoint(QCursor::pos().x() + nPix, QCursor::pos().y());
    }
    else {
        newPosition = QPoint(QCursor::pos().x(), QCursor::pos().y() + nPix);
    }
    GTMouseDriver::press(os);
    GTMouseDriver::moveTo(os, newPosition);
    GTMouseDriver::release(os);
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "moveSliderWithMouseDown"
void GTScrollBar::moveSliderWithMouseDown(GUITestOpStatus &os, QScrollBar *scrollbar, int nPix) {
    GT_CHECK(scrollbar != NULL, "scrollbar is NULL");
    GTMouseDriver::moveTo(os, GTScrollBar::getSliderPosition(os, scrollbar));
    GTMouseDriver::press(os);
    QPoint newPosition;
    if (Qt::Horizontal == scrollbar->orientation()) {
        newPosition = QPoint(QCursor::pos().x() - nPix , QCursor::pos().y());
    }
    else {
        newPosition = QPoint(QCursor::pos().x(), QCursor::pos().y() - nPix);
    }
    GTMouseDriver::moveTo(os, newPosition);
    GTMouseDriver::release(os);
}
#undef GT_METHOD_NAME

void GTScrollBar::moveSliderWithMouseWheelUp(GUITestOpStatus &os, QScrollBar *scrollbar, int nScrolls) {
    GTMouseDriver::moveTo(os, GTScrollBar::getSliderPosition(os, scrollbar));
    GTMouseDriver::click(os);
    GTMouseDriver::scroll(os, nScrolls);
}

void GTScrollBar::moveSliderWithMouseWheelDown(GUITestOpStatus &os, QScrollBar *scrollbar, int nScrolls) {
    GTMouseDriver::moveTo(os, GTScrollBar::getSliderPosition(os, scrollbar));
    GTMouseDriver::click(os);
    GTMouseDriver::scroll(os, (-1 * nScrolls)); //since scrolling down means negative value for GTMouseDriver::scroll
}

#define GT_METHOD_NAME "getSliderPosition"
QPoint GTScrollBar::getSliderPosition(GUITestOpStatus &os, QScrollBar *scrollbar) {
    GT_CHECK_RESULT(scrollbar != NULL, "scrollbar is NULL", QPoint());
    QStyleOptionSlider options = initScrollbarOptions(os, scrollbar);
    QRect sliderRect = scrollbar->style()->subControlRect(QStyle::CC_ScrollBar, &options, QStyle::SC_ScrollBarSlider);
    return scrollbar->mapToGlobal(sliderRect.center());
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "getUpArrowPosition"
QPoint GTScrollBar::getUpArrowPosition(GUITestOpStatus &os, QScrollBar *scrollbar) {
    GT_CHECK_RESULT(scrollbar != NULL, "scrollbar is NULL", QPoint());
    QStyleOptionSlider options = initScrollbarOptions(os, scrollbar);
    QRect grooveRect = scrollbar->style()->subControlRect(QStyle::CC_ScrollBar, &options, QStyle::SC_ScrollBarGroove);
    int upArrowWidth;
    int upArrowHeight;

    if (Qt::Horizontal == scrollbar->orientation()) {
        upArrowWidth = (scrollbar->rect().width() - grooveRect.width()) / 2;
        upArrowHeight = scrollbar->rect().height();
    }
    else {
        upArrowWidth = scrollbar->rect().width();
        upArrowHeight = scrollbar->rect().height() - grooveRect.height() / 2;
    }
    return scrollbar->mapToGlobal(scrollbar->rect().topLeft() + QPoint(upArrowWidth / 2, upArrowHeight / 2));
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "getDownArrowPosition"
QPoint GTScrollBar::getDownArrowPosition(GUITestOpStatus &os, QScrollBar *scrollbar) {
    GT_CHECK_RESULT(scrollbar != NULL, "scrollbar is NULL", QPoint());
    QStyleOptionSlider options = initScrollbarOptions(os, scrollbar);
    QRect grooveRect = scrollbar->style()->subControlRect(QStyle::CC_ScrollBar, &options, QStyle::SC_ScrollBarGroove);
    int downArrowWidth;
    int downArrowHeight;

    if (Qt::Horizontal == scrollbar->orientation()) {
        downArrowWidth = (scrollbar->rect().width() - grooveRect.width()) / 2;
        downArrowHeight = scrollbar->rect().height();
    }
    else {
        downArrowWidth = scrollbar->rect().width();
        downArrowHeight = scrollbar->rect().height() - grooveRect.height() / 2;
    }
    return scrollbar->mapToGlobal(scrollbar->rect().bottomRight() - QPoint(downArrowWidth / 2, downArrowHeight / 2));
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "getAreaUnderSliderPosition"
QPoint GTScrollBar::getAreaUnderSliderPosition(GUITestOpStatus &os, QScrollBar *scrollbar) {
    GT_CHECK_RESULT(scrollbar != NULL, "scrollbar is NULL", QPoint());
    QStyleOptionSlider options = initScrollbarOptions(os, scrollbar);
    QRect grooveRect = scrollbar->style()->subControlRect(QStyle::CC_ScrollBar, &options, QStyle::SC_ScrollBarGroove);
    QRect sliderRect = scrollbar->style()->subControlRect(QStyle::CC_ScrollBar, &options, QStyle::SC_ScrollBarSlider);
    QRect underSliderRect;

    if (Qt::Horizontal == scrollbar->orientation()) {
        int underSliderRectWidth = grooveRect.right() - sliderRect.right();
        int underSliderRectHeight = grooveRect.height();
        underSliderRect = QRect(sliderRect.topRight() + QPoint(1, 0), QSize(underSliderRectWidth, underSliderRectHeight));
    }
    else {
        int underSliderRectWidth = grooveRect.width();
        int underSliderRectHeight = grooveRect.bottom() - sliderRect.bottom();
        underSliderRect = QRect(sliderRect.topRight() + QPoint(1, 1), QSize(underSliderRectWidth, underSliderRectHeight));
    }

    if (underSliderRect.contains(scrollbar->mapFromGlobal(QCursor::pos()))) {
        return QCursor::pos();
    }
    return scrollbar->mapToGlobal(underSliderRect.center());
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "getAreaOverSliderPosition"
QPoint GTScrollBar::getAreaOverSliderPosition(GUITestOpStatus &os, QScrollBar *scrollbar) {
    GT_CHECK_RESULT(scrollbar != NULL, "scrollbar is NULL", QPoint());
    QStyleOptionSlider options = initScrollbarOptions(os, scrollbar);
    QRect grooveRect = scrollbar->style()->subControlRect(QStyle::CC_ScrollBar, &options, QStyle::SC_ScrollBarGroove);
    QRect sliderRect = scrollbar->style()->subControlRect(QStyle::CC_ScrollBar, &options, QStyle::SC_ScrollBarSlider);
    QRect overSliderRect;

    if (Qt::Horizontal == scrollbar->orientation()) {
        int overSliderRectWidth = sliderRect.left() - grooveRect.left();
        int overSliderRectHeight = grooveRect.height();
        overSliderRect = QRect(grooveRect.topLeft(), QSize(overSliderRectWidth, overSliderRectHeight));
    }
    else {
        int overSliderRectWidth = grooveRect.width();
        int overSliderRectHeight = sliderRect.top() - grooveRect.top();
        overSliderRect = QRect(grooveRect.topLeft(), QSize(overSliderRectWidth, overSliderRectHeight));
    }

    if (overSliderRect.contains(scrollbar->mapFromGlobal(QCursor::pos()))) {
        return QCursor::pos();
    }
    return scrollbar->mapToGlobal(overSliderRect.center() + QPoint(1,0));
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "initScrollbarOptions"
QStyleOptionSlider GTScrollBar::initScrollbarOptions(GUITestOpStatus &os, QScrollBar *scrollbar) {
    GT_CHECK_RESULT(scrollbar != NULL, "scrollbar is NULL", QStyleOptionSlider());
    QStyleOptionSlider options;
    options.initFrom(scrollbar);
    options.sliderPosition = scrollbar->sliderPosition();
    options.maximum = scrollbar->maximum();
    options.minimum = scrollbar->minimum();
    options.singleStep = scrollbar->singleStep();
    options.pageStep = scrollbar->pageStep();
    options.orientation = scrollbar->orientation();
    options.sliderValue = options.sliderPosition;
    options.upsideDown = false;
    options.state = QStyle::State_Sunken | QStyle::State_Enabled;

    return options;
}
#undef GT_METHOD_NAME

#undef GT_CLASS_NAME

}
// namespace
