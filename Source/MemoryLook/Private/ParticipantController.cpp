#include "ParticipantController.h"
#include "EnhancedInputSubsystems.h"

AParticipantController::AParticipantController() :
	InputMappingContext(nullptr),
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	RunAction(nullptr),
	ToggleProneAction(nullptr),
	PickupAction(nullptr),
	DropAction(nullptr)
{

}

void AParticipantController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	if (PlayerCameraManager)
	{
		// 위를 볼 때의 제한 (최대 60도)
		PlayerCameraManager->ViewPitchMax = 60.0f;
		// 아래를 볼 때의 제한 (최소 -60도)
		PlayerCameraManager->ViewPitchMin = -60.0f;
	}
}