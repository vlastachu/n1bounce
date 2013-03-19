#pragma once
#include "Text.h"
#include "Graphics.h"
using std::string;
//может павильнее сделать класс кликэйбл
class Button
{
	void *onClick,  *onHover;
	bool isPositionMatch(float x, float y);
	Text *text;	
	void correctText();
	bool changed;
	float shadow, shadowDefault, shadowClicked;
	Color4f background, defaultBackground, hoveredBackground, clickedBackground;
public:
	//enum TextHorizontalAlignment{left = 0, right = 2, center = 1} textHorizontalAlignment;
	//enum TextVerticalAlignment{top = 0, bottom, vcenter} textVerticalAlignment;	пока что ни к чему
		Button(string t = "", int x_ = 0, int y_= 0);
		Button* draw();
	float padding, border, cornerRadius,
		width, height, x, y;
	bool isHovered;
	Color4f borderColor, shadowColor;
	virtual Text* getText();
	Button* clickUp(float x, float y);
	Button* clickDown(float x, float y);
	Button* hover(float x, float y);
	Button* setOnClick(void _onClickDown(Button* f));
	Button* setOnHover(void _onHover(Button* f));
};
