#pragma once

#include "../stdafx.h"


void draw_rect(float Top, float Left, float Height, float Width, int Red, int Green, int Blue, int Alpha);
void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool bDrawRect = true, bool rescaleText = true);
void draw_rect_sc(float lineTop, float lineLeft, float lineWidth, float lineHeight);
void draw_text(float x, float y, char* chSampleText, color_t color);
void drawNotification(std::string str, bool isGxtEntry = false);
std::string GetPlayerName(Player Player);