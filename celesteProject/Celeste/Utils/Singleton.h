#pragma once

template <typename T>
class Singleton
{
public:
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton& operator=(Singleton&&) = delete;
protected:
	Singleton() noexcept = default;
	virtual ~Singleton() = default;
public:
	// 정적으로 이 객체가 호출될 때 
	static T& GetInstance() noexcept
	{
		static T instance;
		return instance;
	}
};