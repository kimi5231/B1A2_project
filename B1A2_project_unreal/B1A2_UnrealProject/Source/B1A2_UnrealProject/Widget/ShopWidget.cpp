// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Main/Main.h"

void UShopWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    // Check Box
    if (CutlassCheckBox) 
    {
        CutlassCheckBox->OnCheckStateChanged.RemoveDynamic(this, &UShopWidget::OnCutlassChecked);
        CutlassCheckBox->OnCheckStateChanged.AddDynamic(this, &UShopWidget::OnCutlassChecked);
    }
   /* if (BlasterCheckBox) 
    {
        BlasterCheckBox->OnCheckStateChanged.RemoveDynamic(this, &UShopWidget::OnBlasterChecked);
        BlasterCheckBox->OnCheckStateChanged.AddDynamic(this, &UShopWidget::OnBlasterChecked);
    }*/
    if (LanternCheckBox) 
    {
        LanternCheckBox->OnCheckStateChanged.RemoveDynamic(this, &UShopWidget::OnLanternChecked);
        LanternCheckBox->OnCheckStateChanged.AddDynamic(this, &UShopWidget::OnLanternChecked);
    }

    // Cutlass
    if (CutlassButtonMinus) 
    {
        CutlassButtonMinus->OnClicked.RemoveDynamic(this, &UShopWidget::OnCutlassMinusClicked);
        CutlassButtonMinus->OnClicked.AddDynamic(this, &UShopWidget::OnCutlassMinusClicked);
    }
    if (CutlassButtonPlus) 
    {
        CutlassButtonPlus->OnClicked.RemoveDynamic(this, &UShopWidget::OnCutlassPlusClicked);
        CutlassButtonPlus->OnClicked.AddDynamic(this, &UShopWidget::OnCutlassPlusClicked);
    }
    
    // Blaster
   /* if (BlasterButtonMinus) 
    {
        BlasterButtonMinus->OnClicked.RemoveDynamic(this, &UShopWidget::OnBlasterMinusClicked);
        BlasterButtonMinus->OnClicked.AddDynamic(this, &UShopWidget::OnBlasterMinusClicked);
    }
    if (BlasterButtonPlus) 
    {
        BlasterButtonPlus->OnClicked.RemoveDynamic(this, &UShopWidget::OnBlasterPlusClicked);
        BlasterButtonPlus->OnClicked.AddDynamic(this, &UShopWidget::OnBlasterPlusClicked);
    }*/

    // Lantern
    if (LanternButtonMinus) 
    {
        LanternButtonMinus->OnClicked.RemoveDynamic(this, &UShopWidget::OnLanternMinusClicked);
        LanternButtonMinus->OnClicked.AddDynamic(this, &UShopWidget::OnLanternMinusClicked);
    }
    if (LanternButtonPlus) 
    {
        LanternButtonPlus->OnClicked.RemoveDynamic(this, &UShopWidget::OnLanternPlusClicked);
        LanternButtonPlus->OnClicked.AddDynamic(this, &UShopWidget::OnLanternPlusClicked);
    }

    // Purchase
    if (Button_Purchase) 
    {
        Button_Purchase->OnClicked.RemoveDynamic(this, &UShopWidget::OnPurchaseButtonClicked);
        Button_Purchase->OnClicked.AddDynamic(this, &UShopWidget::OnPurchaseButtonClicked);
    }
}

void UShopWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // 상점이 켜질 때마다 실시간 크레딧 및 보유 수량 초기화 리셋
    if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
    {
        _currentCredit = gameInstance->GetCurrentCredit();
    }
    else
    {
        _currentCredit = 0;
    }

    _selectedItemType = ItemType::CUTLASS;
    _cutlassQuantity = 0;
    //_blasterQuantity = 0;
    _lanternQuantity = 0;

    if (CutlassCheckBox) CutlassCheckBox->SetIsChecked(true);
    //if (BlasterCheckBox) BlasterCheckBox->SetIsChecked(false);
    if (LanternCheckBox) LanternCheckBox->SetIsChecked(false);

    if (APlayerController* PC = GetOwningPlayer())
    {
        PC->bShowMouseCursor = true;

        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

        PC->SetInputMode(InputMode);
    }

    UpdateUI();
}

