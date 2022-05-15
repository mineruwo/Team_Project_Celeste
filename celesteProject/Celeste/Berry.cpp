#include "Berry.h"

Berry::Berry()
{
}

void Berry::Init()
{
	BerryTexture = "Graphics/strawberry/normal00.png";
	this->BerryObj = new Sprite;
		
	BerryObj->setTexture(TextureHolder::GetTexture(BerryTexture));
	BerryObj->setPosition(500, 500);
	BerryObj->setScale(Vector2f(1, 1));

	Speed = 0.05f;
	GetBerryDeley = 0;
	bool isGetBerry = false;
}

void Berry::MoveBerry(float dt, Player player)
{
	/*if (!isGetBerry)
	{
		if (player.GetGobalBound().intersects(BerryObj->getGlobalBounds()))
		{
			berryPosition = player.GetPosition();
			BerryObj->move(Speed * dt * berryPosition);

			GetBerryDeley += dt;
			if(GetBerryDeley > 1.0)



			isGetBerry = true;
		}
	}
	if (isGetBerry)
	{
		if (player.GetGobalBound().intersects(BerryObj->getGlobalBounds()))
		{
			
			delete BerryObj;

			isGetBerry = false;
		}
	}*/

		berryPosition = player.GetPosition();

		BerryObj->move(berryPosition.x - 30.f * dt, berryPosition.y - 30.f * dt);


		GetBerryDeley += dt;

		if (GetBerryDeley > 1.0)
		{

			isGetBerry = false;

		}

}

void Berry::ColliderBerry(Player player)
{
	if (player.GetSprite().getGlobalBounds().intersects(BerryObj->getGlobalBounds()))
	{
		isGetBerry = true;
	}
}




void Berry::GetPlayerPosition(Vector2f Position)
{
}

void Berry::Update(Player player, float dt)
{
	ColliderBerry(player);

	if (isGetBerry)
	{
		MoveBerry(dt, player);
	}

}

void Berry::Draw(RenderWindow& window)
{
	window.draw(*BerryObj);
}
