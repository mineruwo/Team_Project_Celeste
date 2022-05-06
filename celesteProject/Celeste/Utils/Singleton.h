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
	// �������� �� ��ü�� ȣ��� �� 
	static T& GetInstance() noexcept
	{
		static T instance;
		return instance;
	}
};