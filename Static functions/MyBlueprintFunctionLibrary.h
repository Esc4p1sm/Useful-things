// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SWidget.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MYMECHANICS_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
    UFUNCTION(BlueprintCallable)
    static void EnableAlternativeWidgetNavigation();

	UFUNCTION(BlueprintCallable)
    static void DisableAlternativeWidgetNavigation();
};
