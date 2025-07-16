#include "MPCharacter.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


AMpCharacter::AMpCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	IsFly = false;
	MoveSpeed = 500.0f;
	NowSpeed = MoveSpeed;
	MultipleRunSpeed = 1.7f;
	TotalRunSpeed = MoveSpeed * MultipleRunSpeed;
	LookSensitivity = 300.0f;
	NowGravity = 0.0f;
	CharacterRotation = 5.0f;
	SumGravitySpeed = 0.0f;
	UpVactorValue = 0.0f;
	FlySpeed = MoveSpeed * 1.4f;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetSimulatePhysics(false);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->TargetArmLength = 350.f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
	SkeletalMeshComponent->SetSimulatePhysics(false);

	HalfLength = CapsuleComponent->GetScaledCapsuleHalfHeight();
}

void AMpCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInput is Completed"));
		if (AMyPlayerController* PlayerController = Cast< AMyPlayerController>(GetController()))
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayerController is Completed"));

			if (PlayerController->MoveAction)
			{
				UE_LOG(LogTemp, Warning, TEXT("MoveAction is Completed"));
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMpCharacter::Move
				);
			}
			if (PlayerController->JumpAction)
			{
				UE_LOG(LogTemp, Warning, TEXT("JumpAction is Completed"));
				EnhancedInput->BindAction(
					PlayerController->JumpAction,
					ETriggerEvent::Triggered,
					this,
					&AMpCharacter::Jump
				);
			}
			if (PlayerController->SprintAction)
			{
				UE_LOG(LogTemp, Warning, TEXT("SprintAction is Completed"));
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&AMpCharacter::StartSprint
				);
			}
			if (PlayerController->SprintAction)
			{
				UE_LOG(LogTemp, Warning, TEXT("SprintAction is End"));
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&AMpCharacter::EndSprint
				);
			}
			if (PlayerController->LookAction)
			{
				UE_LOG(LogTemp, Warning, TEXT("LookAction is Completed"));
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMpCharacter::Look
				);
			}
			if (PlayerController->BoolAction)
			{
				UE_LOG(LogTemp, Warning, TEXT("Bool is Changed"));
				EnhancedInput->BindAction(
					PlayerController->BoolAction,
					ETriggerEvent::Completed,
					this,
					&AMpCharacter::FlyBool
				);
			}
			if (PlayerController->WheelAction)
			{
				UE_LOG(LogTemp, Warning, TEXT("Look Up n Dawn"));
				EnhancedInput->BindAction(
					PlayerController->WheelAction,
					ETriggerEvent::Triggered,
					this,
					&AMpCharacter::UpDawnLook
				);
			}
			if (PlayerController->FlyAction)
			{
				UE_LOG(LogTemp, Warning, TEXT("Look Up n Dawn"));
				EnhancedInput->BindAction(
					PlayerController->FlyAction,
					ETriggerEvent::Triggered,
					this,
					&AMpCharacter::Fly
				);
			}
		}
	}
}

void AMpCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) return;
	const FVector2D MoveInput = Value.Get<FVector2D>();

	//FVector GoVector = (GetActorRightVector() * MoveInput.Y )+( GetActorForwardVector() * MoveInput.X); >> ÀÌ·¯¸é ¾È µÊ
	FVector GoVector(MoveInput.X, MoveInput.Y, 0.0f); // by Àç¿ì´Ô

	if (!FMath::IsNearlyZero(MoveInput.X) || !FMath::IsNearlyZero(MoveInput.Y))
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		AddActorLocalOffset(GoVector * NowSpeed * DeltaTime , true);
	}
}

void AMpCharacter::Jump(const FInputActionValue& Value)
{
	if (!Controller || !IsGround()) return;
	bool JumpInput = Value.Get<bool>();
	if (JumpInput)
	{
		UpVactorValue = 600.0f;
	}
}

void AMpCharacter::StartSprint(const FInputActionValue& Value)
{
	if (NowSpeed != TotalRunSpeed && Controller)
	{
		NowSpeed = TotalRunSpeed;
	}
}

void AMpCharacter::EndSprint(const FInputActionValue& Value)
{
	if (NowSpeed != MoveSpeed && Controller)
	{
		NowSpeed = MoveSpeed;
	}
}

void AMpCharacter::Look(const FInputActionValue& Value)
{
	if (!Controller) return;
	FVector2D LookInput = Value.Get<FVector2D>();
	LookInput *= LookSensitivity;

	FRotator NowRotation = Controller->GetControlRotation();//

	NowRotation.Roll += 0.0f;

	NowRotation.Pitch += LookInput.Y;

	NowRotation.Yaw += LookInput.X;

	Controller->SetControlRotation(NowRotation);

	CapsuleComponent->SetWorldRotation(FRotator(0.0f, NowRotation.Yaw, 0.0f));
}

void AMpCharacter::UpDawnLook(const FInputActionValue& Value)
{
	if (!Controller) return;

	float LookInput = Value.Get<float>();

	FRotator NowRotation = Controller->GetControlRotation();

	NowRotation.Roll += LookInput* LookSensitivity;

	Controller->SetControlRotation(NowRotation);
}

void AMpCharacter::Fly(const FInputActionValue& Value)
{
	if (!Controller) return;
	if (!IsFly) return;
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	AddActorLocalOffset(FVector(0.0f,0.0f,FlySpeed*DeltaTime));
	UpVactorValue = 200.0f;
	FlySpeed = 200.0f;
}

void AMpCharacter::FlyBool(const FInputActionValue& Value)
{
	if(IsFly == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("IsFly False"));
		IsFly = false;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("IsFly True"));
		IsFly = true;
	}
}

bool AMpCharacter::IsGround()
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation()-FVector(0.0f,0.0f, 200.0f);

	FHitResult Hit;
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, Params))
	{
		if (Hit.Distance < HalfLength+60.0f)
		{
			return true;
		}
		return false;
	}
	return false;
}

void AMpCharacter::Gravity()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	if (IsGround())
	{
		SumGravitySpeed = 0.0f;
	}

	if (UpVactorValue > 0.0f)
	{
		UpVactorValue -= 980.0f * DeltaTime;
		SumGravitySpeed = UpVactorValue;
		AddActorLocalOffset(GetActorUpVector() * SumGravitySpeed * DeltaTime, true);
	}
	else
	{
		UpVactorValue = 0.0f;
		SumGravitySpeed -= 980.0f * DeltaTime;
		AddActorLocalOffset(GetActorUpVector() * SumGravitySpeed * DeltaTime, true);
	}
}

void AMpCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Gravity();
}
