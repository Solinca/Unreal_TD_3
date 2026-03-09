#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MyDeveloperSettings.generated.h"

UCLASS(Config = Game, DefaultConfig)
class TD_3_NICOLAS_CORBI_API UMyDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	virtual FName GetCategoryName() const override { return FName("Project"); };

#ifdef WITH_EDITOR
	virtual FText GetSectionText() const override { return NSLOCTEXT("CustomSettings", "SectionName", "Custom Section"); };

	virtual FText GetSectionDescription() const override { return NSLOCTEXT("CustomSettings", "SectionDescription", "This is my section description"); };
#endif

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Custom Category")
	TSoftObjectPtr<UWorld> LevelToLoadSubsystem = nullptr;
};
