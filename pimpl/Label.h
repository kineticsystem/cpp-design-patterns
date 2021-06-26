#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"

#include <memory>
#include <iostream>
#include <QString>

namespace DPointer {

    class Label : public Widget
    {
    public:
        Label();
        virtual ~Label();
        void test();

    protected:
        class LabelPrivate;
        Label(LabelPrivate &label);

    private:
        const QString name = "Label";
    };

    /* ////////////////////////////////////////////////////////////////////////////
     * Examples.
     */
    struct Test {
        static void execute() {

            std::cout << "PIMPL IDIOM" << std::endl;

            Label label;
            label.test();

            Widget widget;
            widget.test();

            std::cout << std::endl;
        }
    };
}

#endif // LABEL_H
