#include "pch.h"
#include <cmath>
#include "TrailingCircle.h"
#include "utils.h"

Trail::Trail(float radius, float decrement, Color4f color, Point2f center)
	: radius { radius }
	, decrement { decrement }
	, color { color }
	, center { center }
{
}

void Trail::Update(float deltaTime)
{
	if (radius > 1.0f) radius -= (decrement + 30.0f) * deltaTime;
	else radius = 1.0f;

	if (color.a > 0.01f) color.a -= decrement * deltaTime;
	else color.a = 0.01f;
}

TrailingCircle::TrailingCircle( float radius, const Point2f& center )
	: m_Radius{ radius } 
	, m_Center{center}
	, m_Color{ GetRandomColor() }
	, m_Velocity(GetRandomVelocity() )
{
}

void TrailingCircle::Update( float elapsedSec, const Rectf& boundingRect )
{
	// Calculate new position
	Vector2f centerVector{ m_Center };
	centerVector += m_Velocity * elapsedSec;
	m_Center = centerVector.ToPoint2f( );

	// Handle reflection against bounding rectangle
	if ( m_Velocity.x > 0 && m_Center.x + m_Radius > boundingRect.left + boundingRect.width )
	{
		m_Velocity.x = -m_Velocity.x;
	}
	else if ( m_Velocity.x < 0 && m_Center.x - m_Radius < boundingRect.left )
	{
		m_Velocity.x = -m_Velocity.x;
	}
	if ( m_Velocity.y > 0 && m_Center.y + m_Radius > boundingRect.bottom + boundingRect.height )
	{
		m_Velocity.y = -m_Velocity.y;
	}
	else if ( m_Velocity.y < 0 && m_Center.y - m_Radius < boundingRect.bottom )
	{
		m_Velocity.y = -m_Velocity.y;
	}

	// Update trails
	m_ElapsedTime += elapsedSec;
	if (m_ElapsedTime >= m_TrailSaveTime)
	{
		while (m_pTrails.size() >= m_MaxTrails)
		{
			m_pTrails.pop_front();
		}

		m_pTrails.push_back(new Trail(m_Radius, 1.0f, m_Color, m_Center));
		m_ElapsedTime = 0.0f;
	}

	UpdateTrails(elapsedSec);
}

void TrailingCircle::Draw( ) const
{
	utils::SetColor( m_Color );
	utils::FillEllipse( m_Center, m_Radius, m_Radius );

	for (Trail* element : m_pTrails)
	{
		utils::SetColor(element->color);
		utils::FillEllipse(element->center, element->radius, element->radius);
	}
}

Vector2f TrailingCircle::GetRandomVelocity( )
{
	const int speedMin{ 50 };
	const int speedMax{ 100 };
	int speed{ rand( ) % ( speedMax - speedMin + 1 ) + speedMin };
	float angle{ rand( ) % 360 * float(utils::g_Pi / 360) };
	return Vector2f{ speed * cos( angle ) , speed * sin( angle ) };
}

Color4f TrailingCircle::GetRandomColor( )
{
	return Color4f{ rand( ) % 256 / 256.0f, rand( ) % 256 / 256.0f, rand( ) % 256 / 256.0f, 1.0f };
}

void TrailingCircle::UpdateTrails(float deltaTime)
{
	for (Trail* element : m_pTrails)
	{
		element->Update(deltaTime);
	}
}
