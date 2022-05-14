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
	selectUI,
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

enum class SpriteType
{
	player,
	crabEnemy,
	cannonEnemyBase,
	cannonEnemyBarrel,
	damageBlock,
	risingHand
};

enum class CannonOrientation
{
	up,
	down
};