#pragma once

#include <SFML/Graphics.hpp>

struct LevelParams
{
	sf::Vector2i TexSize;
	sf::Vector2f Scale;
	sf::Vector2f Offset;
};

struct Entity
{
	sf::IntRect TexRect;
	unsigned int Num;
	unsigned int Slot;
};

class Level
{
public:

	void Load(const sf::Texture& texture, const LevelParams& params);
	void Restart();

	void Update(float deltaTime);
	void Render(sf::RenderWindow& window);
	void OnEvent(sf::Event& e);

private:
	bool IsGameOver();
	void Move(const sf::Vector2f& pos);
	bool CanIMove(unsigned int slot);

private:
	sf::Clock clock;
	sf::Sprite sprite;
	Entity entities[15];
	sf::Vector2f positions[16];
	float width;
	float height;
	unsigned int freeSlot = 15;
};