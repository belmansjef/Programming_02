#pragma once

enum class GameState
{
	MainMenu,
	InGame,
	Paused,
	Dead,
	Finished
};

enum class MenuType
{
	Main,
	Options,
	Pause,
	GameOver,
	Finished,
};

enum class SoundType
{
	selectUI = 0,
	enterUI,
	explosion,
	coinPickup,
	healthPickup,
	handRise,
	hitHurt,
	hitWall,
	jump,
	shoot,
	spikeFall,
	levelFinish
};