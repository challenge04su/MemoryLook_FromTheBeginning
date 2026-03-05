#include "AllGameMode.h"
#include "Participant.h"
#include "ParticipantController.h"

AAllGameMode::AAllGameMode()
{
	DefaultPawnClass = AParticipant::StaticClass();
	PlayerControllerClass = AParticipantController::StaticClass();
}