#include "pch.h"
#include "MenuBase.h"
#include "Button.h"
#include "Texture.h"
#include "SoundManager.h"
#include "utils.h"

MenuBase::MenuBase(const std::string& titleText, const int fontSize, float windowWidth, float windowHeight, const Point2f& buttonPanelBottomLeft)
	: m_pTitleText { new Texture(titleText, "Resources/Font.ttf", fontSize, Color4f(1.0f, 1.0f, 1.0f, 1.0f))}
	, m_IsActive { false }
	, m_ActiveButtonIdx{ 0 }
	, m_pHighlightedButton { nullptr }
	, m_ButtonPanel { Rectf(buttonPanelBottomLeft.x, buttonPanelBottomLeft.y, 0.0f, 0.0f) }
	, m_ButtonPadding{ 20 }
{
	m_TitleTextPos = Point2f
	(
		(windowWidth / 2.0f) - m_pTitleText->GetWidth() / 2.0f,
		((windowHeight / 4.0f) * 3.0f) - m_pTitleText->GetHeight() / 2.0f
	);

	m_ButtonBackground = Rectf
	(
		m_ButtonPanel.left - m_ButtonPadding / 2.0f,
		m_ButtonPanel.bottom - m_ButtonPadding / 2.0f,
		0.0f,
		0.0f
	);

	m_TitleBackground = Rectf
	(
		m_TitleTextPos.x - m_ButtonPadding / 2.0f,
		m_TitleTextPos.y - m_ButtonPadding / 2.0f,
		m_pTitleText->GetWidth() + m_ButtonPadding,
		m_pTitleText->GetHeight() + m_ButtonPadding
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
	
	utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
	utils::FillRect(m_ButtonBackground);
	utils::FillRect(m_TitleBackground);

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

	m_ButtonPanel.width = btn->GetWidth();
	m_ButtonPanel.height = m_ButtonBackground.height += btn->GetHeight() + m_ButtonPadding;
	m_ButtonBackground.width = m_ButtonPanel.width + m_ButtonPadding;
}

void MenuBase::FitButtonsToPanel()
{
	for (int i = 0; i < m_pButtons.size(); i++)
	{
		const int btnIdx{ int(m_pButtons.size()) - (i + 1) };
		const Point2f newPos
		{
			m_ButtonPanel.left,
			m_ButtonPanel.bottom + ((m_pButtons[btnIdx]->GetHeight() + m_ButtonPadding) * i)
		};
		m_pButtons[btnIdx]->Reposition(newPos);
	}
}

bool MenuBase::IsActive() const
{
	return m_IsActive;
}
