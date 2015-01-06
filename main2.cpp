#include <iostream>
#include "Capture.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

struct yuyv
{
    __u8 y;
    __u8 rest;
};

int main()
{
    Capture cap("/dev/video0", 640, 480, "YUYV", 15);

    std::cout << cap.getController().getContrast() << std::endl;

    sf::RenderWindow window(sf::VideoMode(640,480), "VideoTest");
    window.setFramerateLimit(30);

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Image img;

    img.create(640,480,sf::Color::Black);

    Image frame;
    bool gotFrame = false;

    while(!gotFrame)
    {
	try
	{
	    frame = cap.getFrame();
	    std::cout << frame.getData() << std::endl;
	    std::cout << "Got the Frame" << std::endl;
	    gotFrame = true;
	}
	catch(NoFrameException)
	{
	    std::cout << "No Frame available" << std::endl;
	}
    }
    
    sf::Clock clock;
    long timeperiod = 0;
    while (window.isOpen())
    {
	sf::Event event;


	while(window.pollEvent(event))
	{
	    if(event.type == sf::Event::Closed)
	    {
		window.close();
	    }
	}
	/*

	try
	{
	    auto frame = std::move(cap.getFrame());

	    for(int i = 0; i < 480; i++)
		for(int j = 0; j < 640 ; j++)
		{
		    auto tmp = ((yuyv*) (frame.getData()))[i*640+j];
		    img.setPixel(j,i,sf::Color(tmp.y,tmp.y,tmp.y,255));
		}
	    texture.loadFromImage(img);
	    sprite.setTexture(texture);

	    window.clear();
	    window.draw(sprite);
	    window.display();
	}
	catch(NoFrameException)
	{
	    std::cout << "no frame" << std::endl;
	}
	*/

	try
	{
	    cap.getFrame();
	}
	catch(...)
	{

	}

	if(frame.getData())
	{
	    for(int i = 0; i < 480; i++)
		for(int j = 0; j < 640 ; j++)
		{
		    auto tmp = ((yuyv*) (frame.getData()))[i*640+j];
		    img.setPixel(j,i,sf::Color(tmp.y,tmp.y,tmp.y,255));
		}
	    texture.loadFromImage(img);
	    sprite.setTexture(texture);

	    window.clear();
	    window.draw(sprite);
	    window.display();
	}
	else
	{
	    window.clear();
	    window.display();
	}
    }

    return 0;
}
