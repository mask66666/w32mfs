#include <iostream>
#include <array>
#include <windows.h>
#include <thread>
#include <chrono>
using namespace std;

#define WHITE {255, 255, 255}
#define BAR_X 1729 // normal: 1491 left half: 1729
#define BAR_Y 239 // normal: 237 left half: 239

void sleep(int miliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
}

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
    int rgb2 = GetBValue(color);
    int rgb3 = GetBValue(color);
    std::array<int, 3> rgb_return = {rgb1, rgb2, rgb3};
    return rgb_return;
}

bool compeare_colors(const std::array<int, 3>& color1, const std::array<int, 3>& color2, int tolerance)
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

void fish()
{
    sleep(750);
    click();
    int x, y;
    get_cursor_pos(x, y);
    COLORREF color = get_pixel_color(x + 1, y - 2);
    std::array color_rgb = color_to_array(color);
    bool res = compeare_colors(color_rgb, WHITE, 30);
    while (!res)
    {
        get_cursor_pos(x, y);
        color = get_pixel_color(x, y);
        color_rgb = color_to_array(color);
        res = compeare_colors(color_rgb, WHITE, 30);
    }
    sleep(100);
    click();
}

void click_to_fill_bar()
{
    COLORREF color = get_pixel_color(BAR_X, BAR_Y);
    std::array color_rgb = color_to_array(color);
    bool res = compeare_colors(color_rgb, WHITE, 30);
    while (res)
    {
        color = get_pixel_color(BAR_X, BAR_Y);
        color_rgb = color_to_array(color);
        res = compeare_colors(color_rgb, WHITE, 30);
        click();
        sleep(50);
    }
}

int main()
{
    int sucess = 0;
    int fail = 0;
    sleep(3000);
    while (true)
    {
        fish();
        sleep(500);
        // stats
        COLORREF color = get_pixel_color(BAR_X, BAR_Y);
        std::array color_rgb = color_to_array(color);
        if (compeare_colors(color_rgb, WHITE, 30))
        {
            sucess++;
        } else
        {
            fail++;
        }
        std::cout << "sucesses: " << sucess << ", fails: " << fail << std::endl;
        click_to_fill_bar();
        sleep(200);
    }
    return 0;
}