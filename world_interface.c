#include "world_interface.h"
#include <stdlib.h>
#include <raylib.h>
#include <stdio.h>
#include "game.h"

extern game_t *pgame;
textBox_t *ga_pTextBoxes[MAX_TEXTBOX];

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