#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MpCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class HW07_API AMpCharacter : public APawn
{
	GENERATED_BODY()

public:
	AMpCharacter();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float MultipleRunSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Move")
	float TotalRunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Look")
	float LookSensitivity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float CharacterRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fly")
	float FlySpeed;


	bool IsFly;
	float NowSpeed;
	float NowGravity;
	float HalfLength;
	float SumGravitySpeed;
	float UpVactorValue;

	void Move(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void EndSprint(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void UpDawnLook(const FInputActionValue& Value);
	void Fly(const FInputActionValue& Value);
	void FlyBool(const FInputActionValue& Value);
	void Gravity();
	bool IsGround();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};