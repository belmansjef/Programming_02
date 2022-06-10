#pragma once

enum class CollectibleType;
class Texture;
class ParticleSystem;

class Collectible final
{
public:
	explicit Collectible(const Point2f& leftBottom, CollectibleType type );
	~Collectible();

	Collectible(const Collectible&) = delete;
	Collectible& operator=(const Collectible&) = delete;
	Collectible(Collectible&&) = delete;
	Collectible& operator=(Collectible&&) = delete;

	CollectibleType GetType() const;
	bool GetIsPickedUp() const;
	void SetIsPickedUp(bool value);
	void PickUp();

	void Update();
	void Draw() const;
	bool IsOverlapping(const Rectf& actorShape) const;

private:
	const CollectibleType m_Type;
	const Texture* m_pTexture;
	Rectf m_Shape;
	ParticleSystem* m_pPickUpPS;

	bool m_IsPickedUp;
};