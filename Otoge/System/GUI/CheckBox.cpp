﻿#include "CheckBox.hpp"
#include "../../Util/Visual/Color.hpp"
#include "../GlobalMethod.hpp"
#include "../Input/MouseManager.hpp"

CheckBox::CheckBox(const std::string& label, const ScreenData& layoutScreen,
                   std::shared_ptr<FlexibleScaler> parentScaler) : GUI(label + "\"<CheckBox>\"", layoutScreen,
                                                                       parentScaler)
{
    baseColor = color_preset::BLUE;
    animationColor = color_preset::DARK_BLUE;
    textColor = color_preset::BLACK;
    CheckButton_ = std::make_shared<Button>(label + "_CheckButton",
                                            ScreenData(0.f, 0.f,
                                                       DefaultScaler_->CalculatePositionRateX(GetRawScreenHeight()),
                                                       100.f), DefaultScaler_);
    CheckButton_->isDrawBase = false;
    CheckButton_->baseColor = baseColor;
    CheckButton_->animationColor = animationColor;
    CheckButton_->SetLabel("");
    CheckButton_->ChangeDrawFunction([=]
    {
        auto l_SizeSubVal = 15.f;
        auto l_Fixed = CheckButton_->GetDefaultScaler()->Calculate(0.f + l_SizeSubVal, 0.f + l_SizeSubVal,
                                                                 100.f - (l_SizeSubVal), 100.f - (l_SizeSubVal));
        float l_Round = CheckButton_->GetDefaultScaler()->CalculateHeight(30.f);
        float l_Thick = CheckButton_->GetDefaultScaler()->CalculateHeight(8.f);
        l_Thick /= 2.f;
        DrawRoundRectAA(l_Fixed.posX + l_Thick, l_Fixed.posY + l_Thick, l_Fixed.width - l_Thick, l_Fixed.height - l_Thick, l_Round, l_Round,
                        engine::CastToInt(l_Round), CheckButton_->textColor, FALSE, l_Thick * 2.f);
        if(IsChecked_)
        {
            DrawRoundRectAA(l_Fixed.posX + l_Thick + 0.5f, l_Fixed.posY + l_Thick + 0.5f, l_Fixed.width - l_Thick - 0.5f,
                            l_Fixed.height - l_Thick - 0.5f, l_Round - 1.f, l_Round - 1.f, engine::CastToInt(l_Round - 1),
                            CheckButton_->baseColor, TRUE);
        }
    });
    AddChildTask(std::static_pointer_cast<Task>(CheckButton_));
    TextLabel_ = std::make_shared<Label>(
        label, ScreenData(CheckButton_->GetScreenWidth(), 2.f, 100.f - CheckButton_->GetScreenWidth(), 96.f),
        DefaultScaler_);
    TextLabel_->baseColor = textColor;
    TextLabel_->adjustmentFontSize = true;
    TextLabel_->ChangeFontThickness(1);
    TextLabel_->SetTextAlign(Label::TextAlignment::left | Label::TextAlignment::middle);
    AddChildTask(std::static_pointer_cast<Task>(TextLabel_));
}

CheckBox::~CheckBox()
{
}

void CheckBox::GUIUpdate(float deltaTime)
{
    IsOldChecked_ = IsChecked_;
    if(CheckButton_->IsClickedMouse() || TextLabel_->IsClickedMouse())
    {
        IsChecked_ = !IsChecked_;
    }
    if(IsDownMouse())
    {
        AddChildTask(std::static_pointer_cast<Task>(std::make_shared<ButtonPushedAnimate>(
            DefaultScaler_->
            CalculatePositionRateX(
                MouseManager::GetInstance()->GetMouseXf() - GetRawPositionX() - ParentScaler_->GetDiffX()),
            DefaultScaler_->CalculatePositionRateY(
                MouseManager::GetInstance()->GetMouseYf() - GetRawPositionY() - ParentScaler_->GetDiffY()),
            animationColor, 35.f, DefaultScaler_)));
    }
}

void CheckBox::Draw()
{
}

void CheckBox::SetChecked(bool check)
{
    IsChecked_ = check;
}

bool CheckBox::IsChecked()
{
    return IsChecked_;
}

bool CheckBox::IsChanged()
{
    return IsOldChecked_ != IsChecked_ && IsEnable();
}

std::shared_ptr<Label> CheckBox::GetTextLabelInstance()
{
    return TextLabel_;
}
