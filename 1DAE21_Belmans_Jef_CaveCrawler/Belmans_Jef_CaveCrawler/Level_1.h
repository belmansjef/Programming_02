#pragma once
#include "Level.h"

class Level_1 final : public Level
{
public:
	Level_1();
	~Level_1();

	Level_1(const Level_1& other) = delete;
	Level_1& operator=(const Level_1& other) = delete;
	Level_1(Level_1&& other) = delete;
	Level_1& operator=(Level_1&& other) = delete;

	virtual void DrawLevel() const override;
	virtual void Update() override;
private:

};

