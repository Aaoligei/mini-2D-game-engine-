#pragma once
#include"../Object/GameObject.h"
#include<string>

class Character:public GameObject
{
public:
	Character();
	Character(Properties* props):GameObject(props){}

	virtual void Draw() = 0;
	virtual void Clean() = 0;
	virtual void Update(float dt) = 0;

protected:
	std::string m_Name;
};

