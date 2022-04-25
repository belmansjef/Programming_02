#pragma once
class Texture;

class PowerUp final
{
public:
	enum class Type 
	{  
		green = 1, 
		brown = 2	
	};

	explicit PowerUp(const Point2f& center, PowerUp::Type type );
	~PowerUp();

	PowerUp(const PowerUp& other);
	PowerUp& operator=(const PowerUp& other) = delete;
	PowerUp(PowerUp&& other) = delete;
	PowerUp& operator=(PowerUp&& other) = delete;

	void Update( float elapsedSec );
	void Draw( ) const;
	bool IsOverlapping(const Rectf& rect ) const;

private:

	const Type m_Type;
	Circlef m_Shape;
	const Texture* m_pTexture;
	Rectf m_TextClip;
	float m_Angle;
	const float m_RotSpeed;	
};


