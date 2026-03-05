#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ParticipantController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class MEMORYLOOK_API AParticipantController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AParticipantController();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RunAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ToggleProneAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* PickupAction;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DropAction;
};
