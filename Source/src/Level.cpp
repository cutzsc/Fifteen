#include <poorpch.h>
#include "Level.h"

#include "Base.h"

void Level::Load(const sf::Texture& texture, const LevelParams& params)
{
	sprite.setTexture(texture);
	sprite.setScale(params.Scale);
	sprite.setOrigin(0.5f, 0.5f);

	for (unsigned int i = 0; i < 16; i++)
	{
		if (i < 15)
		{
			entities[i].Slot = i;
			entities[i].Num = i + 1;
			entities[i].TexRect = sf::IntRect((i + 1) * params.TexSize.x, 0,
				params.TexSize.x, params.TexSize.y);
		}

		positions[i].x = i % 4 * (params.TexSize.x * params.Scale.x + params.Offset.x);
		positions[i].y = i / 4 * (params.TexSize.x * params.Scale.x + params.Offset.y);
	}
}

void Level::Restart()
{
	clock.restart();
}

void Level::Update(float deltaTime)
{
	if (IsGameOver())
	{
		//clog("Game Over");
	}

}

void Level::Render(sf::RenderWindow& window)
{
	for (auto& entity : entities)
	{
		sprite.setTextureRect(entity.TexRect);
		sprite.setPosition(positions[entity.Slot]);
		window.draw(sprite);
	}
}

void Level::OnEvent(sf::Event& e)
{
	switch (e.type)
	{
	case sf::Event::MouseButtonReleased:
		if (e.mouseButton.button == sf::Mouse::Button::Left)
		{
			Move({ (float)e.mouseButton.x, (float)e.mouseButton.y });
		}
	}
}

void Level::Move(const sf::Vector2f& mouse)
{
	for (unsigned int i = 0; i < 15; i++)
	{
		sprite.setTextureRect(entities[i].TexRect);
		sprite.setPosition(positions[entities[i].Slot]);
		if (sprite.getGlobalBounds().contains(mouse))
		{
			if (CanIMove(entities[i].Slot))
			{
				unsigned int tempSlot = freeSlot;
				freeSlot = entities[i].Slot;
				entities[i].Slot = tempSlot;
			}
		}
	}
}

bool Level::IsGameOver()
{
	for (unsigned int i = 0; i < 15; i++)
	{
		if (entities[i].Num != (entities[i].Slot + 1))
			return false;
	}
	return true;
}

bool Level::CanIMove(unsigned int slot)
{
	if (slot == freeSlot - 1 ||
		slot == freeSlot + 1 ||
		slot == freeSlot - 4 ||
		slot == freeSlot + 4)
		return true;
	return false;
}