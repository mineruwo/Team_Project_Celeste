#include "Thorny.h"

Thorny::Thorny()
{
}

void Thorny::Init()
{
	thornyTexture = "Graphics/cliffside_up00.png";
	thornyObj.setTexture(TextureHolder::GetTexture(thornyTexture));

	thronyPos.x = 500;
	thronyPos.y = 580;

	thornyObj.setPosition(thronyPos);
	thornyObj.setScale(3, 3);
	//thornyObj.setColor(Color::Red);

	thornyBox.setPosition(thronyPos);
	thornyBox.setSize(Vector2f(30, 30));
	thornyBox.setFillColor(Color::Transparent);
	thornyBox.setOutlineColor(Color::Red);
	thornyBox.setOutlineThickness(2);

}

void Thorny::Update(Player &player)
{
	if (player.GetSprite().getGlobalBounds().intersects(thornyBox.getGlobalBounds()))
	{
		std::cout << "Thorny" << std::endl;
		player.ResetPosition();
	}
}

void Thorny::Draw(RenderWindow& window)
{
	window.draw(thornyObj);
	window.draw(thornyBox);
}
