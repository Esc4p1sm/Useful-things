// Fill out your copyright notice in the Description page of Project Settings.

#include "ScrollBoxWidget.h"
#include "Framework/Application/SlateApplication.h"
#include "Components/ScrollBox.h"
#include "MyBlueprintFunctionLibrary.h"

bool UScrollBoxWidget::Initialize()
{
    const bool InitStatus = Super::Initialize();

    if (InitStatus)
    {
        ScrollBox->SetNavigationDestination(EDescendantScrollDestination::Center);
        ScrollBox->SetConsumeMouseWheel(EConsumeMouseWheel::Never);
        ScrollBox->SetScrollBarVisibility(ESlateVisibility::Hidden);
        ScrollBox->SetScrollWhenFocusChanges(EScrollWhenFocusChanges::AnimatedScroll);

        for (int32 i = 0; i < ScrollBox->GetChildrenCount(); i++)
        {
            if (i == StartingIndex)
            {
                continue;
            }

            ScrollBox->GetChildAt(i)->SetIsEnabled(false);
            ScrollBox->GetChildAt(i)->SetRenderScale(CachedChildScaleSize * SizeScale);
        }
    }

    return InitStatus;
}

void UScrollBoxWidget::NativeConstruct()
{
    Super::NativeConstruct();

    FSlateApplication* const SlateApplication = &FSlateApplication::Get();

    if (SlateApplication)
    {
        SlateApplication->OnApplicationPreInputKeyDownListener().AddUObject(this, &UScrollBoxWidget::OnKeyDown);
    }

    const auto FocusedChild = ScrollBox->GetChildAt(StartingIndex);

    if (FocusedChild)
    {
        FocusedChild->SetKeyboardFocus();

        CachedChildScaleSize = FocusedChild->GetRenderTransform().Scale;
        CurrentChildIndex    = StartingIndex;
    }
}

void UScrollBoxWidget::OnKeyDown(const FKeyEvent& KeyEvent)
{
    if (!ScrollBox->HasFocusedDescendants() || KeyEvent.IsRepeat())
    {
        return;
    }

    const int32 SavedChildIndex = CurrentChildIndex;

    if (KeyEvent.GetKey() == EKeys::Down)
    {
        CurrentChildIndex++;
    }
    else if (KeyEvent.GetKey() == EKeys::Up)
    {
        CurrentChildIndex--;
    }
    else
    {
        return;
    }

    CurrentChildIndex = FMath::Clamp(CurrentChildIndex, 0, ScrollBox->GetChildrenCount() - 1);

    UpdateChildSize(SavedChildIndex);
}

void UScrollBoxWidget::UpdateChildSize(int32 PreviousIndex)
{
    const auto CurrentChild  = ScrollBox->GetChildAt(CurrentChildIndex);
    const auto PreviousChild = ScrollBox->GetChildAt(PreviousIndex);

    if (!CurrentChild || !PreviousChild)
    {
        return;
    }

    if (CurrentChild == PreviousChild)
    {
        return;
    }

    PreviousChild->SetRenderScale(CachedChildScaleSize * SizeScale);
    PreviousChild->SetIsEnabled(false);

    CurrentChild->SetRenderScale(CachedChildScaleSize);
    CurrentChild->SetIsEnabled(true);
    CurrentChild->SetKeyboardFocus();
}

void UScrollBoxWidget::NativeDestruct()
{
    FSlateApplication* const SlateApplication = &FSlateApplication::Get();

    if (SlateApplication)
    {
        if (SlateApplication->OnApplicationPreInputKeyDownListener().IsBound())
        {
            SlateApplication->OnApplicationPreInputKeyDownListener().Clear();
        }
    }

    Super::NativeDestruct();
}
