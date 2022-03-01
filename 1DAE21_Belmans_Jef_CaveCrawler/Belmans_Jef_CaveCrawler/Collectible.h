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

	void Draw( ) const;
	bool IsOverlapping(const Rectf& rect ) const;

private:
	const Type m_Type;
	Rectf m_Shape;
	const Texture* m_pTexture;
};


