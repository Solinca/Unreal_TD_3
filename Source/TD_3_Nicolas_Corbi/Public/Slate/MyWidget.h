#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "MyWidget.generated.h"

UCLASS()
class TD_3_NICOLAS_CORBI_API UMyWidget : public UWidget
{
	GENERATED_BODY()

private:
	TSharedPtr<class SMyCustomButton> MyCustomButton = nullptr;
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	virtual void SynchronizeProperties() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
	FText Label;

	UFUNCTION(BlueprintCallable)
	void SetLabel(FText NewLabel);
};
