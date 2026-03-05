#include "Participant.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "ParticipantController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AParticipant::AParticipant()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	NormalSpeed = 600.f;
	RunSpeedMultiplier = 1.5f;
	RunSpeed = NormalSpeed * RunSpeedMultiplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	bIsProning = false;
}

void AParticipant::BeginPlay()
{
	Super::BeginPlay();
	
}

void AParticipant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AParticipant::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AParticipantController* PlayerController = Cast<AParticipantController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AParticipant::Move
				);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&AParticipant::StartJump
				);
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Completed,
					this,
					&AParticipant::StopJump
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AParticipant::Look
				);
			}
			if (PlayerController->RunAction)
			{
				EnhancedInput->BindAction(
					PlayerController->RunAction,
					ETriggerEvent::Triggered,
					this,
					&AParticipant::StartRun
				);
				EnhancedInput->BindAction(
					PlayerController->RunAction,
					ETriggerEvent::Completed,
					this,
					&AParticipant::StopRun
				);
			}
			if (PlayerController->ToggleProneAction)
			{
				EnhancedInput->BindAction(
					PlayerController->ToggleProneAction,
					ETriggerEvent::Started,
					this,
					&AParticipant::ToggleProne
				);
			}
			if (PlayerController->PickupAction)
			{
				EnhancedInput->BindAction(
					PlayerController->PickupAction,
					ETriggerEvent::Started,
					this,
					&AParticipant::Pickup
				);
			}
			if (PlayerController->DropAction)
			{
				EnhancedInput->BindAction(
					PlayerController->DropAction,
					ETriggerEvent::Started,
					this,
					&AParticipant::Drop
				);
			}
		}
	}
}

void AParticipant::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void AParticipant::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}

void AParticipant::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void AParticipant::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);

}

void AParticipant::StartRun(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void AParticipant::StopRun(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

void AParticipant::ToggleProne(const FInputActionValue& value)
{
		bIsProning = !bIsProning;

		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (PC->PlayerCameraManager)
			{
				if (bIsProning)
				{
					// 엎드렸을 때: 위아래 회전 거의 차단 (예: -5도 ~ 5도)
					PC->PlayerCameraManager->ViewPitchMin = -5.0f;
					PC->PlayerCameraManager->ViewPitchMax = 5.0f;

					// 캐릭터 이동 및 충돌체 설정 
					GetCapsuleComponent()->SetCapsuleHalfHeight(30.0f);
					GetCharacterMovement()->MaxWalkSpeed = 150.0f;
					UE_LOG(LogTemp, Warning, TEXT("엎드리기"));
				}
				else
				{
					// 일어났을 때: 기본 시야로 복구
					PC->PlayerCameraManager->ViewPitchMin = -60.0f;
					PC->PlayerCameraManager->ViewPitchMax = 60.0f;

					// 캐릭터 이동 및 충돌체 복구 
					GetCapsuleComponent()->SetCapsuleHalfHeight(88.0f);
					GetCharacterMovement()->MaxWalkSpeed = 600.0f;
					UE_LOG(LogTemp, Warning, TEXT("일어나기"));
				}
			}
		}
	
}

void AParticipant::Pickup(const FInputActionValue& value)
{
	// TODO: 라인트레이스를 이용한 아이템 감지 로직 구현 예정
	// TODO: 감지된 아이템을 손 소켓(Hand_Socket)에 부착하는 로직 추가 예정
	UE_LOG(LogTemp, Warning, TEXT("Pickup Action Triggered!")); 
}

void AParticipant::Drop(const FInputActionValue& value)
{
	// TODO: EquippedItem 변수가 유효한지 체크 후 부착 해제
	// TODO: 물리 시뮬레이션(Simulate Physics) 활성화 로직 구현 예정
	 UE_LOG(LogTemp, Warning, TEXT("Drop Action Triggered!"));
}