#include "CustomSlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FCustomSlateStyle::StyleSet = nullptr;

TStrongObjectPtr<UMyPrimaryDataAsset> FCustomSlateStyle::StyleAsset = nullptr;

void FCustomSlateStyle::Create()
{
	StyleSet = MakeShared<FSlateStyleSet>(FName("MyCustomStyle"));

	StyleAsset = TStrongObjectPtr<UMyPrimaryDataAsset>(LoadObject<UMyPrimaryDataAsset>(nullptr, TEXT("/Game/Datas/DA_CustomSlateStyle.DA_CustomSlateStyle")));

	for (FStyleDataInfos Info : StyleAsset->Infos)
	{
		switch (Info.StyleType)
		{
			case ESlateStyleType::BRUSH:
				StyleSet->Set(FName(Info.StyleDataString), new FSlateBrush(Info.Brush));

				break;

			case ESlateStyleType::BUTTON:
				StyleSet->Set(FName(Info.StyleDataString), Info.ButtonStyle);

				break;

			case ESlateStyleType::FONT:
				StyleSet->Set(FName(Info.StyleDataString), Info.FontInfo);

				break;

			case ESlateStyleType::COMBO:
				StyleSet->Set(FName(Info.StyleDataString), Info.ComboButtonStyle);

				break;
		}
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FCustomSlateStyle::Destroy()
{
	if (!StyleSet.IsValid())
	{
		return;
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);

	StyleSet.Reset();
}

void FCustomSlateStyle::Reload()
{
	Destroy();

	Create();

	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}
