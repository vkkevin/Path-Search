#include "core/heuristic.h"
#include <cmath>

Heuristic::Heuristic(Heuristic::HeuristicType type): MType(type)
{

}

Heuristic::~Heuristic()
{

}

void Heuristic::setHeuristicType(Heuristic::HeuristicType type)
{
    MType = type;
}

Heuristic::HeuristicType Heuristic::heuristicType()
{
    return MType;
}

double Heuristic::run(double dx, double dy)
{
    switch(MType){
        case Manhattan:   return manhattan(dx, dy);
        case Euclidean:     return euclidean(dx, dy);
        case Octile:            return octile(dx, dy);
        case Chebyshev:   return chebyshev(dx, dy);
        default: break;
    }
    return 0.0;
}

double Heuristic::manhattan(double dx, double dy)
{
    return dx + dy;
}

double Heuristic::euclidean(double dx, double dy)
{
    return sqrt(dx * dx + dy * dy);
}

double Heuristic::octile(double dx, double dy)
{
    double w = sqrt(2) - 1;
    return (dx < dy) ? w * dx + dy : w * dy + dx;
}

double Heuristic::chebyshev(double dx, double dy)
{
    return dx < dy? dy : dx;
}
