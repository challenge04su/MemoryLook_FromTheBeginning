#include "StartScreenWidget.h"
#include "AllGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void UStartScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 버튼 클릭 이벤트와 함수 연결 (AddDynamic)
	if (Btn_Enter)
	{
		Btn_Enter->OnClicked.AddDynamic(this, &UStartScreenWidget::OnEnterButtonClicked);
	}
}

void UStartScreenWidget::OnEnterButtonClicked()
{
    if (!InputName || !Txt_Warning) return;

    FString UserInput = InputName->GetText().ToString();
    FString WarningMsg;

    UAllGameInstance* GI = Cast<UAllGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
    if (!GI) return;

    // 유효성 검사 실행
    if (GI->CheckNameValidity(UserInput, WarningMsg))
    {
        // [성공] 타이머가 돌아가고 있었다면 중지
        GetWorld()->GetTimerManager().ClearTimer(WarningTimerHandle);
        Txt_Warning->SetText(FText::GetEmpty());

        // 이름 저장 및 레벨 이동
        GI->SetPlayerName(UserInput);
        UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
    }
    else
    {
        // [실패] 경고 메시지 출력
        Txt_Warning->SetText(FText::FromString(WarningMsg));

        // 기존에 돌아가던 타이머가 있다면 초기화 (시간 연장 효과)
        GetWorld()->GetTimerManager().ClearTimer(WarningTimerHandle);

        // 3초 뒤에 ClearWarningMessage 함수 호출
        GetWorld()->GetTimerManager().SetTimer(
            WarningTimerHandle,
            this,
            &UStartScreenWidget::ClearWarningMessage,
            3.0f,
            false
        );
    }
}

void UStartScreenWidget::ClearWarningMessage()
{
    if (Txt_Warning)
    {
        Txt_Warning->SetText(FText::GetEmpty());
    }
}