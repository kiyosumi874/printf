#pragma once

enum class TAG_SCENE
{
	TAG_TITLE,
	TAG_PLAY,
	TAG_CLEAR,
	TAG_OVER,
	TAG_END,

	TAG_NONE
};

enum class MODE
{
	MODE_1P,
	MODE_2P,
	MODE_NONE
};

class Scene
{
public:
	Scene() 
	: m_mode(MODE::MODE_NONE) {}
	Scene(const MODE& mode)
	: m_mode (mode) {}
	virtual ~Scene(){}

	virtual TAG_SCENE Update() = 0;
	virtual void Draw() = 0;

	const MODE& GetMode() const { return m_mode; }
protected:
	const MODE m_mode;
};