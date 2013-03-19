#include "GUI.h"
void Button::correctText()
{
	text->calculateSizes();
	float align = (width - text->getWidth())/2;
		text->setX(x + padding + border + align);
		text->setY(y  + padding + border);
}



Text* Button::getText()
{
	changed = true;
	return text;
}

inline bool Button::isPositionMatch(float x_, float y_)
{
	bool b = (x_ > x) &&  (x_ < (x + width + 2*padding + 2*border)) && (y_ > y) && (y_ < (y +height + 2*border + 2*padding));
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



Button::Button(string label, int x_, int y_)
{
	onClick = onHover = NULL;
	text = (new Text())->setText(label)->setOutline(6.0,0.8,0.8,0.8,1)->setColor(0.3,0,0,1);//->setFont("../fonts/StencilStd.ttf",30);
	padding = 5;
	height = 20;
	width = 240;
	isHovered = false;
	cornerRadius = 9;
	border = 0;//2;
	borderColor = Color4f(0, 0, 0, 0.5);
	shadowColor = Color4f(0.1711,0,0.12,1);
	background = defaultBackground = Color4f(0.674, 0, 0, 1);
	hoveredBackground = Color4f(0.92, 0, 0, 1);
	clickedBackground = Color4f(0.92, 0, 0, 1);
	//width = text->calculateSizes()->getWidth();
	height = text->calculateSizes()->getHeight();
	x = x_;
	y = y_;
	shadow = shadowDefault = 8;
	shadowClicked = 3;
	correctText();
}


Button* Button::draw()
{
	if (shadow != 0){
		Graphics::color(shadowColor);
		Graphics::rectangle(x + shadow, y + shadow, width + 2*border + 2*padding, height + 2*border + 2*padding);
	}
	if (border != 0){
		Graphics::color(borderColor);
		Graphics::rectangle(x, y, width + 2*border + 2*padding, height + 2*border + 2*padding);
	}
	Graphics::color(background);
	Graphics::rectangle(x+border,y+border,width + 2*padding, height + 2*padding);
	if(changed) correctText();
	text->draw();
	return this;
}

