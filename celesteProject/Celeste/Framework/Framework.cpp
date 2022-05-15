#include "Framework.h"

Framework::Framework()
{
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Celeste", Style::Default);
	
	//mainView = new RenderWindow(FloatRect(0, 0, resolution.x, resolution.y));
	//window.setMouseCursorVisible(false);
	window.setFramerateLimit(200);
	icon.loadFromFile("Graphics/icon/icon.PNG");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

}

void Framework::init()
{
	//sceneMgr.SceneInit(resolution);

	SceneMgr::GetInstance().SceneInit(resolution);
}


void Framework::Update()
{
	Event event;
	InputMgr::ClearInput();
	Time dt = clock.restart();
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
		InputMgr::ProcessInput(event);
	}
	//float dt, RenderWindow& window, View& view
	//InputMgr::Update(dt, window, 
	//sceneMgr.SceneUpdate(dt, window);
	SceneMgr::GetInstance().SceneUpdate(dt, window);
}

void Framework::Draw()
{
	window.clear();

	SceneMgr::GetInstance().SceneDraw(window);


	window.display();
}
