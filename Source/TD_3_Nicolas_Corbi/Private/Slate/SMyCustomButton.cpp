#include "Slate/SMyCustomButton.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMyCustomButton::Construct(const FArguments& InArgs)
{
	FSlateFontInfo FontInfo = FAppStyle::GetFontStyle(InArgs._IsBold ? "NormalFontBold" : "");

	FontInfo.Size = InArgs._FontSize;

	Label = InArgs._ButtonText;

	ChildSlot
	[
		SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked(InArgs._OnButtonClicked)
			[
				SNew(STextBlock)
					.Text_Lambda([this]() -> FText { return Label; })
					.ColorAndOpacity(InArgs._FontColor)
					.Font(FontInfo)
			]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
