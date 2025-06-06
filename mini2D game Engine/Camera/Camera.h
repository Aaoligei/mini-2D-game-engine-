#pragma once
#include"../Physics/Vector2D.h"
#include<SDL.h>
#include "../core/Engine.h"
class Camera
{
public:
	inline static Camera* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();
	}

	inline SDL_Rect GetViewBox() const {
		return m_ViewBox;
	}
	inline  Vector2D GetPosition() const {
		return m_Position;
	}
	inline void SetTarget(Point* target) {
		m_Target = target;
	}

	void Update(float dt);

private:
	Camera() { m_ViewBox = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; }
	Point* m_Target;
	Vector2D m_Position;

	SDL_Rect m_ViewBox;

	static Camera* s_Instance;
};

