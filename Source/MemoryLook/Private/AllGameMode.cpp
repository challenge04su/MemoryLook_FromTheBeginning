#include "AllGameMode.h"
#include "Participant.h"
#include "ParticipantController.h"
#include "AllGameState.h"

AAllGameMode::AAllGameMode()
{
	DefaultPawnClass = AParticipant::StaticClass();
	PlayerControllerClass = AParticipantController::StaticClass();
	GameStateClass = AAllGameState::StaticClass();
}
