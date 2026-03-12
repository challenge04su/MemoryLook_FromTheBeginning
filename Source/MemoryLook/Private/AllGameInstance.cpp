#include "AllGameInstance.h"
#include "Internationalization/Regex.h"

void UAllGameInstance::SetPlayerName(FString InName)
{
	// Replace 함수를 사용하여 모든 공백(" ")을 빈 문자열("")로 치환
	SavedPlayerName = InName.Replace(TEXT(" "), TEXT(""));

	UE_LOG(LogTemp, Warning, TEXT("Player Name Saved: %s"), *SavedPlayerName);
}

bool UAllGameInstance::CheckNameValidity(FString InName, FString& OutMessage)
{
	// 공백 및 빈 칸 체크
	// 앞뒤 공백을 제거한 후 비어있는지 확인
	FString TrimmedName = InName.TrimStartAndEnd();
	if (TrimmedName.IsEmpty())
	{
		OutMessage = TEXT("이름을 입력해주세요!");
		return false;
	}

	// 길이 체크 (10자 이내)
	if (InName.Len() > 10)
	{
		OutMessage = TEXT("이름은 10자 이내여야 합니다.");
		return false;
	}

	// 한글 사용 불가 및 특수기호/숫자/영어 허용 체크
	// 정규식 설명: ^(시작) [영어대소문자, 숫자, 지정된 특수문자] 가 1개 이상 존재하며 $(끝)
	// 이 식에 걸리지 않으면 한글이나 공백이 포함된 것으로 간주
	FRegexPattern Pattern(TEXT("^[a-zA-Z0-9!@#$%^&*()_+-=]+$"));
	FRegexMatcher Matcher(Pattern, InName);

	if (!Matcher.FindNext())
	{
		OutMessage = TEXT("한글이나 공백은 사용할 수 없습니다.");
		return false;
	}

	// 모든 검사 통과
	OutMessage = TEXT("");
	return true;
}