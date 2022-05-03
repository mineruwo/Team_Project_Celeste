#include "Framework.h"

Framework::Framework()
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Celeste", Style::Default);
	
	//window.setMouseCursorVisible(false);

	icon.loadFromFile("Graphics/icon/icon.PNG");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Framework::init()
{
	sceneMgr.SceneInit(resolution);
}


void Framework::Update()
{
	Event event;
	Time dt = clock.restart();
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
	
	}
	sceneMgr.SceneUpdate(dt, window);

}

void Framework::Draw()
{
	window.clear();
	sceneMgr.SceneDraw(window);
	//window.display();
}
