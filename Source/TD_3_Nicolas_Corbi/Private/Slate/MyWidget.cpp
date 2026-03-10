#include "Slate/MyWidget.h"
#include "Slate/SMyCustomButton.h"

TSharedRef<SWidget> UMyWidget::RebuildWidget()
{
	MyCustomButton = SNew(SMyCustomButton).ButtonText(Label);

	return MyCustomButton.ToSharedRef();
}

void UMyWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MyCustomButton.Reset();
}

void UMyWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MyCustomButton->SetLabel(Label);
}

void UMyWidget::SetLabel(FText NewLabel)
{
	Label = NewLabel;

	MyCustomButton->SetLabel(Label);
}
