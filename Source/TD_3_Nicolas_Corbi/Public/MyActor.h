#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Damageable.h"
#include "MyActor.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API AMyActor : public AActor, public IDamageable
{
	GENERATED_BODY()
	
protected:
	AMyActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void TakeDamage_Implementation(float Amount) override;
};
