#pragma once
#include <string>
class HUD;

class ScoreManager
{
public:
	ScoreManager(HUD& hud);

	int GetCurrentScore() const;
	int GetHighScore() const;

	void AddScore(int score);
	void ResetScore();

private:
	const std::string m_SaveFilePath;

	HUD& m_Hud;

	int m_CurrentScore;
	int m_HighScore;

	void LoadHighScore();
	void SaveHighScore();
};