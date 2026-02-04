#include "Player/MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	Camera->SetupAttachment(SpringArm);

	bReplicates = true;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Health = 100;
	}
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, Health);
}

void AMyCharacter::OnHealthChanged()
{
	if (!HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Player %d received damage. Current Health is %d"), GetPlayerState()->GetPlayerId(), Health));
	}
}

void AMyCharacter::TryAttack_Implementation()
{
	TArray<AActor*> OverlappedActors;

	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(this);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	ObjectTypes.Add(UCollisionProfile::Get()->ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Try Attack from Player: %d"), GetPlayerState()->GetPlayerId()));

	if (UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), 500, ObjectTypes, nullptr, ActorsToIgnore, OverlappedActors))
	{
		for (AActor* Actor : OverlappedActors)
		{
			if (AMyCharacter* Char = Cast<AMyCharacter>(Actor))
			{
				Char->Health -= 20;

				if (Char->Health <= 0)
				{
					Char->Destroy();
				}
			}
		}
	}
}
