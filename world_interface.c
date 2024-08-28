#include "world_interface.h"
#include <stdlib.h>
#include <raylib.h>
#include <stdio.h>
#include "game.h"

extern game_t *pgame;
textBox_t *ga_pTextBoxes[MAX_TEXTBOX];
t_broadcast *ga_pbroadCasts[MAX_BROADCASTS];
static unsigned g_numberOfBroadCasts;


void textBoxTick(textBox_t *ptext)
{
    if(CheckCollisionCircleRec(pgame->m_mousePosWorld, 1, (Rectangle){ptext->m_pos.x, ptext->m_pos.y, ptext->m_width, ptext->m_fontsize}))
    {
        ptext->m_color = GREEN;
        ptext->m_hovered = true;
    }else{
        ptext->m_color = ptext->m_origincolor;
        ptext->m_hovered = false;
    }
    if(ptext->m_hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ptext->m_color = ORANGE;
        ptext->m_pressed = true;
    }
    // text boxes functionalities
    if(ptext->m_pressed == true)
    switch (ptext->m_ID)
    {
        case TEXT_STARTWAVE:
        pgame->m_waveState = WAVE_STARTED;
        ptext->m_show = false;
        ptext->m_pressed = false;
        break;
    
        default:
        break;
    }
}

void createTextBox(char *text, Vector2 pos, int fontSize, Color color, TextBoxes ID)
{
    textBox_t *ptext = malloc(sizeof(textBox_t));
    ga_pTextBoxes[ID] = ptext;
    ptext->m_text = text;
    ptext->m_pos = pos;
    ptext->m_width = MeasureText(text, fontSize);
    ptext->m_hovered = false;
    ptext->m_pressed = false;
    ptext->m_show = false;
    ptext->m_fontsize = fontSize;
    ptext->m_origincolor = color;
    ptext->m_ID = ID;
}

textBox_t *getTextBoxByID(int ID)
{
    return ga_pTextBoxes[ID];
}

void createBroadcast(char *text, int duration, int fontsize)
{
    t_broadcast *pbrod = malloc(sizeof(t_broadcast));
    for(int i = 0; i < MAX_BROADCASTS; i++)
    {
        if(ga_pbroadCasts[i] != NULL)continue;
        ga_pbroadCasts[i] = pbrod;
        pbrod->m_ID = i;
        break;
    }
    pbrod->m_text = text;
    pbrod->m_duration = duration;
    pbrod->m_tick = 0;
    ++g_numberOfBroadCasts;
}

void broadcastTick(t_broadcast *pbrod)
{
    ++pbrod->m_tick;
    if(pbrod->m_tick >= pbrod->m_duration)
    {
        distroyBroadcast(pbrod->m_ID);
        return;
    }
}

t_broadcast *getBroadcastByID(int ID)
{
    return ga_pbroadCasts[ID];
}

void distroyBroadcast(int ID)
{
    if(ID == -1)
    {
        for(int i = 0; i < MAX_BROADCASTS; i++)
        {
            if(ga_pbroadCasts[i] == NULL)continue;
            free(ga_pbroadCasts[i]);
            ga_pbroadCasts[i] = NULL;
        }
        g_numberOfBroadCasts = 0;
        return;
    }
    free(ga_pbroadCasts[ID]);
    ga_pbroadCasts[ID] = NULL;
    --g_numberOfBroadCasts;
}

unsigned getNumberOfBroadcasts()
{
    return g_numberOfBroadCasts;
}