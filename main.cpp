#include <SFML/Graphics.hpp>
#include <iostream>
#define TILESIZE 80

#define WIDE 800
#define HIGH 600

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"THE ADVENTURE");

  double speed = 1;
  int Lives = 6;
  bool takingDamage = false;

  sf::Texture hero_texture;
  if(!hero_texture.loadFromFile("assets/Hero1.png"))
  {
    std::cout << "ERROR LOADING HERO" << std::endl;
  }
  sf::Sprite hero;
  hero.setTexture(hero_texture);
  hero.setScale(sf::Vector2f(1,1));
  hero.setPosition(100,100);



  sf::Texture goblin_texture;
  if(!goblin_texture.loadFromFile("assets/goblin1.png"))
  {
    std::cout << "ERROR LOADING GOBLIN" << std::endl;
  }
  sf::Sprite goblin;
  goblin.setTexture(goblin_texture);
  goblin.setScale(sf::Vector2f(1,1));
  int goblinDirection = 0;
  goblin.setPosition(0,200);

  sf:: Font font;
  if(!font.loadFromFile("assets/ARCADECLASSIC.TTF"))
  {
    std::cout << "ERROR LOADING FONT" << std::endl;
  }
  sf::Text livesDisp;
  livesDisp.setFont(font);
  livesDisp.setCharacterSize(24);
  livesDisp.setColor(sf::Color::Black);

  sf::Texture wood_texture;
  if(!wood_texture.loadFromFile("assets/wood1.png"))
  {
    std::cout << "ERROR LOADING WOOD" << std::endl;
  }
  sf::Sprite wood;
  wood.setTexture(wood_texture);
  wood.setScale(sf::Vector2f(1,1));
  wood.setPosition(400,400);




  //Game Loop
  while(window.isOpen())
  {
    //Handles Events
    sf::Event event;
    while(window.pollEvent(event))
    {
      //Close Event
      if(event.type ==sf::Event::Closed)
      {
        window.close();
      }


    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && hero.getPosition().y > 0)
    {
        hero.move(0,-speed);
        if(hero.getGlobalBounds().intersects(wood.getGlobalBounds()))
        {
          hero.move(0,speed);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getPosition().y < HIGH-TILESIZE)
    {
        hero.move(0,speed);
        if(hero.getGlobalBounds().intersects(wood.getGlobalBounds()))
        {
          hero.move(0,-speed);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hero.getPosition().x > 0)
    {
        hero.move(-speed,0);
        if(hero.getGlobalBounds().intersects(wood.getGlobalBounds()))
        {
          hero.move(speed,0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hero.getPosition().x < WIDE-TILESIZE)
    {
        hero.move(speed,0);
        if(hero.getGlobalBounds().intersects(wood.getGlobalBounds()))
        {
          hero.move(-speed,0);
        }
    }

    if(hero.getGlobalBounds().intersects(goblin.getGlobalBounds()))
    {
      if(takingDamage == false)
      {
        Lives--;
        takingDamage = true;
      }
    }
    else
    {
      takingDamage = false;
    }

    window.clear(sf::Color::Green);
    //updates stuff-Aaron

    if(goblinDirection == 0)
    {
      goblin.move(1,0);
    }
    else
    {
      goblin.move(-1,0);
    }
    if(goblin.getPosition().x > 800)
    {
      goblinDirection = 1;
    }
    if(goblin.getPosition().x < 0)
    {
      goblinDirection = 0;
    }
      window.draw(goblin);
      window.draw(hero);
      window.draw(wood);
      window.draw(livesDisp);
      livesDisp.setString(std::to_string(Lives));

    //Render-Max
    window.display();
  }
}
