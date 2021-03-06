#ifndef PLOTWIDGET_H
#define PLOTWIDGET_H

#include "qwt_plot.h"

#include <qpoint.h>
#include <qvector.h>
#include <qlist.h>

class QwtPlotPicker;
class KnotPicker;
class MarkerItem;
class KnotItem;
class CanvasPicker;
class MarkerPickerClickPointMachine;
class PlotPanner;
class PlotMagnifier;
class QwtPlotCurve;
class QwtPlotGrid;
class QwtPlotItem;

class PlotWidget : public QwtPlot
{
	Q_OBJECT

public:
	PlotWidget( QWidget* parent = 0 );
	~PlotWidget();

	void setPannerEnabled( bool enabled );
	bool isPannerEnabled() const; 
	void setPickerEnabled( bool enabled );
	bool isPickerEnabled() const;
	void setMagnifierEnabled( bool enabled );
	bool isMagnifierEnabled() const;
	void setKnotPickerEnabled( bool enabled );
	bool isKnotPickerEnabled() const;
	void setCanvasPickerEnabled( bool enabled );
	bool isCanvasPickerEnabled() const;

	void setKnotPicker( KnotPicker* knotPicker );
	void setCanvasPicker( CanvasPicker* canvasPicker );
	void setCurveSamples( const QVector<QPointF>& samples );

	void setKnotsEnabled( bool enabled = true );
	void setKnotsEditable( bool enabled = true );
	void setRangeEnabled( bool enabled = true );

	void insertKnot( double coordinate );
	void insertMarker( const QPointF& point );

	void markerPointsVector( QVector<QPointF>& points ) const;
	void knotsVector( QVector<double>& knots ) const;
	void rangeBorders( double& left, double& right ) const;

	void panToCenter();

	QList<QwtPlotItem*>& listOfSelectedItems( int itemType );

	void boundingXCoordinates( double& x1, double& x2 ) const;

public slots:
	void onItemAdded( QwtPlotItem* plotItem );
	void onSelectionChanged( QList<QwtPlotItem*>& selectedItems, QList<QwtPlotItem*>& deselectedItems );
	void onDeleteSelectedMarkers();
	void onDeleteSelectedKnots();

signals:
	void pointPicked( const QPointF& point );
	void knotPicked( double coordinate );

	void dataChanged( QwtPlotItem* plotItem );
	void itemAdded( QwtPlotItem* plotItem );
	void selectionChanged( QList<QwtPlotItem*>& selectedItems, QList<QwtPlotItem*>& deselectedItems );

private slots:
	void onPicked( Qt::KeyboardModifiers modifiers, QwtPlotItem* plotItem );

private:
	QwtPlotCurve* m_plotCurve;
	QwtPlotPicker* m_plotPicker;
	MarkerPickerClickPointMachine* m_markerPickerClickPointMachine;
	PlotPanner* m_plotPanner;
	PlotMagnifier* m_plotMagnifier;
	QwtPlotGrid* m_plotGrid;
	KnotPicker* m_knotPicker;
	CanvasPicker* m_canvasPicker;

	QList<QwtPlotItem*> m_listOfSelectedMarkers;
	QList<QwtPlotItem*> m_listOfSelectedKnots;
};

#endif //PLOTWIDGET_H