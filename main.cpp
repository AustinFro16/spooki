#include <SFML/Graphics.hpp>

#define WIDE 800
#define HIGH 600

int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"THE ADVENTURE");

  sf::CircleShape circle(100);
  circle.setFillColor(sf::Color::Yellow);
  circle.setPosition(0,200);
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

    window.clear(sf::Color::Red);
    //updates stuff-Aaron

    if(circleDirection == 0)
    {
      circle.move(0.7,0);
    }
    else
    {
      circle.move(-0.5,0);
    }
    if(circle.getPosition().x > 600)
    {
      circleDirection = 1;
    }
    if(circle.getPosition().x < 0)
    {
      circleDirection = 0;
    }

      window.draw(circle);

    //Render-Max
    window.display();
  }
}
