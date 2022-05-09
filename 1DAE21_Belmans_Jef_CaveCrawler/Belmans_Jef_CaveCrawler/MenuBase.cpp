#include "MenuBase.h"
#include "Button.h"

void MenuBase::Draw() const
{
	for (Button* btn : m_pButtons)
	{
		btn->Draw();
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