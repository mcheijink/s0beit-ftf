#include "../stdafx.h"
#include "../natives.h"

void draw_rect(float Top, float Left, float Height, float Width, int Red, int Green, int Blue, int Alpha)
{
	GRAPHICS::DRAW_RECT((Top + (Height * 0.5f)), (Left + (Width * 0.5f)), Height, Width, Red, Green, Blue, Alpha);
}

void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool bDrawRect = true, bool rescaleText = true)
{
	// default values
	int text_col[4] = { 255, 255, 255, 255 },
		rect_col[4] = { 70, 95, 95, 150 };
	float text_scale = 0.30f;
	int font = 0; //Maybe make this a parameter in the future.

	// correcting values for active line
	if (active)
	{
		text_col[0] = 0;
		text_col[1] = 0;
		text_col[2] = 0;

		rect_col[0] = 218;
		rect_col[1] = 242;
		rect_col[2] = 216;

		if (rescaleText) text_scale = 0.40f;
	}

	if (title)
	{
		rect_col[0] = 0;
		rect_col[1] = 0;
		rect_col[2] = 0;

		if (rescaleText) text_scale = 0.50;
		font = 1;
	}

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	textLeft += lineLeft;

	float lineWidthScaled = lineWidth / (float)screen_w; // line width
	float lineTopScaled = lineTop / (float)screen_h; // line top offset
	float textLeftScaled = textLeft / (float)screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float)screen_h; // line height

	float lineLeftScaled = lineLeft / (float)screen_w;

	// text upper part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	UI::_DRAW_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	int num25 = UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	float num26 = UI::_0xDB88A37483346780(text_scale, 0);

	if (bDrawRect)
		draw_rect(lineLeftScaled, lineTopScaled + (0.007f), lineWidthScaled, ((((float)(num25)*num26) + (lineHeightScaled * 2.0f)) + 0.005f), rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
}
void draw_rect_sc(float lineTop, float lineLeft, float lineWidth, float lineHeight)
{
	// default values
	int rect_col[4] = { 50, 50, 50, 125 };
	float text_scale = 0.30f;
	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);
	float textLeft = 5.0;

	textLeft += lineLeft;

	float lineWidthScaled = lineWidth / (float)screen_w; // line width
	float lineTopScaled = lineTop / (float)screen_h; // line top offset
	float textLeftScaled = textLeft / (float)screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float)screen_h; // line height
	float lineLeftScaled = lineLeft / (float)screen_w;

	//int num25 = UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	//float num26 = UI::_0xDB88A37483346780(text_scale, 0);
	draw_rect(lineLeftScaled, lineTopScaled + (0.007f), lineWidthScaled, lineHeightScaled, rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
}


void draw_text(float x, float y, char* chSampleText, color_t color)
{
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(0.0, 0.25f);
	UI::SET_TEXT_COLOUR(color.red, color.green, color.blue, color.alpha); //White
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(chSampleText);
	UI::_DRAW_TEXT(x, y);
}
//custom notofication service
void drawNotification(std::string str, bool isGxtEntry = false)
{
	/* testing another method
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(message);
	UI::_DRAW_NOTIFICATION(FALSE, TRUE);
	*/
	UI::_SET_NOTIFICATION_TEXT_ENTRY((isGxtEntry ? &str[0u] : "STRING"));
	UI::_ADD_TEXT_COMPONENT_STRING(&str[0u]);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE); // _DRAW_NOTIFICATION(BOOL blink, BOOL p1)
}

std::string GetPlayerName(Player Player)
{

	char chStringName[50];
	strcpy_s(chStringName, PLAYER::GET_PLAYER_NAME(Player));

	//char chStringName[32];
	//sprintf_s(chStringName, "%s", PLAYER::GET_PLAYER_NAME(Player));
	//sprintf_s(chStringName, "%s", chStringName);

	std::string stringName = (std::string)chStringName;
	std::string t = "";
	unsigned int i1;

	for (i1 = 0; i1 < stringName.length(); i1++)
	{
		if (!isspace(stringName[i1]))
			t += stringName[i1];
	}

	stringName = t;

	return stringName;
}