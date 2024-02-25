#include <iostream>
#include <array>
#include <windows.h>
using namespace std;

#define WHITE = 0x00FFFFFF

COLORREF get_pixel_color(int x, int y)
{
    HDC hdc = GetDC(NULL);
    COLORREF color = GetPixel(hdc, x, y);
    ReleaseDC(NULL, hdc);
    return color;
}

void get_cursor_pos(int& x, int& y)
{
    POINT cursor_pos;
    GetCursorPos(&cursor_pos);
    x = cursor_pos.x;
    y = cursor_pos.y;
}

int main()
{
    int x, y;
    int itr = 0;
    while (true)
    {
        itr++;
        get_cursor_pos(x, y);
        std::cout << x << " " << y << std::endl;
        if (itr > 30000)
        {
            break;
        }
    }
    return 0;
}