void UShopWidget::NativeDestruct()
{
    if (APlayerController* PC = GetOwningPlayer())
    {
        PC->bShowMouseCursor = false;

        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
    }

    Super::NativeDestruct();
}

void UShopWidget::OnCutlassChecked(bool isChecked)
{
    if (isChecked)
    {
        _selectedItemType = ItemType::CUTLASS;
        
        _cutlassQuantity = 0;
        //_blasterQuantity = 0;
        _lanternQuantity = 0;

        //if (BlasterCheckBox) BlasterCheckBox->SetIsChecked(false);
        if (LanternCheckBox) LanternCheckBox->SetIsChecked(false);
    }
    else if (_selectedItemType == ItemType::CUTLASS)
    {
        CutlassCheckBox->SetIsChecked(true);    // 여러 번 눌렸을 때 체크 해제 방지
    }

    UpdateUI();
}

//void UShopWidget::OnBlasterChecked(bool isChecked)
//{
//    if (isChecked)
//    {
//        _selectedItemType = ItemType::Blaster;
//     
//        _cutlassQuantity = 0;
//        _blasterQuantity = 0;
//        _lanternQuantity = 0;
//
//        if (CutlassCheckBox) CutlassCheckBox->SetIsChecked(false);
//        if (LanternCheckBox) LanternCheckBox->SetIsChecked(false);
//    }
//    else if (_selectedItemType == ItemType::Blaster)
//    {
//        BlasterCheckBox->SetIsChecked(true);
//    }
//
//    UpdateUI();
//}

void UShopWidget::OnLanternChecked(bool isChecked)
{
    if (isChecked)
    {
        _selectedItemType = ItemType::LANTERN;
        
        _cutlassQuantity = 0;
        //_blasterQuantity = 0;
        _lanternQuantity = 0;

        if (CutlassCheckBox) CutlassCheckBox->SetIsChecked(false);
        //if (BlasterCheckBox) BlasterCheckBox->SetIsChecked(false);
    }
    else if (_selectedItemType == ItemType::LANTERN)
    {
        LanternCheckBox->SetIsChecked(true);
    }

    UpdateUI();
}

void UShopWidget::OnCutlassMinusClicked()
{
    // 현재 Cutlass가 선택된 상태 && 수량이 0보다 클 때
    if (_selectedItemType == ItemType::CUTLASS && _cutlassQuantity > 0)
    {
        _cutlassQuantity--;
        UpdateUI();
    }
}

void UShopWidget::OnCutlassPlusClicked()
{
    if (_selectedItemType == ItemType::CUTLASS && _cutlassQuantity < 99)
    {
        // 수량을 1개 늘렸을 때 필요한 예측 총 비용 계산
        int32 predictedCost = _cutlassPrice * (_cutlassQuantity + 1);

        // 잔액이 충분할 때만 증가 허용
        if (predictedCost <= _currentCredit)
        {
            _cutlassQuantity++;
            UpdateUI();
        }
    }
}

//void UShopWidget::OnBlasterMinusClicked()
//{
//    if (_selectedItemType == ItemType::Blaster && _blasterQuantity > 0)
//    {
//        _blasterQuantity--;
//        UpdateUI();
//    }
//}
//
//void UShopWidget::OnBlasterPlusClicked()
//{
//    if (_selectedItemType == ItemType::Blaster && _blasterQuantity < 99)
//    {
//        int32 predictedCost = _blasterPrice * (_blasterQuantity + 1);
//
//        if (predictedCost <= _currentCredit)
//        {
//            _blasterQuantity++;
//            UpdateUI();
//        }
//    }
//}

