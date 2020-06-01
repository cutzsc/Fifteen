#include <poorpch.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

template<class T>
void show(const T message)
{
	std::cout << message << std::endl;
}

int main(int argc, char* argv[]);

struct Number
{
	sf::Sprite sprite;
};

class Game
{
private:
	sf::Texture tex;
	Number numbers[15];

public:
	Game()
	{
		window.create(sf::VideoMode(800, 600), "15 Puzzle");
		window.setVerticalSyncEnabled(true);

		tex.loadFromFile("assets/numbers.png");
		
		for (int i = 0; i < 15; i++)
		{
			numbers[i].sprite.setTexture(tex);

			numbers[i].sprite.setTextureRect(sf::IntRect(i * 32, 0, 32, 32));
			numbers[i].sprite.setPosition(i * (numbers[i].sprite.getLocalBounds().width +
				numbers[i].sprite.getLocalBounds().width / 2.0f), 0);
		}
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

			window.display();
		}
	}

	void OnUpdate(float deltaTime)
	{
		static unsigned int fps = 0;
		static float time = 0;
		time += deltaTime;
		fps++;
		if (time >= 1.0f)
		{
			show(fps);
			fps = 0;
			time -= 1.0f;
		}

		
	}

	void OnRender()
	{
		for (auto& num : numbers)
		{
			window.draw(num.sprite);
		}
	}

	void OnEvent(sf::Event& e)
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			OnWindowClose(e);
		case sf::Event::Resized:
			OnWindowResize(e);
		}
	}

	void OnWindowClose(sf::Event& e)
	{
		running = false;
	}

	void OnWindowResize(sf::Event& e)
	{
		if (running)
			glViewport(0, 0, e.size.width, e.size.height);
		
	}

private:
	sf::RenderWindow window;
	bool running = true;
};


int main(int argc, char* argv[])
{
	Game game;
	game.Run();
	return 0;
}