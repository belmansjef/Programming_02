#pragma once

class Texture;
class Collectible final
{
public:
	enum class CollectibleType 
	{  
		points = 1, 
		health = 2	
	};

	explicit Collectible(const Point2f& leftBottom, Collectible::CollectibleType type );
	~Collectible();
	Collectible(const Collectible&) = delete;
	Collectible& operator=(const Collectible&) = delete;
	Collectible(Collectible&&) = delete;
	Collectible& operator=(Collectible&&) = delete;

	CollectibleType GetType() const;
	bool GetIsPickedUp() const;
	void SetIsPickedUp(bool isPickedUp);

	void Draw() const;
	bool IsOverlapping(const Rectf& actorShape) const;

private:
	const CollectibleType m_Type;
	const Texture* m_pTexture;
	Rectf m_Shape;

	bool m_IsPickedUp;
};