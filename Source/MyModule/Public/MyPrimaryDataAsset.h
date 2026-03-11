#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MyPrimaryDataAsset.generated.h"

UENUM(BlueprintType)
enum ESlateStyleType
{
	BRUSH = 0,
	BUTTON = 1,
	FONT = 2,
	COMBO = 3
};

USTRUCT(BlueprintType)
struct FStyleDataInfos
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESlateStyleType> StyleType = BRUSH;

	UPROPERTY(EditAnywhere)
	FString StyleDataString = "";

	UPROPERTY(EditAnywhere, meta = (EditCondition = "StyleType == ESlateStyleType::BRUSH", EditConditionHides))
	FSlateBrush Brush = FSlateBrush();

	UPROPERTY(EditAnywhere, meta = (EditCondition = "StyleType == ESlateStyleType::BUTTON", EditConditionHides))
	FButtonStyle ButtonStyle = FButtonStyle();

	UPROPERTY(EditAnywhere, meta = (EditCondition = "StyleType == ESlateStyleType::FONT", EditConditionHides))
	FSlateFontInfo FontInfo = FSlateFontInfo();

	UPROPERTY(EditAnywhere, meta = (EditCondition = "StyleType == ESlateStyleType::COMBO", EditConditionHides))
	FComboButtonStyle ComboButtonStyle = FComboButtonStyle();
};

UCLASS()
class MYMODULE_API UMyPrimaryDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FStyleDataInfos> Infos;
};
