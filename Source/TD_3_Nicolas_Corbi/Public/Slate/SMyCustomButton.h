#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class TD_3_NICOLAS_CORBI_API SMyCustomButton : public SCompoundWidget
{
private:
	FText Label;

	FButtonStyle ButtonStyle;

public:
	SLATE_BEGIN_ARGS(SMyCustomButton)
	{
		_FontSize = 24;
		_FontColor = FLinearColor::White;
		_IsBold = true;
	}

	SLATE_ARGUMENT(float, FontSize)
	SLATE_ARGUMENT(FText, ButtonText)
	SLATE_ARGUMENT(FLinearColor, FontColor)
	SLATE_ARGUMENT(bool, IsBold)
	SLATE_ARGUMENT(FButtonStyle, ButtonStyle)

	SLATE_EVENT(FOnClicked, OnButtonClicked)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetLabel(FText NewText)
	{
		Label = NewText;
	}

	void SetButtonStyle(FButtonStyle NewStyle)
	{
		ButtonStyle = NewStyle;
	}
};
