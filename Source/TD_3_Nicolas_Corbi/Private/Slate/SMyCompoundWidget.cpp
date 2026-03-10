#include "Slate/SMyCompoundWidget.h"
#include "SlateOptMacros.h"
#include "Slate/SMyCustomButton.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMyCompoundWidget::Construct(const FArguments& InArgs)
{
	FSlateFontInfo TitleFontInfo = FAppStyle::GetFontStyle("NormalFontBold");

	TitleFontInfo.Size = 48;

	ChildSlot
	[
		SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("WhiteBrush"))
			.BorderBackgroundColor(FLinearColor(0.33f, 0.33f, 0.33f))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Top)
					[
						SNew(STextBlock)
							.Text(InArgs._GameTitle)
							.ColorAndOpacity(FLinearColor(1, 1, 1))
							.Font(TitleFontInfo)
					]
					+ SVerticalBox::Slot()
					[
						SNew(SBox)
							.HeightOverride(256)
							.HAlign(HAlign_Center)
							.VAlign(VAlign_Center)
							[
								SNew(SVerticalBox)
									+ SVerticalBox::Slot()
									.Padding(FMargin(5))
									[
										SNew(SMyCustomButton)
											.ButtonText(INVTEXT("PLAY"))
											.OnButtonClicked_Lambda([]() -> FReply { GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "PLAY CLICKED"); return FReply::Handled(); })
									]
								+ SVerticalBox::Slot()
									.Padding(FMargin(5))
									[
										SNew(SMyCustomButton)
											.ButtonText(INVTEXT("OPTIONS"))
											.OnButtonClicked_Lambda([]() -> FReply { GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "OPTIONS CLICKED"); return FReply::Handled(); })
									]
								+ SVerticalBox::Slot()
									.Padding(FMargin(5))
									[
										SNew(SMyCustomButton)
											.ButtonText(INVTEXT("QUIT"))
											.OnButtonClicked_Lambda([]() -> FReply { GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "QUIT CLICKED"); return FReply::Handled(); })
									]
							]
					]
			]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
