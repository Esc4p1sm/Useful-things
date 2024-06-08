// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScrollBoxWidget.generated.h"

/**
 *
 */
UCLASS()
class MYMECHANICS_API UScrollBoxWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual bool Initialize() override;

    void OnKeyDown(const FKeyEvent& KeyEvent);

  protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<class UScrollBox> ScrollBox;

    UPROPERTY(EditDefaultsOnly, Category = "Scrollbox Params")
    int32 StartingIndex = 0;

    UPROPERTY(EditDefaultsOnly, Category = "Scrollbox Params")
    float SizeScale = 0.5f;

  private:
    void UpdateChildSize(int32 PreviousIndex);

    int32 CurrentChildIndex = 0;

    FVector2D CachedChildScaleSize;
};
