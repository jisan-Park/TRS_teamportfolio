#include "stdafx.h"
#include "Coin.h"

HRESULT Coin::init()
{
	for (int i = 0; i < MAX_COIN; i++)
	{
		IMAGEMANAGER->addFrameImage("sCoin", "image/coin/smallCoin.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
		_smallCoin[i].img = new image;
		_smallCoin[i].img->init("image/coin/smallCoin.bmp", 300, 50, 6, 1, true, RGB(255, 0, 255));
		_smallCoin[i].img->setFrameY(0);

		_mediumCoin[i].img = IMAGEMANAGER->addFrameImage("mCoin", "image/coin/mediumCoin.bmp", 360, 60, 6, 1, true, RGB(255, 0, 255));
		_mediumCoin[i].img = new image;
		_mediumCoin[i].img->init("image/coin/mediumCoin.bmp", 360, 60, 6, 1, true, RGB(255, 0, 255));
		_mediumCoin[i].img->setFrameY(0);

		_largeCoin[i].img = IMAGEMANAGER->addFrameImage("lCoin", "image/coin/largeCoin.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
		_largeCoin[i].img = new image;
		_largeCoin[i].img->init("image/coin/largeCoin.bmp", 384, 64, 6, 1, true, RGB(255, 0, 255));
		_largeCoin[i].img->setFrameY(0);

		_smallCoin[i].isfire = false;
		_mediumCoin[i].isfire = false;
		_largeCoin[i].isfire = false;
	}

	smallC = 0;
	mediumC = 0;
	largeC = 0;

	return S_OK;
}

void Coin::release()
{
}

void Coin::update()
{

	moveCoin();
	rectCoin();

	if (smallC != 0)
	{
		for (int i = 0; i < smallC; i++)
		{
			_smallCoin[i].isfire = true;
		}
	}
	if (mediumC != 0)
	{
		for (int i = 0; i < mediumC; i++)
		{
			_mediumCoin[i].isfire = true;
		}
	}
	if (largeC != 0)
	{
		for (int i = 0; i < largeC; i++)
		{
			_largeCoin[i].isfire = true;
		}
	}





	for (int i = 0; i < MAX_COIN; i++)
	{
		playerRc = PLAYER->getCharacterRc();

		if (IntersectRect(&temp, &_smallCoin[i].rc, &playerRc) && _smallCoin[i].isfire)
		{
			PLAYER->setMoney(PLAYER->getMoney() + 1);
			_smallCoin[i].isfire = false;
		}
		else if (IntersectRect(&temp, &_mediumCoin[i].rc, &playerRc) && _mediumCoin[i].isfire)
		{
			PLAYER->setMoney(PLAYER->getMoney() + 5);
			_mediumCoin[i].isfire = false;
		}
		else if (IntersectRect(&temp, &_largeCoin[i].rc, &playerRc) && _largeCoin[i].isfire)
		{
			PLAYER->setMoney(PLAYER->getMoney() + 20);
			_largeCoin[i].isfire = false;
		}
	}

}

void Coin::render()
{
	for (int i = 0; i < MAX_COIN; i++)
	{
		_smallCoin[i].img->frameRender(getMemDC(), _sCoinX - 25, _sCoinY - 25);
		//Rectangle(getMemDC(), _smallCoin[i].rc);

		_mediumCoin[i].img->frameRender(getMemDC(), _mCoinX - 30, _mCoinY - 30);
		//Rectangle(getMemDC(), _mediumCoin[i].rc);

		_largeCoin[i].img->frameRender(getMemDC(), _lCoinX - 32, _lCoinY - 32);
		//Rectangle(getMemDC(), _largeCoin[i].rc);
	}
}

void Coin::moveCoin()
{
	for (int i = 0; i < MAX_COIN; i++)
	{
		if (_smallCoin[i].isfire)
		{
			_count1++;

			if (_count1 % 4 == 0)
			{
				if (_index1 >= 6) _index1 = 0;
				_smallCoin[i].img->setFrameX(_index1);
				_index1++;
			}
		}

		if (_mediumCoin[i].isfire)
		{
			_count2++;

			if (_count2 % 4 == 0)
			{
				if (_index2 >= 6) _index2 = 0;
				_mediumCoin[i].img->setFrameX(_index2);
				_index2++;
			}
		}

		if (_largeCoin[i].isfire)
		{
			_count3++;

			if (_count3 % 4 == 0)
			{
				if (_index3 >= 6) _index3 = 0;
				_largeCoin[i].img->setFrameX(_index3);
				_index3++;
			}
		}


	}
}

void Coin::rectCoin()
{
	for (int i = 0; i < MAX_COIN; i++)
	{
		_smallCoin[i].rc = RectMakeCenter(_sCoinX, _sCoinY, 50, 50);
		_mediumCoin[i].rc = RectMakeCenter(_sCoinX, _sCoinY, 60, 60);
		_largeCoin[i].rc = RectMakeCenter(_sCoinX, _sCoinY, 64, 64);

	}
}

