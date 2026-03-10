#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class TD_3_NICOLAS_CORBI_API SMyCompoundWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyCompoundWidget) {}

	SLATE_ARGUMENT(FText, GameTitle)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
};
