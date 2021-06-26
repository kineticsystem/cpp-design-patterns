#ifndef WIDGET_P_H
#define WIDGET_P_H

#include "Widget.h"

namespace DPointer {

    class Widget::WidgetPrivate
    {
    public:
        WidgetPrivate(Widget *widget);
        ~WidgetPrivate();
        void test();

    private:
        Widget *q_ptr; // Useful if WidgetPrivate wants to access methods of Widget.
    };
}

#endif // WIDGET_P_H
