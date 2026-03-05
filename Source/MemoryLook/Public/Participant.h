#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Participant.generated.h"

class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class MEMORYLOOK_API AParticipant : public ACharacter
{
	GENERATED_BODY()

public:
	AParticipant();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera") USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera") UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float NormalSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float RunSpeedMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") float RunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement") bool bIsProning;

	UFUNCTION() void Move(const FInputActionValue& value);
	UFUNCTION() void StartJump(const FInputActionValue& value);
	UFUNCTION() void StopJump(const FInputActionValue& value);
	UFUNCTION() void Look(const FInputActionValue& value);
	UFUNCTION() void StartRun(const FInputActionValue& value);
	UFUNCTION() void StopRun(const FInputActionValue& value);
	UFUNCTION() void ToggleProne(const FInputActionValue& value);
	UFUNCTION() void Pickup(const FInputActionValue& value);
	UFUNCTION() void Drop(const FInputActionValue& value);
};
