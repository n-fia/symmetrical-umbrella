#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class HW07_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AMyPlayerController();
	void BeginPlay();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputAction")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputAction")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputAction")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputAction")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputAction")
	UInputAction* LookAction;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="InputAction")
	UInputAction* FlyAction;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="InputAction")
	UInputAction* BoolAction;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category="InputAction")
	UInputAction* WheelAction;

};
