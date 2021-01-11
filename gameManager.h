#pragma once
#include "singletonBase.h"
#include "picture.h"

#include <vector>
enum DIFFICULTY {
	EASY,
	NORMAL,
	HARD
};
class gameManager :public singletonBase<gameManager>
{
private:
	vector<picture*>				arrPicture;
	vector<picture*>::iterator	iterPicture;

	DIFFICULTY _difficulty;
	float _hp;
	float _str;

	int renderNum;

	//vector<image*, POINT>
public:
	gameManager();
	~gameManager();
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//setter
	void setDifficulty(int i) { _difficulty = (DIFFICULTY)i; _hp = ((i + 1)*1.0f); _str = ((i + 1) * 0.5f); };
	//getter
	int getDifficulty() { (int)_difficulty; };
	int getRenderNum() { return renderNum++; }; //�Ϸù�ȣ �Ѱ��ְ� 1�� ��ü ������Ű��
	float getHp() { return _hp; };
	float getStr() { return _str; };
	//z-orderRender
	void addPicture(characterInfo info, image * img);
	void addPicture(characterInfo info, image * img, animation * ani);
	void updatePicture(characterInfo info, image * img, animation * ani);
	void quicksort(vector<picture*>& data, int start, int end);
	void deletePicture(int renderNum);
};

