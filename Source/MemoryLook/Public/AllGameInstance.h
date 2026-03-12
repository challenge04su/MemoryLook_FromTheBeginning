#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AllGameInstance.generated.h"

UCLASS()
class MEMORYLOOK_API UAllGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
    // 플레이어 이름을 저장할 변수
    UPROPERTY(BlueprintReadWrite, Category = "PlayerInfo")
    FString SavedPlayerName;

    // 공백을 제거하고 이름을 저장하는 함수
    UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
    void SetPlayerName(FString InName);

    UFUNCTION(BlueprintCallable, Category = "PlayerInfo")
    bool CheckNameValidity(FString InName, FString& OutMessage);
};
