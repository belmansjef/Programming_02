#include <fstream>
#include "ScoreManager.h"
#include "HUD.h"
#include "FileReader.h"

ScoreManager::ScoreManager(HUD& hud)
	: m_CurrentScore { 0 }
	, m_HighScore { 0 }
	, m_Hud { hud }
	, m_SaveFilePath { "Resources/Saves/Higscore.txt" }
{
	LoadHighScore();
}

int ScoreManager::GetCurrentScore() const
{
	return m_CurrentScore;
}

int ScoreManager::GetHighScore() const
{
	return m_HighScore;
}

void ScoreManager::AddScore(int score)
{
	m_CurrentScore += score;
	m_Hud.UpdateScore(m_CurrentScore);
	if (m_CurrentScore > m_HighScore)
	{
		SaveHighScore();
	}
}

void ScoreManager::ResetScore()
{
	m_CurrentScore = 0;
	m_Hud.UpdateScore(m_CurrentScore);
}

void ScoreManager::LoadHighScore()
{
	std::ifstream file{ m_SaveFilePath };

	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string line;
			std::getline(file, line, '>');

			int highscore{ std::stoi(FileReader::GetAttributeValue("Highscore", line)) };
			m_HighScore = highscore;
		}
	}
}

void ScoreManager::SaveHighScore()
{
	m_HighScore = m_CurrentScore;

	std::ofstream outStream { m_SaveFilePath };
	if (!outStream) 
	{
		std::cout << "Error opening file: " << m_SaveFilePath << std::endl;
		return;
	}

	outStream << "Highscore=\"" << m_HighScore << "\"";
}
