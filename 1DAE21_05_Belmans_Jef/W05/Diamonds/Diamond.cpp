#include "Diamond.h"
#include "Texture.h"
#include "utils.h"
#include "Matrix2x3.h"

Diamond::Diamond(const Point2f startPos)
	: m_StartPos { startPos }
	, m_pTexture{ new Texture("Resources/Images/Diamond.png") }
{
	m_Translation.x = m_StartPos.x;
	m_Translation.y = m_StartPos.y;

	for (Point2f vert : m_TransVertices)
	{
		vert.x += m_Translation.x;
		vert.y += m_Translation.y;
	}
}

Diamond::~Diamond()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Diamond::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Translation.x, m_Translation.y, 0);
	glRotatef(m_Rotation, 0, 0, 1);
	glScalef(m_Scale, m_Scale, 1);
	m_pTexture->Draw();
	glPopMatrix();

	if (m_IsSelected)
	{
		utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		utils::SetColor(Color4f(0.0f, 0.0f, 1.0f, 1.0f));
	}

	utils::DrawPolygon(m_TransVertices, true, 4.0f);
}

void Diamond::Update(float elapsedSec)
{
	
	if (m_IsSelected)
	{
		const Uint8* pKeyStates = SDL_GetKeyboardState(nullptr);

		m_Rotation += (60 * elapsedSec) * (pKeyStates[SDL_SCANCODE_A] - pKeyStates[SDL_SCANCODE_D]);

		m_Scale *= 1 + 3 * elapsedSec * pKeyStates[SDL_SCANCODE_W];
		m_Scale /= 1 + 3 * elapsedSec * pKeyStates[SDL_SCANCODE_S];

		m_Translation.x += 120 * elapsedSec * (pKeyStates[SDL_SCANCODE_RIGHT] - pKeyStates[SDL_SCANCODE_LEFT]);
		m_Translation.y += 120 * elapsedSec * (pKeyStates[SDL_SCANCODE_UP] - pKeyStates[SDL_SCANCODE_DOWN]);
	
		if (pKeyStates[SDL_SCANCODE_R])
		{
			Reset();
		}
	}

	Matrix2x3 matTranslate, matRotate, matScale;
	matTranslate.SetAsTranslate(m_Translation);
	matRotate.SetAsRotate(m_Rotation);
	matScale.SetAsScale(m_Scale);

	Matrix2x3 matWorld{matTranslate * matRotate * matScale};
	m_TransVertices = matWorld.Transform(m_Vertices);
}

void Diamond::CheckIfClicked(Point2f clickPos)
{
	if (utils::IsPointInPolygon(clickPos, m_TransVertices))
	{
		m_IsSelected = !m_IsSelected;
	};
}

void Diamond::Reset()
{
	m_Translation.x = m_StartPos.x;
	m_Translation.y = m_StartPos.y;
	m_Rotation = 0.0f;
	m_Scale = 1.0f;

	m_IsSelected = false;
}
