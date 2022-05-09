// Fill out your copyright notice in the Description page of Project Settings.

#include "Survivor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"

#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"

#include "Camera/CameraComponent.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "WidgetHUD.h"
#include "SurvRunMode.h"


// Sets default values
ASurvivor::ASurvivor(): m_health(100.f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springCamComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springCam"));
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	springCamComp->SetupAttachment(RootComponent);
	springCamComp->TargetArmLength = 1.f;

	cameraComp->SetupAttachment(springCamComp, USpringArmComponent::SocketName);

}

// Called when the game starts or when spawned
void ASurvivor::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ASurvivor::BeginPlay"));

	OnTakeAnyDamage.AddDynamic(this, &ASurvivor::ApplyDamage);

	auto survMode = Cast<ASurvRunMode>(GetWorld()->GetAuthGameMode());
	if (survMode)
		m_playerDeadDeleg.BindUFunction(survMode, "playerDeath");
	if (!m_playerDeadDeleg.IsBound())
		SLOG(TEXT("Player death delegate isn\'t bound"));
}

// Called every frame
void ASurvivor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASurvivor::SetupPlayerInputComponent(UInputComponent* pic)
{
	Super::SetupPlayerInputComponent(pic);

	pic->BindAxis("Move Forward / Backward", this, &ASurvivor::forward);
	pic->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);

	pic->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	
	GetCharacterMovement()->AirControl = 15.5f;
	GetCharacterMovement()->MaxWalkSpeed *= 2.f;

}

void ASurvivor::forward(float scale)
{
	FRotator rotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	AddMovementInput(FVector(FRotationMatrix(rotation).GetUnitAxis(EAxis::X)), scale);
}

float ASurvivor::health()
{
	return m_health;
}

void ASurvivor::healup(float hp)
{
	m_health = FMath::Min(m_health + hp, 100.f);
	//m_health = FGenericPlatformMath::Min<float>(m_health + hp, 100.f);
}

void ASurvivor::ApplyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	m_health -= Damage;
	if (m_health <= 0.f)
	{
		m_playerDeadDeleg.ExecuteIfBound(this);
	}
}

void ASurvivor::speedup()
{
	GetCharacterMovement()->MaxWalkSpeed *= 1.5f;
	GetWorld()->GetTimerManager().SetTimer(m_boostTimer, [&]() {GetCharacterMovement()->MaxWalkSpeed /= 1.5f; }, 5.f, false, 5.f);
}
