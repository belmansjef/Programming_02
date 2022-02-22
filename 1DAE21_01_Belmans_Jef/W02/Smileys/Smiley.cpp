// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
#include "pch.h"
#include "Texture.h"
#include "utils.h"
#include "Smiley.h"

// Static Texture data
Texture* Smiley::m_pSmileyTexture{ nullptr };
float Smiley::m_SmileyDiameter{ 0.0f };
int Smiley::m_InstanceCounter{ 0 };

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn’t been created before( !)
//  - Adapts the instance counter
Smiley::Smiley( const Point2f& position )
	: m_Position { position }
	, m_Velocity { Vector2f(float(rand() % 120 + 60), float(rand() % 120 - 180))}
	, m_IsHighest{ false }
	, m_IsSleeping{ false }
	, m_IsInSafeArea{ false }
{
	m_InstanceCounter++;
	if (m_pSmileyTexture == nullptr)
	{
		m_pSmileyTexture = new Texture("Resources/Smileys.png");
		m_SmileyDiameter = m_pSmileyTexture->GetWidth() / 4.0f;
	}
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley( )
{
	m_InstanceCounter--;
	if (m_InstanceCounter == 0)
	{
		delete m_pSmileyTexture;
		m_pSmileyTexture = nullptr;
	}
}

// Draw
// Draws a part of the image on the window, which part depends on the state of the smiley:
// - If the smiley is sleeping then the sleeping smiley is drawn.
// - If the smiley is at the highest position, then the happy smiley is drawn.
// - If the smiley is not in the safe area, the scary smiley is drawn.
// - If none of the above conditions is met, the neutral smiley should be drawn.
void Smiley::Draw( ) const
{
	const Rectf dstRect
	{
		
	};

	float xOffset{ m_IsSleeping ? 3.0f : m_IsHighest ? 0.0f : m_IsInSafeArea ? 1.0f : 2.0f };
	const Rectf srcRect
	{
		m_SmileyDiameter * xOffset,
		0.0f,
		m_SmileyDiameter,
		m_SmileyDiameter
	};

	glPushMatrix();
		glTranslatef(m_Position.x, m_Position.y, 0);
		m_pSmileyTexture->Draw(dstRect, srcRect);
	glPopMatrix();
	
 }

// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update( float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect )
{
	if (this == nullptr) return;

	if (!m_IsSleeping)
	{
		m_Position += m_Velocity * elapsedSec;
		m_IsInSafeArea = IsInSafeArea(safeRect);

		if (m_Position.x <= 0.0f || m_Position.x + m_SmileyDiameter >= boundingRect.left + boundingRect.width)
		{
			m_Velocity.x = -m_Velocity.x;
		}

		if (m_Position.y <= 0.0f || m_Position.y + m_SmileyDiameter >= boundingRect.bottom + boundingRect.height)
		{
			m_Velocity.y = -m_Velocity.y;
		}
	}
}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley’s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest( const Point2f& pos )
{
	if (utils::GetDistance(pos, m_Position) < m_SmileyDiameter)
	{
		m_IsSleeping = !m_IsSleeping;
	}
}

// IsSleeping
// Getter of the m_IsSleeping data member
bool Smiley::IsSleeping( ) const
{
	return m_IsSleeping; 
}

// GetPosition
// Getter of the m_Position data member
Point2f Smiley::GetPosition( ) const
{
	return m_Position;
}

// SetHighest
// Setter of the m_IsHighest data member
void Smiley::SetHighest( bool isHighest )
{
	m_IsHighest = isHighest;
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed( )
{
	m_Velocity *= 1.05f;
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed( )
{
	m_Velocity /= 1.05f;
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect
bool Smiley::IsInSafeArea( const Rectf& safeRect ) const
{
	return
		m_Position.x > safeRect.left &&
		m_Position.x + m_SmileyDiameter < safeRect.left + safeRect.width &&
		m_Position.y > safeRect.bottom &&
		m_Position.y + m_SmileyDiameter < safeRect.bottom + safeRect.height;
}



