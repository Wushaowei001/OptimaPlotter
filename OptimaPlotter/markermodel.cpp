#include "stdafx.h"
#include "markermodel.h"

#include "qwt_plot.h"

#include <qpoint.h>

MarkerModel::MarkerModel( QObject* parent ) : BaseModel( parent )
{
}

MarkerModel::~MarkerModel()
{

}

int MarkerModel::columnCount( const QModelIndex& parent ) const
{
	return 2;
}

QVariant MarkerModel::data( const QModelIndex& index, int role ) const
{
	if( role == Qt::DisplayRole )
	{
		const int row = index.row();
		const int column = index.column();

		if( row >= 0 && row < m_plotItems.count() )
		{
			QwtPlotItem* plotItem = m_plotItems.at( row );
			MarkerItem* markerItem = dynamic_cast<MarkerItem*>( plotItem );

			if( markerItem )
			{
				switch( column )
				{
				case 0:
					return markerItem->xValue();
				case 1:
					return markerItem->yValue();
				}
			}
		}
	}

	return QVariant();
}

QVariant MarkerModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
	{
		switch( section )
		{
			case 0:
				return "X";
			case 1:
				return "Y";
		}

	}

	return BaseModel::headerData( section, orientation, role );
}

void MarkerModel::onAddNewMarker( MarkerItem* markerItem, bool emitMarkerAdded )
{
	beginInsertRows( QModelIndex(), m_plotItems.count(), m_plotItems.count() );
	m_plotItems.append( markerItem );
	endInsertRows();

	if( emitMarkerAdded )
		emit itemAdded( markerItem );
}


bool MarkerModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
	/*if( role == Qt::EditRole )
	{
		MarkerItem* markerItem = itemFromIndexAs<MarkerItem>( index );
		const int column = index.column();

		bool isOk;
		const double valueInDouble = value.toDouble( &isOk );

		if( !isOk )
			return false;

		switch( column )
		{
		case 0:
			{
				markerItem->setXValue( valueInDouble );
				markerItem->plot()->replot();
				return true;
			}
		case 1:
			{
				markerItem->setYValue( valueInDouble );
				markerItem->plot()->replot();
				return true;
			}
		default:
			return false;
		}
	}
	*/
	return QAbstractItemModel::setData( index, value, role );
}