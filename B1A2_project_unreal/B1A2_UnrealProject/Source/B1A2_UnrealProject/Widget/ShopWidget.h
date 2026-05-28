// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Network/Includes.h"

#include "ShopWidget.generated.h"

class UCheckBox;
class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class B1A2_UNREALPROJECT_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

public:
    void SetCurrentCredit(int32 currentCredit) { _currentCredit = currentCredit;}

    void UpdateUI();
private:
    // CheckBox 이벤트 리스너
    UFUNCTION() void OnCutlassChecked(bool isChecked);
    UFUNCTION() void OnBlasterChecked(bool isChecked);
    UFUNCTION() void OnLanternChecked(bool isChecked);

    // 수량 조절 버튼 리스너
    UFUNCTION() void OnCutlassMinusClicked();
    UFUNCTION() void OnCutlassPlusClicked();
    UFUNCTION() void OnBlasterMinusClicked();
    UFUNCTION() void OnBlasterPlusClicked();
    UFUNCTION() void OnLanternMinusClicked();
    UFUNCTION() void OnLanternPlusClicked();

    // 구매 버튼 리스너
    UFUNCTION() void OnPurchaseButtonClicked();

protected:
    // Current Credit
    UPROPERTY(meta = (BindWidget))
    UTextBlock* Text_CurrentCredit;
      
    // Pruchase Button
    UPROPERTY(meta = (BindWidget))
    UButton* Button_Purchase;

    // Cutlass
    UPROPERTY(meta = (BindWidget))
    UCheckBox* CutlassCheckBox;
    
    UPROPERTY(meta = (BindWidget))
    UButton* CutlassButtonMinus;

    UPROPERTY(meta = (BindWidget))
    UButton* CutlassButtonPlus;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* CutlassQuantity;

    // Blaster
    UPROPERTY(meta = (BindWidget))
    UCheckBox* BlasterCheckBox;

    UPROPERTY(meta = (BindWidget))
    UButton* BlasterButtonMinus;

    UPROPERTY(meta = (BindWidget))
    UButton* BlasterButtonPlus;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* BlasterQuantity;

    // Lantern
    UPROPERTY(meta = (BindWidget))
    UCheckBox* LanternCheckBox;

    UPROPERTY(meta = (BindWidget))
    UButton* LanternButtonMinus;

    UPROPERTY(meta = (BindWidget))
    UButton* LanternButtonPlus;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LanternQuantity;

private:
    // 가격
    const int32 _cutlassPrice = 65;
    const int32 _blasterPrice = 100;
    const int32 _lanternPrice = 30;

    // 내부 상태 변수
    ItemType _selectedItemType = ItemType::None;
    int32 _cutlassQuantity = 0;
    int32 _blasterQuantity = 0;
    int32 _lanternQuantity = 0;

    int32 _currentCredit;

};
