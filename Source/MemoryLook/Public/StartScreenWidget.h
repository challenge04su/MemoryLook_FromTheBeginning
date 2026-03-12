#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "StartScreenWidget.generated.h"


UCLASS()
class MEMORYLOOK_API UStartScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	FTimerHandle WarningTimerHandle;

	// meta = (BindWidget)은 WBP 내의 위젯 이름과 변수명을 매칭시켜줍니다.
	UPROPERTY(meta = (BindWidget))
	UEditableText* InputName;

	UPROPERTY(meta = (BindWidget))
	UButton* Btn_Enter;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Txt_Warning;

	// 위젯이 생성될 때 실행되는 초기화 함수 (BeginPlay와 유사)
	virtual void NativeConstruct() override;

	// 버튼 클릭 시 실행될 함수
	UFUNCTION()
	void OnEnterButtonClicked();

	void ClearWarningMessage();
};
