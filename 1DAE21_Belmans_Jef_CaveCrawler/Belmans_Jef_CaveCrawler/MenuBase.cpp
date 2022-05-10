#include "pch.h"
#include "MenuBase.h"
#include "Button.h"
#include "Texture.h"
#include "SoundManager.h"

MenuBase::MenuBase(const std::string& titleText, const int fontSize, float windowWidth, float windowHeight, const Rectf& buttonPanel)
	: m_pTitleText { new Texture(titleText, "Resources/Font.ttf", fontSize, Color4f(1.0f, 1.0f, 1.0f, 1.0f))}
	, m_IsActive { false }
	, m_ActiveButtonIdx{ 0 }
	, m_pHighlightedButton { nullptr }
	, m_ButtonPanel { buttonPanel }
{
	m_TitleTextPos = Point2f
	(
		(windowWidth / 2.0f) - m_pTitleText->GetWidth() / 2.0f,
		((windowHeight / 4.0f) * 3.0f) - m_pTitleText->GetHeight() / 2.0f
	);
}
	
MenuBase::~MenuBase()
{
	for (Button* btn : m_pButtons)
	{
		delete btn;
		btn = nullptr;
	} 
	m_pButtons.clear();

	delete m_pTitleText;
	m_pTitleText = nullptr;
	m_pHighlightedButton = nullptr;
}

void MenuBase::Draw() const
{
	if (!m_IsActive) return;

	m_pTitleText->Draw(m_TitleTextPos);
	for (Button* btn : m_pButtons)
	{
		btn->Draw();
	}
}

void MenuBase::Enter(Game& game)
{
	if (m_IsActive)
	{
		SoundManager::GetInstance()->PlaySound(SoundType::enterUI);
	}
}

void MenuBase::CycleSelection(bool up)
{
	if (m_IsActive)
	{
		SoundManager::GetInstance()->PlaySound(SoundType::selectUI);
		m_pHighlightedButton->SetHighlighted(false);

		up ? --m_ActiveButtonIdx : ++m_ActiveButtonIdx;
		m_ActiveButtonIdx = ((m_ActiveButtonIdx + int(m_pButtons.size())) % int(m_pButtons.size()));
		m_pHighlightedButton = m_pButtons[m_ActiveButtonIdx];
		m_pHighlightedButton->SetHighlighted(true);
	}
}

void MenuBase::Close()
{
	m_IsActive = false;
}

void MenuBase::Open()
{
	m_IsActive = true;
}

Button* MenuBase::GetHighlightedButton() const
{
	return m_pHighlightedButton;
}

void MenuBase::AddButton(Button* btn)
{
	if (m_pButtons.size() == 0)
	{
		m_pHighlightedButton = btn;
		btn->SetHighlighted(true);
	}
	m_pButtons.push_back(btn);
}

void MenuBase::FitButtonsToPanel()
{
	const int padding{ 20 };
	for (size_t i = 0; i < m_pButtons.size(); i++)
	{
		const Point2f newPos
		{
			m_ButtonPanel.left,
			(m_ButtonPanel.bottom + m_ButtonPanel.height) - ((m_pButtons[i]->GetHeight() + padding )* i)
		};
		m_pButtons[i]->Reposition(newPos);
	}
}

bool MenuBase::IsActive() const
{
	return m_IsActive;
}
