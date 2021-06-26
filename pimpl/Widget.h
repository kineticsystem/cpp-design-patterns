#ifndef WIDGET_H
#define WIDGET_H

#include <memory>
#include <iostream>

namespace DPointer {

    class Widget
    {
    public:
        Widget();
        virtual ~Widget();
        void test();

     protected:
        class WidgetPrivate;
        Widget(WidgetPrivate &widget);

        // To reduce the amount of memory allocation, only the base class Widget
        // contains a pointer to its private implementation.
        std::unique_ptr<WidgetPrivate> d_ptr;
    };


    /* /////////////////////////////////////////////////////////////////////////
     * Examples.
     */
    struct WidgetTest {
        static void execute() {

            std::cout << "PIMPL IDIOM" << std::endl;

            Widget widget;
            widget.test();

            std::cout << std::endl;
        }
    };
}

#endif // WIDGET_H
