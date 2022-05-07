#pragma once
#include "AnimationClip.h"
#include <map>
#include <queue>

using namespace sf;

class AnimationController
{
private:
	std::map<std::string, AnimationClip> clips;
	std::queue<std::string> playQueue; //��Ƶ�

	AnimationClip *currentClip; // ���� ����Ǵ� Ŭ��
	bool isPlaying; // �ִϸ��̼� ����
	int currentFrame;
	int totalFrame; // �� ������ ����
	float frameDurtion; // 1������ ���ݿ� ���� �ð�

	float speed;

	float ContolSpeed;
	float accumTime;

	Sprite *sprite;

public:
	AnimationController();

	void SetTarget(Sprite *sprite);
	void AddClip(const AnimationClip &newClip);

	void Update(float dt);

	void Play(std::string clipId, bool clear = true); //claer : ť�� ����� �ƴ���
	void PlayQueue(std::string clipId);

	void Stop();

	float GetSpeed();
	void SetSpeed(float speed);

	void ClearPlayQueue();

	bool IsPlaying();
};

