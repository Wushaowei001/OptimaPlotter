#ifndef POLYNOMIALALGORITHM_H
#define POLYNOMIALALGORITHM_H

#include "ialgorithm.h"
#include "algorithmbase.h"

class PolynomialAlgorithm : public AlgorithmBase
{
	Q_OBJECT
    Q_INTERFACES( IAlgorithm )
public:
	PolynomialAlgorithm();
	virtual ~PolynomialAlgorithm();

	virtual void evaluate();
	virtual QString name() const;
	virtual QString tagName() const;
	virtual Globals::AlgorithmFlags flags() const;

	virtual QString translatorPath( int language ) const;
};

#endif // POLYNOMIALALGORITHM_H
