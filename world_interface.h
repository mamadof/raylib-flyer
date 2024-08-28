#ifndef WORLD_INTERFACE_H
#define WORLD_INTERFACE_H
#include <raylib.h>

#define MAX_TEXTBOX 100

typedef  enum{
    TEXT_STARTWAVE,
    TEXT_COUNT
}TextBoxes;

typedef struct{
    Vector2 m_pos;
    unsigned m_fontsize;
    char *m_text;
    int m_width;
    Color m_origincolor;
    Color m_color;
    bool m_hovered;
    bool m_pressed;
    bool m_show;
    TextBoxes m_ID;
}textBox_t;
void createTextBox(char *text, Vector2 pos, int fontsize, Color color, TextBoxes);
textBox_t *getTextBoxByID(int ID);
void textBoxTick(textBox_t *ptext);

#endif //WORLD_INTERFACE_H
