#include "core/option.h"
#include <iostream>
#include <cstring>

Option::Option()
{
    for(int i = 0; i < OptionTypeNum; i++){
        _optionUsability[i] = Unuability;
        _optionValue[i] = UNSELECTED;
    }
}

Option::~Option()
{

}

void Option::setOptionUsability(Option::OptionType type)
{
    _optionUsability[type] = Usability;
}

void Option::setOptionUnusability(Option::OptionType type)
{
    _optionUsability[type] = Unuability;
}

bool Option::optionUsability(Option::OptionType type)
{
    return _optionUsability[type];
}

void Option::setOptionValue(Option::OptionType type, int value)
{
    _optionValue[type] = value;
}

int Option::optionValue(Option::OptionType type)
{
    return _optionValue[type];
}
