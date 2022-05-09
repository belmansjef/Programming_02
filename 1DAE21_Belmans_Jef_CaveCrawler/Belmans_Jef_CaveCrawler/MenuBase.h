#pragma once
#include <vector>
#include "structs.h"
#include "Texture.h"

class Button;
class MenuBase
{
public:
	virtual void Draw() const;
	virtual void Enter() = 0;

	void Close();
	void Open();

protected:
	Button* m_pHighlightedButton;

private:
	bool m_IsActive;
	std::vector<Button*> m_pButtons;
};

