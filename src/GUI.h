#pragma once
#include "Graphics.h"
using std::string;
//может павильнее сделать класс кликэйбл
class Button
{
	void *onClick,  *onHover;
	bool isPositionMatch(float x, float y);
	string label;
	float shadow, shadowDefault, shadowClicked;
	float width, height, x, y;//border, cornerRadius,	
	Color4f shadowColor; //borderColor
	Color4f background, defaultBackground, hoveredBackground, clickedBackground;
public:
	//enum TextHorizontalAlignment{left = 0, right = 2, center = 1} textHorizontalAlignment;
	//enum TextVerticalAlignment{top = 0, bottom, vcenter} textVerticalAlignment;	пока что ни к чему
	Button(string t = "", float x_ = 0, float y_= 0);
	Button* draw();
	bool isHovered;
	Button* clickUp(float x, float y);
	Button* clickDown(float x, float y);
	Button* hover(float x, float y);
	Button* setOnClick(void _onClickDown(Button* f));
	Button* setOnHover(void _onHover(Button* f));
};
