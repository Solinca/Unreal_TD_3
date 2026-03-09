#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MyWorldSubsystem.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API UMyWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	FTickerDelegate TickDelegate;

	FTSTicker::FDelegateHandle TickHandle;

	bool Tick(float DeltaTime);
	
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};
