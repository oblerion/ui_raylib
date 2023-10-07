#ifndef UI_H
#define UI_H
#include <stdio.h>
#include "raylib.h"
#include "kbd_layout.h"
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
    bool outline;
    bool visible;
};
struct UI_BUTTON UI_BUTTON(int x,int y,const char* name,int size_font,Color color);
bool UI_BUTTON_draw(struct UI_BUTTON* uibutton);

struct UI_TEXTFIELD
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
struct UI_TEXTFIELD UI_TEXTFIELD(int x,int y,char* text,int size_font,Color color);
void UI_TEXTFIELD_draw(struct UI_TEXTFIELD* uitextfield);

#define UI_TEXTZONE_MAXCAR 35
struct UI_TEXTZONE
{
    int x;
    int y;
    int width;
    int height;
    int size_font;
    char* text;
    Color color;
    bool visible;
};
struct UI_TEXTZONE UI_TEXTZONE(int x,int y,int size_font,Color color);
void UI_TEXTZONE_cpy(struct UI_TEXTZONE* textzone,char* text);
void UI_TEXTZONE_cat(struct UI_TEXTZONE* textzone,char* text);
void UI_TEXTZONE_draw(struct UI_TEXTZONE* textzone);

struct UI_TEXTINPUT
{
    int x;
    int y;
    int width;
    int height;
    int pos_cursor;
    int size_font;
    char text[50];
    Color color;

    bool visible;
    bool active;
};
struct UI_TEXTINPUT UI_TEXTINPUT(int x,int y,char* text,int size_font,Color color);
void UI_TEXTINPUT_draw(struct UI_TEXTINPUT* uitextinput,KBD_Layout layout);

struct UI_SLIDEBAR_V
{
    int x;
    int y;
    int size_cursor;
    int nb_pos_max;
    int pos;
    Color color;
    bool visible;
};
struct UI_SLIDEBAR_V UI_SLIDEBAR_V(int x,int y,int pos_max);
void UI_SLIDEBAR_V_resize(struct UI_SLIDEBAR_V* bar, int pos_max);
bool UI_SLIDEBAR_V_draw(struct UI_SLIDEBAR_V* bar);

#define UI_EXPLORER_MAX_FILE 18
#ifdef __linux__
    #define UI_EXPLORER_START_PATH "/home"
#elif _WIN32
    #define UI_EXPLORER_START_PATH "C:/"
#endif
struct UI_EXPLORER
{
    int x;
    int y;
    bool visible;
    Color color;
    struct UI_TEXTZONE path;
    struct UI_TEXTFIELD text_path;
    struct UI_SLIDEBAR_V barv;
    struct UI_BUTTON files[UI_EXPLORER_MAX_FILE];
    struct UI_BUTTON uibtn_icon_back;
};
struct UI_EXPLORER UI_EXPLORER(int x,int y,Color color);
void UI_EXPLORER_draw(struct UI_EXPLORER* uiexp);

struct UI_FILEIO
{
    int x;
    int y;
    int width;
    int height;
    Color color;

    struct UI_EXPLORER uiexplorer;
    struct UI_BUTTON uibtn_icon_quit;
  
    struct UI_BUTTON uibtn_back;
    struct UI_BUTTON uibtn_enter;
    struct UI_TEXTFIELD uitext_filename;
    struct UI_TEXTINPUT uiinput_filename;

    char* io_path;
    bool visible;
};
struct UI_FILEIO UI_FILEIO(int x,int y,Color color);
void UI_FILEIO_draw(struct UI_FILEIO* uifilemanager);
#endif