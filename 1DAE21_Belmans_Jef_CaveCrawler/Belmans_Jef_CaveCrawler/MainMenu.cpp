#include "MainMenu.h"
#include "Game.h"

void MainMenu::Enter(Game* game)
{
	if (m_pHighlightedButton == m_pStartButton)
	{
		game->SetGameState(GameState::InGame);
		Close();
	}
	else if (m_pHighlightedButton == m_pOptionsButton)
	{
		// TODO: open options
	}
	else if (m_pHighlightedButton == m_pExitButton)
	{
		// TODO: exit game
	}
}
