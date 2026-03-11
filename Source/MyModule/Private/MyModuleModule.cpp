#include "MyModuleModule.h"
#include "Modules/ModuleManager.h"
#include "CustomSlateStyle.h"

IMPLEMENT_MODULE(FMyModule, MyModule);

void FMyModule::StartupModule()
{
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FMyModule::OnPostInit);

	FCoreUObjectDelegates::OnObjectPropertyChanged.AddRaw(this, &FMyModule::OnDataPropertyChanged);
}

void FMyModule::ShutdownModule()
{
	FCoreDelegates::OnPostEngineInit.RemoveAll(this);

	FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);

	FCustomSlateStyle::Destroy();
}

void FMyModule::OnPostInit()
{
	FCustomSlateStyle::Create();
}

void FMyModule::OnDataPropertyChanged(UObject* Object, FPropertyChangedEvent& Event)
{
	if ((EPropertyChangeType::ValueSet & Event.ChangeType || EPropertyChangeType::Interactive & Event.ChangeType) && Object->IsA<UMyPrimaryDataAsset>())
	{
		FCustomSlateStyle::Reload();
	}
}
