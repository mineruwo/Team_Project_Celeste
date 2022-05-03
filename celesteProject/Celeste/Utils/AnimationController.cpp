#include "AnimationController.h"

AnimationController::AnimationController()
	:clips(),
	currentClip(nullptr),
	isPlaying(false),
	currentFrame(-1),
	totalFrame(0),
	frameDurtion(0.f),
	accumTime(0.f),
	sprite(nullptr),
	speed(1.f)
{
}

void AnimationController::SetTarget(Sprite *sprite)
{
	this->sprite = sprite;
}

void AnimationController::AddClip(const AnimationClip &newClip)
{
	if (clips.find(newClip.id) == clips.end())
	{
		clips[newClip.id] = newClip;
	}
	else
	{

	}
}

void AnimationController::Update(float dt)
{
	if (!isPlaying)
		return;

	accumTime += dt * speed;
	if (accumTime < frameDurtion)
		return;

	accumTime = 0.f;
	++currentFrame;
	if (currentFrame >= totalFrame)
	{
		if (playQueue.empty()) //q에 아무것도 없을때
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				break;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;
				break;
			default:
				break;
			}
		}
		else
		{
			std::string nextClipId = playQueue.front(); //q 제일 앞에 있는 걸 이용
			playQueue.pop();
			Play(nextClipId, false); //새로운 애니메이션을 넣음 , false : q를 날리지 않기 위해
		}
	}
	sprite->setTexture(currentClip->frames[currentFrame].texture);
	sprite->setTextureRect(currentClip->frames[currentFrame].texCoord);

}

void AnimationController::Play(std::string clipId, bool clear)
{
	if (clear)
	{
		ClearPlayQueue();
	}

	isPlaying = true;
	currentClip = &clips[clipId];
	currentFrame = 0;
	totalFrame = currentClip->frames.size();
	frameDurtion = 1.f / currentClip->fps;
}

void AnimationController::PlayQueue(std::string clipId)
{
	isPlaying = true;
	playQueue.push(clipId);
}

void AnimationController::Stop() //정지
{
	isPlaying = false;
	ClearPlayQueue();
}

float AnimationController::GetSpeed()
{
	return speed;
}

void AnimationController::SetSpeed(float speed)
{
	this->speed = speed;
	//frameDurtion = (frameDurtion = 1.f / currentClip->fps)/ speed;
}

void AnimationController::ClearPlayQueue()
{
	while (!playQueue.empty()) //플레이 큐를 비워야 할때
		playQueue.pop();
}

bool AnimationController::IsPlaying()
{
	return isPlaying;
}
