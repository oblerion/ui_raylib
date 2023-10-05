#include "ui.h"
#include "math.h"

int MATH_collide(int x,int y,int w,int h,int x2,int y2,int w2,int h2)
{
	if(x+w>x2 && x<x2+w2 && y+h>y2 && y2+h2>y) return 1;
	return 0;
}

struct UI_BUTTON UI_BUTTON(int x, int y, const char *name, int size_font, Color color)
{
    struct UI_BUTTON uibutton;
    uibutton.x = x;
    uibutton.y = y;
    strcpy(uibutton.name,name);
    uibutton.size_font = size_font;
    uibutton.color = color;
    uibutton.outline=true;
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
        if(uibutton->outline)DrawRectangleLines(uibutton->x-4,uibutton->y-2,uibutton->width,uibutton->height,lcol);
        DrawText(uibutton->name,uibutton->x,uibutton->y,uibutton->size_font,lcol);
    }
    return lbool;
}

struct UI_TEXTFIELD UI_TEXTFIELD(int x, int y, char *text, int size_font, Color color)
{
    struct UI_TEXTFIELD uitextf;
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

void UI_TEXTFIELD_draw(struct UI_TEXTFIELD* uitextfield)
{
    if(uitextfield->visible)
    {
        DrawText(uitextfield->text,uitextfield->x,uitextfield->y,uitextfield->size_font,uitextfield->color);
    }
}

struct UI_TEXTINPUT UI_TEXTINPUT(int x, int y, char *text, int size_font, Color color)
{
    struct UI_TEXTINPUT uitextinput={
        x,y,0,0,0,size_font,{0},color,true
    };
    strcpy(uitextinput.text,text);
    uitextinput.width = (MeasureText("mmmmmmmmmmmmmmmmmmmmmmmmm",size_font))+8;
    uitextinput.height = size_font+8;

