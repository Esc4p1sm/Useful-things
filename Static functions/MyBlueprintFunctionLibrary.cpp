// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/NavigationConfig.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UMyBlueprintFunctionLibrary::EnableAlternativeWidgetNavigation()
{
    FSlateApplication* const SlateApplication = &FSlateApplication::Get();

    if (SlateApplication)
    {
        FNavigationConfig* const NavigationConfig = &SlateApplication->GetNavigationConfig().Get();

        if (NavigationConfig)
        {
            NavigationConfig->KeyEventRules.Emplace(EKeys::A, EUINavigation::Left);
            NavigationConfig->KeyEventRules.Emplace(EKeys::S, EUINavigation::Down);
            NavigationConfig->KeyEventRules.Emplace(EKeys::W, EUINavigation::Up);
            NavigationConfig->KeyEventRules.Emplace(EKeys::D, EUINavigation::Right);
        }
    }
}

void UMyBlueprintFunctionLibrary::DisableAlternativeWidgetNavigation()
{
    FSlateApplication* const SlateApplication = &FSlateApplication::Get();

    if (SlateApplication)
    {
        FNavigationConfig* const NavigationConfig = &SlateApplication->GetNavigationConfig().Get();

        if (NavigationConfig)
        {
            NavigationConfig->KeyEventRules.FindAndRemoveChecked(EKeys::A);
            NavigationConfig->KeyEventRules.FindAndRemoveChecked(EKeys::S);
            NavigationConfig->KeyEventRules.FindAndRemoveChecked(EKeys::W);
            NavigationConfig->KeyEventRules.FindAndRemoveChecked(EKeys::D);
        }
    }
}
