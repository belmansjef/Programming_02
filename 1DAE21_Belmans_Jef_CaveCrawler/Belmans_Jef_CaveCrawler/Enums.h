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
	levelFinish,
	cannonShoot
};

enum class SpriteType
{
	player,
	crabEnemy,
	cannonEnemyBase,
	cannonEnemyBarrel,
	damageBlock,
	risingHand,
	boss
};

enum class CannonOrientation
{
	up,
	down
};

enum class ProjectileType
{
	small,
	big
};

enum class CollectibleType
{
	points = 1,
	health = 2
};

enum class BossState
{
	landed,
	pre_charge,
	charge,
	in_air
};