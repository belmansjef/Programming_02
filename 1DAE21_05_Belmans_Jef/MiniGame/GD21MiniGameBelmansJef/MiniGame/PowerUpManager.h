#pragma once
#include <vector>
#include "PowerUp.h"
#include "structs.h"

class SoundEffect;
class PowerUpManager final
{
public:
	PowerUpManager( );
	~PowerUpManager( );
	PowerUpManager(const PowerUpManager&) = delete;
	PowerUpManager& operator=(const PowerUpManager&) = delete;
	PowerUpManager(PowerUpManager&&) = delete;
	PowerUpManager& operator=(PowerUpManager&&) = delete;

	PowerUp* AddItem( const Point2f &center, PowerUp::Type type );
	void Update( float elapsedSec );
	void Draw( ) const;

	size_t Size( ) const;
	bool HitItem( const Rectf& rect ) ;

private:

	std::vector<PowerUp*> m_pItems;
	void DeletePowerUp(const PowerUp* powerup);

	SoundEffect* m_pPowerUpSE;
};
