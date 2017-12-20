#include "core/option.h"
#include <iostream>
#include <cstring>

Option::Option()
{
    for(int i = 0; i < OptionTypeNum; i++){
        MOptionUsability[i] = Unuability;
        MOptionValue[i] = UNSELECTED;
    }
}

Option::~Option()
{

}

void Option::setOptionUsability(Option::OptionType type)
{
    MOptionUsability[type] = Usability;
}

void Option::setOptionUnusability(Option::OptionType type)
{
    MOptionUsability[type] = Unuability;
}

bool Option::optionUsability(Option::OptionType type)
{
    return MOptionUsability[type];
}

void Option::setOptionValue(Option::OptionType type, int value)
{
    MOptionValue[type] = value;
}

int Option::optionValue(Option::OptionType type)
{
    return MOptionValue[type];
}
