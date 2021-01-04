#pragma once
class square
{
public :
	RECT _rc;
	float _x, _y, _width, _height;
public:
	square();
	~square();
	void init(float x,float y, float width, float height);
	void render(HDC hdc);

	bool operator<(square* s)const {
		if (this->_y == s->_y) {
			return this->_x < s->_x;
		}
		else {
			return this->_y < s->_y;
		}
	}
};

