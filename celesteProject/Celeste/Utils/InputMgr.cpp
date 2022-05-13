#include "InputMgr.h"
#include <algorithm>
#include <iostream>
#include <cmath>

map<Axis, AxisInfo> InputMgr::mapAxis;

list<Keyboard::Key> InputMgr::downKeys;
list<Keyboard::Key> InputMgr::ingKeys;
list<Keyboard::Key> InputMgr::upKeys;

list<Mouse::Button>  InputMgr::downButtons;
list<Mouse::Button>  InputMgr::ingButtons;
list<Mouse::Button>  InputMgr::upButtons;

Vector2i InputMgr::mousePosititon;
Vector2f InputMgr::mousePosititonWorld;

void InputMgr::Init()
{
	mapAxis.clear();
	HorInit();
	VerInit();
}

void InputMgr::HorInit()
{
	AxisInfo info;
	info.axis = Axis::Horizontal;
	info.sensi = 2.f;
	info.value = 0.f;
	info.limit = 0.05f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::Right);
	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::Left);
	mapAxis[info.axis] = info;
}

void InputMgr::VerInit()
{
	AxisInfo info;

	// Vertical
	info.axis = Axis::Vertical;
	info.sensi = 2.f;
	info.value = 0.f;
	info.limit = 0.05f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::Down);
	info.negativeKeys.clear();
	info.negativeKeys.push_back(Keyboard::Up);
	mapAxis[info.axis] = info;
}

void InputMgr::ClearInput()
{
	downKeys.clear();
	upKeys.clear();
}

void InputMgr::ProcessInput(const Event& event)
{
	switch (event.type)
	{
	case Event::KeyPressed:
		if (!GetKey(event.key.code))
		{
			downKeys.push_back(event.key.code);
			ingKeys.push_back(event.key.code);
		}
		break;
	case Event::KeyReleased:
		ingKeys.remove(event.key.code);
		upKeys.push_back(event.key.code);
		break;

	default:
		break;
	}
}

void InputMgr::Update(float dt)
{
	for (auto it = mapAxis.begin(); it != mapAxis.end(); ++it)
	{
		AxisInfo& ref = it->second;

		int axis = GetAxisRaw(ref.axis);
		if (axis == 0)
		{
			axis = ref.value > 0 ? -1 : 1;
			if (abs(ref.value) < ref.limit)
			{
				axis = 0;
				ref.value = 0;
			}
		}

		ref.value += axis * ref.sensi * dt;
		if (ref.value > 1.f)
		{
			ref.value = 1.f;
		}
		if (ref.value < -1.f)
		{
			ref.value = -1.f;
		}
	}
}

float InputMgr::GetAxis(Axis axis)
{
	if (mapAxis.find(axis) != mapAxis.end())
	{
		return mapAxis[axis].value;
	}
	return 0.0f;
}

int InputMgr::GetAxisRaw(const list<Keyboard::Key>& positive, const list<Keyboard::Key>& negaive)
{
	int axis = 0;
	bool isPositive = false, isNegative = false;

	for (auto it = positive.cbegin(); it != positive.cend(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isPositive = true;
			break;
		}
	}
	for (auto it = negaive.cbegin(); it != negaive.cend(); ++it)
	{
		Keyboard::Key key = (*it);
		if (Keyboard::isKeyPressed(key))
		{
			isNegative = true;
			break;
		}
	}
	if (isPositive && isNegative)
	{
		axis = 0;
	}
	else if (isPositive)
	{
		axis = 1;
	}
	else if (isNegative)
	{
		axis = -1;
	}
	return axis;
}

int InputMgr::GetAxisRaw(Axis axis)
{
	auto pair = mapAxis.find(axis);
	if (pair != mapAxis.end())
	{
		return GetAxisRaw(pair->second.positiveKeys, pair->second.negativeKeys);
	}
	return 0;
}

/*========================
	 키보드 눌렀을때
==========================*/
bool InputMgr::GetKeyDown(Keyboard::Key key)
{
	auto it = find(downKeys.begin(), downKeys.end(), key);
	return it != downKeys.end();
}
/*========================
	키보드 누르는 중일때
==========================*/
bool InputMgr::GetKey(Keyboard::Key key)
{
	auto it = find(ingKeys.begin(), ingKeys.end(), key);
	return it != ingKeys.end();
}
/*========================
	 키보드를 뗏을때
==========================*/
bool InputMgr::GetKeyUp(Keyboard::Key key)
{
	auto it = find(upKeys.begin(), upKeys.end(), key);
	return it != upKeys.end();
}

Vector2i InputMgr::GetMousePosition()
{
	return mousePosititon;
}

Vector2f InputMgr::GetMouseWolrdPosition()
{
	return mousePosititonWorld;
}

bool InputMgr::GetMouseButtonDown(Mouse::Button button)
{
	auto it = find(downButtons.begin(), downButtons.end(), button);
	return it != downButtons.end();
}

bool InputMgr::GetMouseButton(Mouse::Button button)
{
	auto it = find(ingButtons.begin(), ingButtons.end(), button);
	return it != ingButtons.end();
}

bool InputMgr::GetMouseButtonUp(Mouse::Button button)
{
	auto it = find(upButtons.begin(), upButtons.end(), button);
	return it != upButtons.end();
}