#ifndef OPTION_H
#define OPTION_H

class Option
{
public:
    enum OptionType{
        AllowDiagonal = 0,
        BiDirectional,
        DontCrossCorners,
        Weight,
        SecondsLimit,
        VisualizeRecursion
    };
static const int OptionTypeNum = 6;

enum OptionUsability{
    Usability = true,
    Unuability = false
};

static const int SELECTED      = 1;
static const int UNSELECTED = 0;

public:
    Option();
    ~Option();
    void setOptionUsability(OptionType type);
    void setOptionUnusability(OptionType type);
    bool optionUsability(OptionType type);

    void setOptionValue(OptionType type, int value);
    int optionValue(OptionType type);

private:
    OptionUsability _optionUsability[OptionTypeNum];
    int _optionValue[OptionTypeNum];
};

#endif /* OPTION_H */
