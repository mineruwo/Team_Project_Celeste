#pragma once
#include "AnimationClip.h"
#include <map>
#include <queue>

using namespace sf;

class AnimationController
{
private:
	std::map<std::string, AnimationClip> clips;
	std::queue<std::string> playQueue; //담아둠

	AnimationClip *currentClip; // 현재 재생되는 클립
	bool isPlaying; // 애니메이션 여부
	int currentFrame;
	int totalFrame; // 총 프레임 갯수
	float frameDurtion; // 1프레임 간격에 대한 시간

	float speed;

	float ContolSpeed;
	float accumTime;

	Sprite *sprite;

public:
	AnimationController();

	void SetTarget(Sprite *sprite);
	void AddClip(const AnimationClip &newClip);

	void Update(float dt);

	void Play(std::string clipId, bool clear = true); //claer : 큐를 비울지 아닐지
	void PlayQueue(std::string clipId);

	void Stop();

	float GetSpeed();
	void SetSpeed(float speed);

	void ClearPlayQueue();

	bool IsPlaying();
};

