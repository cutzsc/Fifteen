#pragma once

#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Base.h"

int main(int argc, char* argv[]);

class Game
{
public:
	Game()
	{
		window.create(sf::VideoMode(800, 600), "15 Puzzle");
		window.setVerticalSyncEnabled(true);

		texture.loadFromFile("assets/numbers.png");
		font.loadFromFile("assets/Montserrat-Regular.otf");
		text.setFont(font);
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setCharacterSize(20);

		level.Load(texture, { { 32, 32 }, {2.0f, 2.0f }, { 10.0f, 10.0f } });
	}

	~Game()
	{
		window.close();
	}


private:
	friend int ::main(int argc, char* argv[]);

	void Run()
	{
		sf::Time pastTime;
		sf::Time deltaTime;
		sf::Clock clock;
		sf::Event e;

		while (running)
		{
			sf::Time time = clock.getElapsedTime();
			deltaTime = time - pastTime;
			pastTime = time;

			while (window.pollEvent(e))
			{
				OnEvent(e);
			}

			OnUpdate(deltaTime.asSeconds());

			window.clear(sf::Color(
				static_cast<sf::Uint8>(0.1f * 255.0f),
				static_cast<sf::Uint8>(0.1f * 255.0f),
				static_cast<sf::Uint8>(0.1f * 255.0f)));

			OnRender();
			OnGUI();

			window.display();
		}
	}

	void OnUpdate(float deltaTime)
	{
		level.Update(deltaTime);
	}

	void OnRender()
	{
		level.Render(window);
	}

	void OnEvent(sf::Event& e)
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			OnWindowClose(e);
		}

		level.OnEvent(e);
	}

	void OnGUI()
	{
		text.setString(restartText);
		text.setOrigin({ 1.0f, 0.0f });
		int textWidth = static_cast<unsigned int>(restartText.length()) * text.getCharacterSize();
		text.setPosition({ static_cast<float>(window.getSize().x - textWidth), 100.0f });
		window.draw(text);
	}

	void OnWindowClose(sf::Event& e)
	{
		running = false;
	}

private:
	sf::RenderWindow window;
	bool running = true;
	sf::Texture texture;
	sf::Font font;
	sf::Text text;
	Level level;

	std::string restartText = "Space - to restart";
};