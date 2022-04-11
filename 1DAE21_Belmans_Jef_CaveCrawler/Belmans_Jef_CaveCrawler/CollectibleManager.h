#pragma once
#include <vector>
#include "structs.h"
#include "Collectible.h"

class CollectibleManager final
{
public:
	CollectibleManager() = default;
	~CollectibleManager();
	CollectibleManager(const CollectibleManager&) = delete;
	CollectibleManager& operator=(const CollectibleManager&) = delete;
	CollectibleManager(CollectibleManager&&) = delete;
	CollectibleManager& operator=(CollectibleManager&&) = delete;

	Collectible* AddItem( const Point2f &bottomL, Collectible::Type type );
	void Draw( ) const;

	size_t Size( ) const;
	bool HitItem( const Rectf& rect ) ;

private:
	std::vector<Collectible*> m_pItems;

	void DeletePowerUp(const Collectible* powerup) const;
};
