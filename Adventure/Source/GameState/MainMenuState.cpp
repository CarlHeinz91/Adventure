#include "stdafx.h"
#include "Source\GameState\MainMenuState.hpp"

namespace GameState
{
	MainMenuState::~MainMenuState()
	{

	}

	void MainMenuState::update(sf::Time const & frametime, sf::RenderWindow* renderWindow)
	{
		mMainMenu.update(frametime, renderWindow);
	}

	void MainMenuState::render(sf::RenderWindow* renderWindow)
	{
		mMainMenu.render(renderWindow);
	}

	GameStateChange MainMenuState::pollGameStateChange()
	{
		if (!mCloseMainMenu)
		{
			switch (mMainMenu.mOutgoingEvent)
			{
			case MainMenu::OutgoingEvent::NO_EVENT:
				return GameStateChange::NO_CHANGE;
				break;
			case MainMenu::OutgoingEvent::START_GAME:
				return GameStateChange::REPLACE_PLAYING_STATE;
				break;
			case MainMenu::OutgoingEvent::START_EDITOR:
				return GameStateChange::REPLACE_EDITOR_STATE;
				break;
			case MainMenu::OutgoingEvent::EXIT:
				return GameStateChange::POP;
				break;
			}
		}
		else
		{
			return GameStateChange::POP;
		}
	}

	void MainMenuState::reactOnESC()
	{
		mCloseMainMenu = true;
	}

}

