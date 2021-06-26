#include "Widget.h"
#include "Widget_p.h"

using namespace DPointer;

////////////////////////////////////////////////////////////////////////////////
/// \brief Widget::WidgetPrivate::WidgetPrivate
///

Widget::WidgetPrivate::WidgetPrivate(Widget *widget) : q_ptr{widget}
{
}

Widget::WidgetPrivate::~WidgetPrivate()
{
}

void Widget::WidgetPrivate::test()
{
    std::cout << "I am a " << q_ptr->name.toStdString() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Widget::Widget
///

Widget::Widget() : d_ptr{new WidgetPrivate{this}}
{
}

Widget::~Widget()
{
}

void Widget::test()
{
    d_ptr->test();
}

Widget::Widget(Widget::WidgetPrivate &widget) : d_ptr{&widget}
{
}
