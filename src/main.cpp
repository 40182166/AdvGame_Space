#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <GameState.hpp>
//using namespace sf;



int main()
{
	try
	{
		GameState::Start();
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
		
	return 0;
}

/*Texture texture;
Sprite sprite;
float thresholdBound = 50.0f;

void Load() {
  if (!texture.loadFromFile("res/img/spaceship1.png")) {
    throw std::invalid_argument("Loading error!");
  }
}

void Update(sf::RenderWindow& window) {
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  Vector2f move;
  float left = 0.0f + thresholdBound; //useless, but shows the meaning of the threshold
  float right = window.getSize().x - thresholdBound;

  if (Keyboard::isKeyPressed(Keyboard::Left)) {
	  if (sprite.getPosition().x <= left)
	  {
		  sprite.setPosition(left, sprite.getPosition().y);
	  }
	  else
	  {
		  move.x--;
	  }
    
	std::cout << sprite.getPosition().x << "\n";
  }
  if (Keyboard::isKeyPressed(Keyboard::Right)) {
	  if (sprite.getPosition().x >= right)
	  {
		  sprite.setPosition(right, sprite.getPosition().y);
	  }
	  else
	  {
		  move.x++;
	  }
    
	std::cout << sprite.getPosition().x << "\n";
  }
  sprite.move(move*300.0f*dt);
}

void Render(RenderWindow &window) 
{ 
	window.draw(sprite); 
}

int main() {
  RenderWindow window(VideoMode(400, 400), "Cat Invaders");

  try {
    Load();
  } catch (const std::exception &) {
    std::cerr << "Load error" << std::endl;
    return 1;
  }

  sf::Vector2u size = window.getSize();
  unsigned int width = size.x;
  unsigned int height = size.y;

  sprite.setTexture(texture);
  sprite.setScale(Vector2f(2.f, 2.f));

  sf::FloatRect spriteBound = sprite.getLocalBounds();
  sprite.setOrigin(spriteBound.left + spriteBound.width / 2.0f,
				   spriteBound.top + spriteBound.height / 2.0f);
  sprite.setPosition(sf::Vector2f(width / 2.0f, height - thresholdBound));


  while (window.isOpen()) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed){
        window.close();
      }
    }
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
      window.close();
    }

    window.clear();
    Update(window);
    Render(window);
    window.display();
  }

  return 0;
}*/