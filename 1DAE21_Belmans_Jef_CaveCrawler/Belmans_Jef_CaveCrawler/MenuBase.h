#pragma once
#include <vector>
#include "structs.h"

class Game;
class Button;
class Texture;
class MenuBase
{
public:
	MenuBase(const std::string& titleText, const int fontSize, const Window& window, const Rectf& buttonPanel = {});
	virtual ~MenuBase();

	MenuBase(const MenuBase& other) = delete;
	MenuBase& operator= (const MenuBase& other) = delete;
	MenuBase(MenuBase&& other) = delete;
	MenuBase& operator= (MenuBase&& other) = delete;

	virtual void Draw() const;
	virtual void Enter(Game& game) = 0;

	void CycleSelection(bool up);
	void Close();
	void Open();

protected:

	Button* m_pHighlightedButton;
	void AddButton(Button* btn);
	void FitButtonsToPanel();

private:
	bool m_IsActive;
	int m_ActiveButtonIdx;

	Texture* m_pTitleText;
	Point2f m_TitleTextPos;

	std::vector<Button*> m_pButtons;
	Rectf m_ButtonPanel;
};

