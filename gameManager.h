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
	//volume
	float _background_volume;
	float _SFX_volume;

	int renderNum;
	//UI
	image* _uiImage;

	image* hp_number_100;
	image* hp_number_10;
	image* hp_number_1;

	image* gp_number_100;
	image* gp_number_10;
	image* gp_number_1;

	image* coin_number_100;
	image* coin_number_10;
	image* coin_number_1;

	image* life_number;

	image* _snack;
	int _shopNum;
	//vector<image*, POINT>
public:
	gameManager();
	~gameManager();
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	//setter
	void setShopNum(int i) { _shopNum = i; };
	void setBackgroundVolume(float f) { _background_volume = f; };
	void setSFXVolume(float f) { _SFX_volume = f; };
	void setUI();
	void setUIimage();
	void setDifficulty(int i) { _difficulty = (DIFFICULTY)i; _hp = ((i + 1)*1.0f); _str = ((i + 1) * 0.5f); };
	//getter
	int getShopNum() { return _shopNum; };
	float getBackgroundVolume() { return _background_volume; };
	float getSFXVolume() { return _SFX_volume; };
	int getDifficulty() { (int)_difficulty; };
	int getRenderNum() { return renderNum++; }; //일련번호 넘겨주고 1씩 자체 증가시키기
	float getHp() { return _hp; };
	float getStr() { return _str; };
	//z-orderRender
	void addPicture(characterInfo info, image * img);
	void addPicture(characterInfo info, image * img, animation * ani);
	void updatePicture(characterInfo info, image * img, animation * ani);
	void quicksort(vector<picture*>& data, int start, int end);
	void deletePicture(int renderNum);
	void resetPicture() { arrPicture.clear(); };
};

