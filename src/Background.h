#include <string>

using std::string;

class Background
{
private:
	float dx, y;
	float texX;
	unsigned texture, texWidth, texHeight;
public:
	Background* setX(float x);
	Background* setY(float y_);
	Background* draw();
	Background* setTexture(char* file);
	Background();
};