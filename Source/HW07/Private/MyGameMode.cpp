#include "MyGameMode.h"
#include "MPCharacter.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = AMpCharacter::StaticClass();//Static이라서 객체생성 안 해줘도 선언가능

	//플레이어 컨트롤러
	PlayerControllerClass = AMyPlayerController::StaticClass();
}