#pragma once
#include <vector>
#include "structs.h"

class Game;
class Button;
class Texture;

class MenuBase
{
public:
	MenuBase(const std::string& titleText, const int fontSize, float windowWidth, float windowHeight, const Rectf& buttonPanel = {});
	virtual ~MenuBase();

	MenuBase(const MenuBase& other) = delete;
	MenuBase& operator= (const MenuBase& other) = delete;
	MenuBase(MenuBase&& other) = delete;
	MenuBase& operator= (MenuBase&& other) = delete;

	virtual void Draw() const;
	virtual void Enter(Game& game);

	void CycleSelection(bool up);
	void Close();
	void Open();

protected:

	Button* GetHighlightedButton() const;

	void AddButton(Button* btn);
	void FitButtonsToPanel();

	bool IsActive() const;

private:
	bool m_IsActive;
	int m_ActiveButtonIdx;

	Texture* m_pTitleText;
	Point2f m_TitleTextPos;

	std::vector<Button*> m_pButtons;
	Button* m_pHighlightedButton;
	Rectf m_ButtonPanel;
};

