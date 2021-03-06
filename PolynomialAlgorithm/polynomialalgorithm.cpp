#include "stdafx.h"
#include "polynomialalgorithm.h"
#include "globals.h"

#include <qmath.h>
#include <qtranslator.h>
#include <qapplication.h>

using namespace Eigen;

bool lessThanForTwoPointsOnXAxis( const QPointF& p1, const QPointF& p2 )
{
	return p1.x() < p2.x();
}

PolynomialAlgorithm::PolynomialAlgorithm()
{
	m_settingsWidget = new QWidget();
	m_settingsWidgetForm.setupUi( m_settingsWidget );
}

PolynomialAlgorithm::~PolynomialAlgorithm()
{

}

void PolynomialAlgorithm::evaluate()
{
	m_samples.clear();

	bool ok;
	QVariant value;

	getPropertyValueByTagName( "samples_count", value, ok );
	if( !ok )
		return;
	const int samplesCount = value.toInt();

	applySettings();

	getPropertyValueByTagName( "polynomial_degree", value, ok );
	if( !ok )
		return;
	const int polynomialDegree = value.toInt();

	qSort( m_markers.begin(), m_markers.end(), lessThanForTwoPointsOnXAxis );

	const double step = qAbs( m_markers.first().x() -  m_markers.last().x() ) / ( samplesCount - 1 );

	const int columnCount = polynomialDegree + 1;
	const int rowCount = m_markers.size();

	MatrixXf matrixA( rowCount, columnCount );
	MatrixXf matrixAPlus( columnCount, rowCount );
	VectorXf vectorB( rowCount );
	VectorXf result( columnCount );

	int row = 0;
	foreach( QPointF point, m_markers )
	{
		vectorB( row ) = point.y();

		for( int column = 0; column < columnCount; ++column )
		{
			matrixA( row, column ) = qPow( point.x(), column );
		}

		++row;
	}

	JacobiSVD<MatrixXf> svd( matrixA, ComputeFullU | ComputeFullV );

	MatrixXf matrixSPlus = MatrixXf::Zero( columnCount, rowCount );

	const JacobiSVD<MatrixXf>::SingularValuesType& singularValues = svd.singularValues();
	for( int i = 0; i < singularValues.size(); i++ )
	{
		float value = svd.singularValues()[i];
		if( value ) //TODO: is this check needed?
		{
			matrixSPlus( i, i ) = 1.0 / value;
		}
	}

	matrixAPlus = svd.matrixV() * matrixSPlus * svd.matrixU().transpose();
	result = matrixAPlus * vectorB;

	int i = 0;
	double x = m_markers.first().x();
	int pointIndex = 1;

	while( i != samplesCount + m_markers.size() )
	{
		double y = 0;
		double xTemp = 1;
		
		for( int j = 0; j <= polynomialDegree; j++ )
		{
			y += xTemp * result( j );
			xTemp *= x;
		}

		m_samples.append( QPointF( x, y ) );
		//TODO: optimize
		if( pointIndex < m_markers.size() && x + step >= m_markers.at( pointIndex ).x() )
		{
			x = m_markers.at( pointIndex ).x();
			++pointIndex;
		}
		else
		{
			x += step;
		}
		++i;
	}

	m_knots.clear();
	m_knots << x;
}

QString PolynomialAlgorithm::name() const
{
	return tr( "Polynomial" );
}

QString PolynomialAlgorithm::tagName() const
{
	return "polynomial";
}

QString PolynomialAlgorithm::translatorPath( int language ) const
{
	switch( language )
	{
	case ( int )Globals::LANG_HY:
		{
			return ":/polynomialalgorithm/polynomialalgorithm_hy.qm";
		}
	default:
		return QString();
	}
}

void PolynomialAlgorithm::retranslateUi()
{
	if( m_settingsWidget )
		m_settingsWidgetForm.retranslateUi( m_settingsWidget );
}

Globals::AlgorithmFlags PolynomialAlgorithm::flags() const
{
	Globals::AlgorithmFlags flags = AlgorithmBase::flags();
	return flags;
	//return flags /*| Globals::ALGO_FLAG_KNOT_PICKER*/  | Globals::ALGO_FLAG_RANGE_PICKER;
}

void PolynomialAlgorithm::applySettings()
{
	setPropertyValueByTagName( "polynomial_degree", m_settingsWidgetForm.polynomialDegreeSpinBox->value() );
}

Q_EXPORT_PLUGIN2( polynomialalgorithm, PolynomialAlgorithm );