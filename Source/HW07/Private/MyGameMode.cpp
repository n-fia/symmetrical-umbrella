#include "MyGameMode.h"
#include "MPCharacter.h"
#include "MyPlayerController.h"

AMyGameMode::AMyGameMode()
{
	DefaultPawnClass = AMpCharacter::StaticClass();//Static�̶� ��ü���� �� ���൵ ���𰡴�

	//�÷��̾� ��Ʈ�ѷ�
	PlayerControllerClass = AMyPlayerController::StaticClass();
}