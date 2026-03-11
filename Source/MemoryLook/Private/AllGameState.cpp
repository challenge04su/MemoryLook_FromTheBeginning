#include "AllGameState.h"

AAllGameState::AAllGameState()
{
	FinalPassword.Reserve(3);
}

void AAllGameState::BeginPlay()
{
	Super::BeginPlay();

	GenerateRandomPassword();
}

void AAllGameState::GenerateRandomPassword()
{
	FinalPassword.Empty();

    for (int32 i = 0; i < 3; i++)
    {
        FPasswordDigit NewDigit;

        // 숫자 중복 가능: 0~9 사이 랜덤
        NewDigit.Value = FMath::RandRange(0, 9);

        // 색상 중복 가능: Enum 범위 내 랜덤
        uint8 RandomColorIndex = (uint8)FMath::RandRange(0, 6);
        NewDigit.Color = static_cast<EPasswordColor>(RandomColorIndex);

        FinalPassword.Add(NewDigit);

        // 디버그 로그로 생성된 정답 확인
        UE_LOG(LogTemp, Warning, TEXT("Digit %d: Value[%d], ColorIndex[%d]"), i + 1, NewDigit.Value, RandomColorIndex);
    }
}