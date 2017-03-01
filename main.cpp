#include <SFML/Graphics.hpp>
#include <iostream>

#define WIDE 800
#define HIGH 600

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"THE ADVENTURE");

  int speed = 1;
  int Points = 10002;


  sf::RectangleShape hero(sf::Vector2f(25,25));
  hero.setFillColor(sf::Color::Red);
  hero.setPosition(WIDE-50,0);


  sf::CircleShape circle(25);
  circle.setFillColor(sf::Color::Blue);
  circle.setPosition(0,225);
  int circleDirection = 0;

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
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getPosition().y < HIGH-hero.getSize().y)
    {
        hero.move(0,speed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hero.getPosition().x > 0)
    {
        hero.move(-speed,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hero.getPosition().x < WIDE-hero.getSize().x)
    {
        hero.move(speed,0);
    }

    if(hero.getGlobalBounds().intersects(circle.getGlobalBounds()))
    {
      std::cout << "NOOOOO!" << std::endl;
    }
    else
    {
      std::cout << "ok." << std::endl;
    }

    window.clear(sf::Color::Green);
    //updates stuff-Aaron

    if(circleDirection == 0)
    {
      circle.move(1,0);
    }
    else
    {
      circle.move(-1,0);
    }
    if(circle.getPosition().x > 800)
    {
      circleDirection = 1;
    }
    if(circle.getPosition().x < 0)
    {
      circleDirection = 0;
    }
      window.draw(hero);
      window.draw(circle);

    //Render-Max
    window.display();
  }
}
