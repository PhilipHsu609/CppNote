#include <iostream>
#include <memory>

/*
    PImpl (Pointer to Implementation) idiom is a technique used in C++ to
    reduce compile-time dependencies between the implementation and the
    interface of a class. This idiom
    - reduces compile-time dependencies
    - hides implementation details from the user of the class
    - allows the implementation details to change without affecting the user of
    the class
*/

// Widget class with a pImpl. This is a common idiom in C++ to hide the
// implementation details of a class from the user of the class.
template <typename Impl>
class Widget {
  public:
    Widget();
    ~Widget();
    void draw();

  private:
    std::unique_ptr<Impl> pImpl;
};

// Widget's implementation details. This class is only visible to the Widget
// class and not to the user of the Widget class.
//
// The advantage of this approach is that the user of the Widget class does not
// need to know about the implementation details of the Widget class. This
// allows the implementation details to change without affecting the user of the
// Widget class. Also, the compilation time is reduced because the user of the
// Widget class does not need to include the header file for the Impl class.
class DefaultImpl {
  public:
    void draw() { std::cout << "Drawing Widget" << std::endl; }
};

class FancyImpl {
  public:
    void draw() { std::cout << "Drawing Fancy Widget" << std::endl; }
};

template <typename Impl>
Widget<Impl>::Widget() : pImpl(std::make_unique<Impl>()) {}

template <typename Impl>
Widget<Impl>::~Widget() = default;

template <typename Impl>
void Widget<Impl>::draw() {
    pImpl->draw();
}

int main() {
    Widget<DefaultImpl> widget;
    widget.draw();

    Widget<FancyImpl> fancyWidget;
    fancyWidget.draw();
    return 0;
}
