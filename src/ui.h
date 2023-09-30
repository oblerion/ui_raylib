#ifndef UI_H
#define UI_H
#include "raylib.h"
#include "kbd_layout.h"
#include "math.h"
#include <string.h>
struct UI_BUTTON
{
    int x;
    int y;
    int width;
    int height;
    int size_font;
    char name[30];
    Color color;

    bool visible;
};
struct UI_BUTTON UI_BUTTON(int x,int y,char* name,int size_font,Color color);
bool UI_BUTTON_draw(struct UI_BUTTON* uibutton);

struct UI_TEXT_FIELD
{
    int x;
    int y;
    int width;
    int height;
    int size_font;
    char text[50];
    Color color;

    bool visible;
};
struct UI_TEXT_FIELD UI_TEXT_FIELD(int x,int y,char* text,int size_font,Color color);
void UI_TEXT_FIELD_draw(struct UI_TEXT_FIELD* uitextfield);

struct UI_TEXT_INPUT
{
    int x;
    int y;
    int width;
    int height;
    int pos_cursor;
    int size_font;
    char text[30];
    Color color;

    bool visible;
    bool active;
};
struct UI_TEXT_INPUT UI_TEXT_INPUT(int x,int y,char* text,int size_font,Color color);
void UI_TEXT_INPUT_draw(struct UI_TEXT_INPUT* uitextinput,KBD_Layout layout);

struct UI_FILE_MANAGER
{
    int x;
    int y;
    int width;
    int height;
    Color color;

    struct UI_TEXT_INPUT uipath;
    struct UI_TEXT_FIELD uitext_input;
    struct UI_BUTTON uibtn_icon_quit;
    struct UI_BUTTON uibtn_icon_back;
    struct UI_BUTTON uibtn_back;
    struct UI_BUTTON uibtn_enter;
    struct UI_TEXT_INPUT uitextinput;
    
    bool visible;
};
struct UI_FILE_MANAGER UI_FILE_MANAGER(int x,int y,Color color);
void UI_FILE_MANAGER_draw(struct UI_FILE_MANAGER* uifilemanager);
#endif