    return uitextinput;
}

void UI_TEXTINPUT_draw(struct UI_TEXTINPUT *uitextinput,KBD_Layout layout)
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
struct UI_SLIDEBAR_V UI_SLIDEBAR_V(int x,int y,int pos_max)
{
    struct UI_SLIDEBAR_V bar = {x,y};
    bar.pos=0;
    UI_SLIDEBAR_V_resize(&bar,pos_max);
    bar.color=BLACK;
    bar.visible=true;
    return bar;
}
void UI_SLIDEBAR_V_resize(struct UI_SLIDEBAR_V* bar,int pos_max)
{
    //actualize size and max barre
    bar->nb_pos_max=pos_max;
    bar->size_cursor=400/pos_max;
}

bool UI_SLIDEBAR_V_draw(struct UI_SLIDEBAR_V* bar)
{
    bool ret = false;
    if(bar->visible==true)
    {
        if(IsKeyPressed(KEY_UP) || GetMouseWheelMove()>0)
        {
            if(bar->pos>0) bar->pos--;
            ret=true;
        }
        if(IsKeyPressed(KEY_DOWN) || GetMouseWheelMove()<0)
        {
            if(bar->pos<bar->nb_pos_max) bar->pos++;
            ret=true;
        }
        DrawRectangle(bar->x,bar->y+(bar->pos*bar->size_cursor),23,bar->size_cursor,bar->color);
        DrawRectangleLines(bar->x,bar->y,23,bar->size_cursor*bar->nb_pos_max,bar->color);
    }
    return ret;
}
void _UI_EXPLORER_scan(struct UI_EXPLORER* uiexp,int pos)
{
    FilePathList files = LoadDirectoryFiles(uiexp->path.text);
    int ifile = 0;
    char lname[files.count][200];
    // dir filter && .
    for(int i=0;i<files.count;i++)
    {
        if(DirectoryExists(files.paths[i]) &&
            files.paths[i][strlen(uiexp->path.text)+1]!='.')
        {
            strcpy(lname[ifile],files.paths[i]);
            ifile++;
        }
    }
    // active/unactive bar
    if(UI_EXPLORER_MAX_FILE<ifile)
    {
        uiexp->barv.visible=true;
        UI_SLIDEBAR_V_resize(&uiexp->barv,ifile-5);
    }
    else
    {
        uiexp->barv.visible=false;
    }

    for(int i=0;i<UI_EXPLORER_MAX_FILE;i++)
    {
        if(i+pos<ifile)
        {
            uiexp->files[i] = UI_BUTTON(
                uiexp->x+40,
                uiexp->y+45+(i*28),GetFileName(lname[i+pos]),19,
                uiexp->color);
            uiexp->files[i].outline=false;
        }
        else
        {
            uiexp->files[i] = UI_BUTTON(0,0,"",0,BLACK);
            uiexp->files[i].visible = false;
        }
    }
    UnloadDirectoryFiles(files);
}

struct UI_EXPLORER UI_EXPLORER(int x,int y,Color color)
{
    struct UI_EXPLORER uiexplorer={
        x,y,true,color,
        UI_TEXTFIELD(x+30,y+10,UI_EXPLORER_START_PATH,20,color)
    };
    uiexplorer.uibtn_icon_back = UI_BUTTON(x+570,y+10," < ",20,color);
    uiexplorer.barv = UI_SLIDEBAR_V(x,y,10);
    _UI_EXPLORER_scan(&uiexplorer,0);
    return uiexplorer;
}

void UI_EXPLORER_draw(struct UI_EXPLORER* uiexp)
{
    if(uiexp->visible)
    {
        DrawRectangleLines(uiexp->x+28,uiexp->y+8,530,24,uiexp->color);
        DrawRectangleLines(uiexp->x+28,uiexp->y+42,530,500,uiexp->color);
        UI_TEXTFIELD_draw(&uiexp->path);
        if(UI_SLIDEBAR_V_draw(&uiexp->barv))
        {
            _UI_EXPLORER_scan(uiexp,uiexp->barv.pos);
        }
        if(UI_BUTTON_draw(&uiexp->uibtn_icon_back))
        {
            // go back directory
            for(int i=strlen(uiexp->path.text);i>0;i--)
            {
                if(uiexp->path.text[i]=='/')
                {
                    uiexp->path.text[i]='\0';
                    _UI_EXPLORER_scan(uiexp,0);
                    uiexp->barv.pos=0;
                    break;
                }
            }
        }
        for(int i=0;i<UI_EXPLORER_MAX_FILE;i++)
        {
            if(UI_BUTTON_draw(&uiexp->files[i]))
            {
                if(DirectoryExists(TextFormat("%s%c%s",uiexp->path.text,'/',uiexp->files[i].name)))
                {
                    sprintf(uiexp->path.text,"%s%c%s",uiexp->path.text,'/',uiexp->files[i].name);
                    _UI_EXPLORER_scan(uiexp,0);
                }
            }
        }
    }
}

struct UI_FILEMANAGER UI_FILEMANAGER(int x,int y ,Color color)
{
    struct UI_FILEMANAGER uifilemanager={x,y,500,500,color};
    uifilemanager.visible=true;
    uifilemanager.uitext_path = UI_TEXTFIELD(x+10,y+15,"file path",20,color);
    uifilemanager.uitext_filename = UI_TEXTFIELD(x+10,y+370,"file name",20,color);
    uifilemanager.uiinput_path = UI_TEXTINPUT(x+5,y+45,"...",20,color);
    uifilemanager.uiinput_filename = UI_TEXTINPUT(x+10,y+400,"input",20,color);
    uifilemanager.uibtn_icon_quit = UI_BUTTON(x+475,y+10,"x",20,color);
    uifilemanager.uibtn_icon_back = UI_BUTTON(x+450,y+45," < ",20,color);
    uifilemanager.uibtn_back = UI_BUTTON(x+420,y+460,"cancel",20,color);
    uifilemanager.uibtn_enter = UI_BUTTON(x+420,y+430,"select",20,color);
    return uifilemanager;
}

void UI_FILEMANAGER_draw(struct UI_FILEMANAGER *uifilemanager)
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
        UI_TEXTINPUT_draw(&uifilemanager->uiinput_path,FR_BEL_VAR);
        UI_TEXTINPUT_draw(&uifilemanager->uiinput_filename,FR_BEL_VAR);
        UI_TEXTFIELD_draw(&uifilemanager->uitext_filename);
        UI_TEXTFIELD_draw(&uifilemanager->uitext_path);
    }
}
