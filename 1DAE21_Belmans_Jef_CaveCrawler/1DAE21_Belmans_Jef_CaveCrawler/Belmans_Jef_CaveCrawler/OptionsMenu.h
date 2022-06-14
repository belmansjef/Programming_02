#pragma once
#include "MenuBase.h"
class OptionsMenu : public MenuBase
{
public:
	OptionsMenu(const Point2f& bottomLeft, float windowWidth, float windowHeight);
	~OptionsMenu();

	OptionsMenu(const OptionsMenu& other) = delete;
	OptionsMenu& operator=(const OptionsMenu& other) = delete;
	OptionsMenu(OptionsMenu&& other) = delete;
	OptionsMenu& operator=(OptionsMenu&& other) = delete;


	virtual void Draw() const override;
	virtual void Enter(Game& game) override;

private:
	Texture* m_pVolumeText;
	Point2f m_PosVolumeText;

	Button* m_pVolumeUpButton;
	Button* m_pVolumeDownButton;
	Button* m_pMenuButton;

	void ChangeVolume(bool up);
	void SetVolumeText();
};