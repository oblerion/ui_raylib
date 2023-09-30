#include "ui.h"
#include "math.h"

int MATH_collide(int x,int y,int w,int h,int x2,int y2,int w2,int h2)
{
	if(x+w>x2 && x<x2+w2 && y+h>y2 && y2+h2>y) return 1;
	return 0;
}

struct UI_BUTTON UI_BUTTON(int x, int y, char *name, int size_font, Color color)
{
    struct UI_BUTTON uibutton;
    uibutton.x = x;
    uibutton.y = y;
    strcpy(uibutton.name,name);
    uibutton.size_font = size_font;
    uibutton.color = color;
    uibutton.visible=true;

    uibutton.width = MeasureText(name,uibutton.size_font)+8;
    uibutton.height = size_font+4;
    return uibutton;
}


bool UI_BUTTON_draw(struct UI_BUTTON *uibutton)
{
    bool lbool = false;
    if(uibutton->visible)
    {
        Color lcol = uibutton->color;
        if(MATH_collide(GetMouseX(),GetMouseY(),10,10,
            uibutton->x-4,uibutton->y-2,uibutton->width,uibutton->height)==1)
        {
            lcol.a = 50;
            if(IsMouseButtonPressed(0)) lbool = true;
        }
        DrawRectangleLines(uibutton->x-4,uibutton->y-2,uibutton->width,uibutton->height,lcol);
        DrawText(uibutton->name,uibutton->x,uibutton->y,uibutton->size_font,lcol);
    }
    return lbool;
}

struct UI_TEXT_FIELD UI_TEXT_FIELD(int x, int y, char *text, int size_font, Color color)
{
    struct UI_TEXT_FIELD uitextf;
    uitextf.x = x;
    uitextf.y = y;
    strcpy(uitextf.text,text);
    uitextf.size_font=size_font;
    uitextf.color=color;
    uitextf.visible=true;

    uitextf.width = MeasureText(text,size_font)+8;
    uitextf.height = size_font+8;
    return uitextf;
}

void UI_TEXT_FIELD_draw(struct UI_TEXT_FIELD* uitextfield)
{
    if(uitextfield->visible)
    {
        DrawText(uitextfield->text,uitextfield->x,uitextfield->y,uitextfield->size_font,uitextfield->color);
    }
}

struct UI_TEXT_INPUT UI_TEXT_INPUT(int x, int y, char *text, int size_font, Color color)
{
    struct UI_TEXT_INPUT uitextinput={
        x,y,0,0,0,size_font,{0},color,true
    };
    strcpy(uitextinput.text,text);
    uitextinput.width = (MeasureText("mmmmmmmmmmmmmmmmmmmmmmmmm",size_font))+8;
    uitextinput.height = size_font+8;

    return uitextinput;
}

void UI_TEXT_INPUT_draw(struct UI_TEXT_INPUT *uitextinput,KBD_Layout layout)
{
    if(uitextinput->active)
    {
        int key = Kbd_GetKeyPressed(layout);
        if( key != KEY_LEFT_SHIFT &&
            key != KEY_RIGHT_SHIFT &&
            key != KEY_LEFT_ALT && 
            key != KEY_RIGHT_ALT &&
            key != KEY_LEFT_CONTROL && 
            key != KEY_RIGHT_CONTROL &&
            key != KEY_BACKSPACE &&
            key != 0)
        {
            if(strlen(uitextinput->text)<25)
                strcat(uitextinput->text,TextFormat("%c",key));
        }
        else if(key == KEY_BACKSPACE)
        {
            int size = strlen(uitextinput->text);
            if(size>0)
            {
                uitextinput->text[size-1] = '\0';
                uitextinput->text[size] = 0;
            }
        }
    }
    if(uitextinput->visible)
    {
        Color lcol = uitextinput->color;
        if(MATH_collide(GetMouseX(),GetMouseY(),10,10,
            uitextinput->x-4,uitextinput->y-4,uitextinput->width,uitextinput->height)==1)
        {
            lcol.a = 50;
            if(IsMouseButtonPressed(0)) uitextinput->active = !uitextinput->active;
        }
        else
        {
            if(IsMouseButtonPressed(0)) uitextinput->active=false;
        }
        DrawRectangleLines(uitextinput->x-4,uitextinput->y-4,uitextinput->width,uitextinput->height,lcol);
        if(uitextinput->active==true) 
            DrawRectangleLines(uitextinput->x-6,uitextinput->y-6,uitextinput->width+4,uitextinput->height+4,lcol);
        DrawText(uitextinput->text,uitextinput->x,uitextinput->y,uitextinput->size_font,lcol);
    }
}

struct UI_FILE_MANAGER UI_FILE_MANAGER(int x,int y ,Color color)
{
    struct UI_FILE_MANAGER uifilemanager={x,y,500,500,color};
    uifilemanager.visible=true;
    uifilemanager.uitext_input = UI_TEXT_FIELD(x+10,y+370,"file name",20,color);
    uifilemanager.uipath = UI_TEXT_INPUT(x+5,y+45,"...",20,color);
    uifilemanager.uitextinput = UI_TEXT_INPUT(x+10,y+400,"input",20,color);
    uifilemanager.uibtn_icon_quit = UI_BUTTON(x+475,y+10,"x",20,color);
    uifilemanager.uibtn_icon_back = UI_BUTTON(x+450,y+45," < ",20,color);
    uifilemanager.uibtn_back = UI_BUTTON(x+420,y+460,"cancel",20,color);
    uifilemanager.uibtn_enter = UI_BUTTON(x+420,y+430,"select",20,color);
    return uifilemanager;
}

void UI_FILE_MANAGER_draw(struct UI_FILE_MANAGER *uifilemanager)
{
    if(uifilemanager->visible)
    {
        DrawRectangleLines(
            uifilemanager->x,
            uifilemanager->y,
            uifilemanager->width,
            uifilemanager->height,
            uifilemanager->color);
        if(UI_BUTTON_draw(&uifilemanager->uibtn_back))
        {
            uifilemanager->visible=false;
        }
        if(UI_BUTTON_draw(&uifilemanager->uibtn_enter))
        {

        }
        if(UI_BUTTON_draw(&uifilemanager->uibtn_icon_back))
        {

        }
        if(UI_BUTTON_draw(&uifilemanager->uibtn_icon_quit))
        {
            uifilemanager->visible=false;
        }
        UI_TEXT_INPUT_draw(&uifilemanager->uitextinput,FR_BEL_VAR);
        UI_TEXT_INPUT_draw(&uifilemanager->uipath,FR_BEL_VAR);
        UI_TEXT_FIELD_draw(&uifilemanager->uitext_input);
    }
}
