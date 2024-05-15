// Copyright Big Woof Studios, LLC. All Rights Reserved.


#include "UI/Widget/TangiUserWidget.h"

void UTangiUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