void UShopWidget::OnLanternMinusClicked()
{
    if (_selectedItemType == ItemType::LANTERN && _lanternQuantity > 0)
    {
        _lanternQuantity--;
        UpdateUI();
    }
}

void UShopWidget::OnLanternPlusClicked()
{
    if (_selectedItemType == ItemType::LANTERN && _lanternQuantity < 99)
    {
        int32 predictedCost = _lanternPrice * (_lanternQuantity + 1);

        if (predictedCost <= _currentCredit)
        {
            _lanternQuantity++;
            UpdateUI();
        }
    }
}

void UShopWidget::OnPurchaseButtonClicked()
{
    int32 sendQuantity = 0;

    switch (_selectedItemType)
    {
    case ItemType::CUTLASS: sendQuantity = _cutlassQuantity; break;
    //case ItemType::Blaster: sendQuantity = _blasterQuantity; break;
    case ItemType::LANTERN: sendQuantity = _lanternQuantity; break;
    default: return;
    }

    // 수량이 0개면 Send하지 않음
    if (sendQuantity <= 0) return;

    if (UMain* gameInstance = Cast<UMain>(GetGameInstance()))
    {
        gameInstance->SendBuyItem(gameInstance->GetMyID(), _selectedItemType, sendQuantity);

        UE_LOG(LogTemp, Log, TEXT("[ShopWidget] SendBuyItem Successfully Called. Type: %d, Qty: %d"), (int32)_selectedItemType, sendQuantity);
    }
}

void UShopWidget::UpdateUI()
{
    FText unitFormat0 = FText::FromString(TEXT("{0}CD"));
    if (Text_CurrentCredit)
    {
        Text_CurrentCredit->SetText(FText::Format(unitFormat0, FText::AsNumber(_currentCredit)));
    }
    UE_LOG(LogTemp, Display, TEXT("[UdateUI] credit %d"), _currentCredit);

    // 아이템별 가격 * 수량 계산
    int32 cutlassTotal = _cutlassPrice * _cutlassQuantity;
    //int32 blasterTotal = _blasterPrice * _blasterQuantity;
    int32 lanternTotal = _lanternPrice * _lanternQuantity;

    // UI 텍스트
    FText unitFormat1 = FText::FromString(TEXT("x{0}"));
    if (CutlassQuantity) CutlassQuantity->SetText(FText::Format(unitFormat1, FText::AsNumber(_cutlassQuantity)));
    //if (BlasterQuantity) BlasterQuantity->SetText(FText::Format(unitFormat1, FText::AsNumber(_blasterQuantity)));
    if (LanternQuantity) LanternQuantity->SetText(FText::Format(unitFormat1, FText::AsNumber(_lanternQuantity)));

    // 현재 선택된 아이템의 총 비용 및 수량 판별
    int32 activeTotalCost = 0;
    int32 activeQuantity = 0;

    switch (_selectedItemType)
    {
    case ItemType::CUTLASS:
        activeTotalCost = cutlassTotal;
        activeQuantity = _cutlassQuantity;
        break;
  /*  case ItemType::Blaster:
        activeTotalCost = blasterTotal;
        activeQuantity = _blasterQuantity;
        break;*/
    case ItemType::LANTERN:
        activeTotalCost = lanternTotal;
        activeQuantity = _lanternQuantity;
        break;
    default:
        break;
    }

    // 구매 버튼
    if (Button_Purchase)
    {
        // 선택품목 존재 && 수량이 1개 이상 && 총 비용이 잔액 이하일 때만 활성화
        if (_selectedItemType != ItemType::None && activeQuantity > 0 && activeTotalCost <= _currentCredit)
        {
            Button_Purchase->SetIsEnabled(true);
        }
        else
        {
            Button_Purchase->SetIsEnabled(false);
        }
    }
}