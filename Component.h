#pragma once

class Component
{
public:
	Component(){}
	virtual ~Component(){}
	class Object* m_pParent;
	virtual void Start(){}
	virtual void Update(){}
	virtual void Draw(){}
};