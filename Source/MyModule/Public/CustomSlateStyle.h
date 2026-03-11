#pragma once

#include "MyPrimaryDataAsset.h"

class MYMODULE_API FCustomSlateStyle
{
private:
	static TSharedPtr<FSlateStyleSet> StyleSet;

	static TStrongObjectPtr<UMyPrimaryDataAsset> StyleAsset;

public:
	static void Create();

	static void Destroy();

	static void Reload();

	static const ISlateStyle& Get() { return *StyleSet; };
};
