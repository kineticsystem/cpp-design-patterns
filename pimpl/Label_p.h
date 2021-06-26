#ifndef LABEL_P_H
#define LABEL_P_H

#include "Label.h"
#include "Widget_p.h"

namespace DPointer {

    class Label::LabelPrivate : public Widget::WidgetPrivate
    {
    public:
        LabelPrivate(Label *Label);
        ~LabelPrivate();
        void test();

    private:
        Label *q_ptr; // Useful if LabelPrivate wants to access methods of Label.
    };
}

#endif // LABEL_P_H
