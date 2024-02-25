#include <iostream>
#include <array>
#include <windows.h>
using namespace std;

#define WHITE {255, 255, 255}

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

std::array<int, 3> color_to_array(COLORREF color)
{
    int rgb1 = GetRValue(color);
    int rgb2 = GetRValue(color);
    int rgb3 = GetRValue(color);
    std::array<int, 3> rgb_return = {rgb1, rgb2, rgb3};
    return rgb_return;
}

bool copeare_colors(const std::array<int, 3>& color1, const std::array<int, 3>& color2, int tolerance)
{
    return (abs(color1[0] - color2[0]) <= tolerance &&
            abs(color1[1] - color2[1]) <= tolerance &&
            abs(color1[2] - color2[2]) <= tolerance);
}

void click()
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0 ,0 ,0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0 ,0 ,0);
}

int main()
{
    int x, y;
    int itr = 0;
    while (true)
    {
        itr++;
        get_cursor_pos(x, y);
        std::cout << x << " " << y << std::ends;
        COLORREF color = get_pixel_color(x, y);
        std::cout << " " << color << std::ends;
        std::array<int, 3> color_rgb = color_to_array(color);
        for (int i = 0; i < 3; i++)
        {
            std::cout << " " << color_rgb[i] << std::ends;
        }

        bool res = copeare_colors(color_rgb, WHITE, 20);
        std::cout << " " << res << std::ends;


        std::cout << " " << std::endl;
        if (itr > 300)
        {
            break;
        }
    }
    return 0;
}