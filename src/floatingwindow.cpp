#include "floatingwindow.hpp"
#include <cstring>

using namespace PPLNAMESPACE;

FloatingWindow::FloatingWindow(int left, int top, int width, int height):
    width_2d_(width),
    height_2d_(height),
    visible_2d_(false)
    
{
    XPLMCreateWindow_t win;
    memset(&win, 0, sizeof(win));

    win.structSize = sizeof(win);
    win.left = left;
    win.top = top;
    win.right = left+width;
    win.bottom = top-height;
    win.visible = visible_2d_;
    win.drawWindowFunc = draw2dWindowCallback;
    //win.handleKeyFunc = handle2dKeyCallback;
    //win.handleMouseClickFunc = handle2dClickCallback;
    //win.handleCursorFunc = handle2dCursorCallback;
    //win.handleMouseWheelFunc = handle2dWheelCallback;
    win.refcon = this;
    window2d_id_ = XPLMCreateWindowEx(&win);
}


