#include "InputMgr.h"
#include <algorithm>
#include <iostream>
#include <cmath>

map<Axis, AxisInfo> InputMgr::mapAxis;

list<Keyboard::Key> InputMgr::downKeys;
list<Keyboard::Key> InputMgr::ingKeys;
list<Keyboard::Key> InputMgr::upKeys;

void InputMgr::Init()
{
	mapAxis.clear();
	HorInit();
	VerInit();
	Jump();
	Dash();
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
void InputMgr::Jump()
{
	AxisInfo info;
	info.axis = Axis::Jump;
	info.sensi = 2.f;
	info.value = 0.f;
	info.limit = 0.05f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::C);
	mapAxis[info.axis] = info;
}
void InputMgr::Dash()
{
	AxisInfo info;
	info.axis = Axis::Dash;
	info.sensi = 2.f;
	info.value = 0.f;
	info.limit = 0.05f;
	info.positiveKeys.clear();
	info.positiveKeys.push_back(Keyboard::X);
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
	 Ű���� ��������
==========================*/
bool InputMgr::GetKeyDown(Keyboard::Key key)
{
	auto it = find(downKeys.begin(), downKeys.end(), key);
	return it != downKeys.end();
}
/*========================
	Ű���� ������ ���϶�
==========================*/
bool InputMgr::GetKey(Keyboard::Key key)
{
	auto it = find(ingKeys.begin(), ingKeys.end(), key);
	return it != ingKeys.end();
}
/*========================
	 Ű���带 ������
==========================*/
bool InputMgr::GetKeyUp(Keyboard::Key key)
{
	auto it = find(upKeys.begin(), upKeys.end(), key);
	return it != upKeys.end();
}

