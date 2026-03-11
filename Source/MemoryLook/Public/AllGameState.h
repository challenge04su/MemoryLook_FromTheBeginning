#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AllGameState.generated.h"

// 색상 종류 정의
UENUM(BlueprintType)
enum class EPasswordColor : uint8
{
    Red UMETA(DisplayName = "Red"),
    Orange UMETA(DisplayName = "Orange"),
    Yellow UMETA(DisplayName = "Yellow"),
    Green UMETA(DisplayName = "Green"),
    Blue UMETA(DisplayName = "Blue"),
    Pink UMETA(DisplayName = "Pink"),
    Purple UMETA(DisplayName = "Purple")
};

// 비밀번호 한 자리 데이터 구조
USTRUCT(BlueprintType)
struct FPasswordDigit
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Value = 0; // 0~9 숫자

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPasswordColor Color = EPasswordColor::Red; // 지정된 색상
};

UCLASS()
class MEMORYLOOK_API AAllGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    AAllGameState();

protected:
    virtual void BeginPlay() override;

private:
    // 최종 생성된 비밀번호 3자리 저장 배열
    UPROPERTY(BlueprintReadOnly, Category = "GameLogic", meta = (AllowPrivateAccess = "true"))
    TArray<FPasswordDigit> FinalPassword;

    // 비밀번호 생성 함수
    void GenerateRandomPassword();

public:
    // 다른 액터들이 정답을 확인할 수 있도록 Getter 제공
    UFUNCTION(BlueprintCallable, Category = "GameLogic")
    TArray<FPasswordDigit> GetFinalPassword() const { return FinalPassword; }
};
