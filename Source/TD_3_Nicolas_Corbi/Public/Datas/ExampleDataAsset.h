#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExampleDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FExampleStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	float FireRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	int MagSize = 6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	bool bIsAutomatic = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	float Range = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	float Damages = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	FName WeaponName = NAME_None;
};

UCLASS(Blueprintable)
class TD_3_NICOLAS_CORBI_API UExampleDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	TObjectPtr<UStaticMesh> StaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	float FireRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	int MagSize = 6;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	bool bIsAutomatic = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	float Range = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Example")
	float Damages = 10.f;
};
