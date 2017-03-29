#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#define TILESIZE 32

#define WIDE 800
#define HIGH 640


bool testColl(sf:: Sprite a, sf:: Sprite b)
{
  return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

bool testWallColl(sf:: Sprite a, std::vector<sf::Sprite> wood)
{
  for(int i=0; i<wood.size(); i++)
  {
    if(a.getGlobalBounds().intersects(wood[i].getGlobalBounds()))
    {
        return true;
    }
  }
  return false;
}





int main()
{
  sf::RenderWindow window(sf::VideoMode(WIDE,HIGH),"THE ADVENTURE");

  int tileW = WIDE/TILESIZE;
  int tileH = HIGH/TILESIZE;

  std::vector<std::vector<bool> > map;

  for(int i=0; i<tileH; i++)
  {
    std::vector<bool> temp;
    for(int j=0; j<tileW; j++)
    {
      temp.push_back(false);
    }
    map.push_back(temp);
  }

  map[4][3] = true;
  map[5][3] = true;
  map[3][3] = true;
  map[3][2] = true;
  map[6][3] = true;
  map[6][2] = true;
  map[6][1] = true;


  for(int i=0; i<tileH; i++)
  {
    map[i][0] = true;
    map[i][tileW-1] = true;
  }
  for(int i=0; i<tileW; i++)
  {
    map[0][i] = true;
    map[tileH-1][i] = true;
  }

  for(int i=0; i<map.size(); i++)
  {
    for(int j=0; j<map[i].size(); j++)
    {
        if(map[i][j] == true)
        {
          std::cout << 'X';
        }
        else
        {
          std::cout << ' ';
        }

    }
    std::cout << std::endl;
  }



  double speed = 1;
  int Lives = 6;
  bool takingDamage = false;
  double homingX = 0.5;
  double homingY = 0.5;
  double homingDist = 0;

  sf::Texture hero_texture;
  if(!hero_texture.loadFromFile("assets/Hero1.png"))
  {
    std::cout << "ERROR LOADING HERO" << std::endl;
  }
  sf::Sprite hero;
  hero.setTexture(hero_texture);
  hero.setScale(sf::Vector2f(.5,.5));
  hero.setPosition(320,320);



  sf::Texture goblin_texture;
  if(!goblin_texture.loadFromFile("assets/goblin1.png"))
  {
    std::cout << "ERROR LOADING GOBLIN" << std::endl;
  }
  sf::Sprite goblin;
  goblin.setTexture(goblin_texture);
  goblin.setScale(sf::Vector2f(.5,.5));
  int goblinDirection = 0;
  goblin.setPosition(192,192);

  sf::Texture ghoul_texture;
  if(!ghoul_texture.loadFromFile("assets/ghoul.png"))
  {
    std::cout << "ERROR LOADING GHOUL" << std::endl;
  }
  sf::Sprite ghoul;
  ghoul.setTexture(ghoul_texture);
  ghoul.setScale(sf::Vector2f(.5,.5));
  int ghoulDirection = 0;
  ghoul.setPosition(384,384);

  sf:: Font font;
  if(!font.loadFromFile("assets/ARCADECLASSIC.TTF"))
  {
    std::cout << "ERROR LOADING FONT" << std::endl;
  }
  sf::Text livesDisp;
  livesDisp.setFont(font);
  livesDisp.setCharacterSize(24);
  livesDisp.setColor(sf::Color::Red);

  sf::Texture wood_texture;
  if(!wood_texture.loadFromFile("assets/wood1.png"))
  {
    std::cout << "ERROR LOADING WOOD" << std::endl;
  }
  std::vector<sf::Sprite> woodArr;
  for(int i=0; i<map.size(); i++)
  {
    for(int j=0; j<map[i].size(); j++)
    {
      if(map[i][j] == true)
      {
        sf::Sprite temp;
        temp.setTexture(wood_texture);
        temp.setScale(sf::Vector2f(.5,.5));
        temp.setPosition(j*TILESIZE,i*TILESIZE);
        woodArr.push_back(temp);
      }
    }
  }

  sf::Texture stone_texture;
  if(!stone_texture.loadFromFile("assets/cobblestone1.png"))
  {
    std::cout << "ERROR LOADING STONE" << std::endl;
  }
  sf::Sprite stone;
  stone.setTexture(stone_texture);
  stone.setScale(sf::Vector2f(1,1));


  sf::SoundBuffer grunt_buffer;
  if(!grunt_buffer.loadFromFile("assets/grunt.wav"))
  {
    std::cout << "ERROR LOADING GRUNT" << std::endl;
  }
  sf::Sound grunt;
  grunt.setBuffer(grunt_buffer);
  grunt.setPitch(1.001);

  //sf::SoundBuffer music_buffer;
  //if(!grunt_buffer.loadFromFile("assets/music1.wav"))
  //{
    //std::cout << "ERROR LOADING MUSIC" << std::endl;
  //}
  //sf::Sound music;
  //music.setBuffer(music_buffer);
  //music.setPitch(1);
  //music.setLoop(true);




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
        if(testWallColl(hero, woodArr))
        {
          hero.move(0,speed);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && hero.getPosition().y < HIGH-TILESIZE)
    {
        hero.move(0,speed);
        if(testWallColl(hero, woodArr))
        {
          hero.move(0,-speed);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && hero.getPosition().x > 0)
    {
        hero.move(-speed,0);
        if(testWallColl(hero, woodArr))
        {
          hero.move(speed,0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && hero.getPosition().x < WIDE-TILESIZE)
    {
        hero.move(speed,0);
        if(testWallColl(hero, woodArr))
        {
          hero.move(-speed,0);
        }
    }

    if(hero.getGlobalBounds().intersects(goblin.getGlobalBounds()))
    {
      if(takingDamage == false)
      {
        Lives--;
        grunt.play();
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
    if(testWallColl(goblin, woodArr))
    {
      if(goblinDirection == 1)
      {
        goblinDirection = 0;
      }
      else
      {
        goblinDirection = 1;
      }

    }




      for(int i=0; i<tileH; i++)
      {
        for(int j=0; j<tileW; j++)
        {
          stone.setPosition(j*TILESIZE,i*TILESIZE);
          window.draw(stone);
        }
      }
      window.draw(ghoul);
      window.draw(hero);
      window.draw(goblin);
      for(int i=0; i<woodArr.size(); i++)
      {
          window.draw(woodArr[i]);
      }
      window.draw(livesDisp);
      livesDisp.setString(std::to_string(Lives));

    //Render-Max
    window.display();
  }
}
