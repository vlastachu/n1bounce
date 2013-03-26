#include "GUI.h"

inline bool Button::isPositionMatch(float x_, float y_)
{
	bool b = (x_ > x) &&  (x_ < (x + width)) && (y_ > y) && (y_ < (y +height));
	return b;
}

Button* Button::clickUp(float x, float y)
{
	if(isPositionMatch(x, y))
	{
		if(onClick != NULL)
		{
			((void(*)(Button*))onClick)(this);
		}
		shadow = shadowDefault;
	}
	return this;
}
	
Button* Button::clickDown(float x, float y)
{
	if(isPositionMatch(x, y))
	{
		background = clickedBackground;
		shadow = shadowClicked;
	}
	return this;
}
Button* Button::hover(float x, float y)
{

	if(isPositionMatch(x, y) && !isHovered)
	{
		isHovered = true;
		background = hoveredBackground;
		if(onHover != NULL)
		{
			((void(*)(Button*))onHover)(this);
		}
	}
	else if(!isPositionMatch(x, y) && isHovered)
	{
		isHovered = false;
		background = defaultBackground;
	}
	return this;
}
Button* Button::setOnClick(void _onClick(Button* f))
{
	onClick = _onClick;
	return this;
}
Button* Button::setOnHover(void _onHover(Button* f))
{
	onHover = _onHover;
	return this;
}



Button::Button(string label, float x_, float y_)
{
	onClick = onHover = NULL;
	this->label = label;
	height = 0.0333f;
	width = 0.24f;
	isHovered = false;
	shadowColor = Color4f(0.1711,0,0.12,1);
	background = defaultBackground = Color4f(0.674, 0, 0, 1);
	hoveredBackground = Color4f(0.92, 0, 0, 1);
	clickedBackground = Color4f(0.92, 0, 0, 1);
	x = x_;
	y = y_;
	shadow = shadowDefault = 8;
	shadowClicked = 3;
}


Button* Button::draw()
{
	if (shadow != 0){
		Graphics::color(shadowColor);
		Graphics::rectangle(x + shadow, y + shadow, width, height);
	}
	Graphics::color(background);
	Graphics::rectangle(x,y,width, height);
	//Text::drawAtCenter(label, x, y, width, height, "button"); //->setOutline(1,0.75,0.75,0.75,1)->setColor(0.3,0,0,1)
	return this;
}

