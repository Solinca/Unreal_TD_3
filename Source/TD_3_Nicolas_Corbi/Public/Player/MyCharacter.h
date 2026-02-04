#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	AMyCharacter();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UCameraComponent> Camera = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USpringArmComponent> SpringArm = nullptr;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnHealthChanged();

public:
	UFUNCTION(Server, Reliable)
	void TryAttack();

	UPROPERTY(ReplicatedUsing = OnHealthChanged)
	int Health = 100;
};
