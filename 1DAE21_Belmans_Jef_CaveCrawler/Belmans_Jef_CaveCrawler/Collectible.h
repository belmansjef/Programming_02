#pragma once
class Texture;

class Collectible final
{
public:
	enum class Type 
	{  
		points = 1, 
		health = 2	
	};

	explicit Collectible(const Point2f& leftBottom, Collectible::Type type );
	~Collectible();
	Collectible(const Collectible&) = delete;
	Collectible& operator=(const Collectible&) = delete;
	Collectible(Collectible&&) = delete;
	Collectible& operator=(Collectible&&) = delete;

	void Draw( ) const;
	bool IsOverlapping(const Rectf& actorShape) const;

private:
	const Type m_Type;
	const Texture* m_pTexture;

	Rectf m_Shape;
};