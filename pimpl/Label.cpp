#include "Label.h"
#include "Label_p.h"

using namespace DPointer;

////////////////////////////////////////////////////////////////////////////////
/// \brief Widget::WidgetPrivate::WidgetPrivate
///
///
Label::LabelPrivate::LabelPrivate(Label *label) : WidgetPrivate{label},
    q_ptr{label}
{
}

Label::LabelPrivate::~LabelPrivate()
{
}

void Label::LabelPrivate::test()
{
    std::cout << "I am a " << q_ptr->name.toStdString() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Label::Label
///

Label::Label() : Widget{*new LabelPrivate{this}}
{
}

Label::~Label()
{
}

void Label::test()
{
    // Cast is required to invoke a method on LabelPrivate.
    static_cast<LabelPrivate *>(d_ptr.get())->test();
}

Label::Label(Label::LabelPrivate &label) : Widget{label}
{
}
