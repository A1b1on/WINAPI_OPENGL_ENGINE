#pragma once
#include "AbstractWindow.h"
namespace alb {
    class ExplorerElement : public AbstractWindow
    {
    public:
        ExplorerElement() { }

        std::string Text_place();

    private:
        std::string text_place = NULL;
        HWND label = NULL;
        HWND button = NULL;
        HBITMAP button_icon = NULL;
    };
}

