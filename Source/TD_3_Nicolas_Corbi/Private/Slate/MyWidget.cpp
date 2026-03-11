#include "Slate/MyWidget.h"
#include "Slate/SMyCustomButton.h"

TSharedRef<SWidget> UMyWidget::RebuildWidget()
{
	MyCustomButton = SNew(SMyCustomButton).ButtonText(Label).ButtonStyle(ButtonStyle);

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

	MyCustomButton->SetButtonStyle(ButtonStyle);
}

void UMyWidget::SetLabel(FText NewLabel)
{
	Label = NewLabel;

	MyCustomButton->SetLabel(Label);
}

void UMyWidget::SetButtonStyle(FButtonStyle NewStyle)
{
	ButtonStyle = NewStyle;

	MyCustomButton->SetButtonStyle(NewStyle);
}
