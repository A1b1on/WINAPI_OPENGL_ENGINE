#pragma once
#include "AbstractWindow.h"
#include "AbstractLabel.h"
namespace alb {
    class ExplorerWindow : public AbstractWindow
    {
    public:
        ExplorerWindow();
        ExplorerWindow(HINSTANCE hInstance, HWND parent_window, std::uint16_t w, std::uint16_t h, std::uint16_t x, std::uint16_t y);
        
       

        BOOL Destroy_Explorer();
        BOOL Create_Explorer();

        BOOL Change_size(UINT w, UINT h) override;
    private:
        alb::AbstractLabel* directory_label = NULL;
        std::string current_directory = "";
    };
    
}

