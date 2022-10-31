#pragma once

class ResultGround final : public ModelBase, public Component
{
public:
	ResultGround();
	~ResultGround();

	void Start()override;
	void Update()override;
	void Draw()override;
private:
	float m_rotate;
};