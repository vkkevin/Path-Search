#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__

class Heuristic
{
public:
    enum HeuristicType{
        Manhattan,
        Euclidean,
        Octile,
        Chebyshev
    };

public:
    Heuristic(HeuristicType type = Manhattan);
	~Heuristic();
	void setHeuristicType(HeuristicType type);
	HeuristicType heuristicType();
	double run(double dx, double dy);

protected:
	double manhattan(double dx, double dy);
	double euclidean(double dx, double dy);
	double octile(double dx, double dy);
	double chebyshev(double dx, double dy);

private:
    HeuristicType _type;

};

#endif /* __HEURISTIC_H__ */
