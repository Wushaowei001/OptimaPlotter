#ifndef OPTIMAPLOTTER_H
#define OPTIMAPLOTTER_H

#include <QtGui/QMainWindow>
#include "ui_optimaplotter.h"

class PlotWidget;
class QSpinBox;
class QTranslator;
class QLabel;

class OptimaPlotter : public QMainWindow
{
	Q_OBJECT

public:
	OptimaPlotter(QWidget *parent = 0, Qt::WFlags flags = 0);
	~OptimaPlotter();

private:
	void initPlotWidget();
	void setupToolBar();
	void setupAnimation();
	void readSettings();

	void retranslateUi();
	virtual void changeEvent( QEvent* event );

public slots:
	void onReset();
	void onEventLoopStarted();

private slots:
	void onPickModeActivated();
	void onPanModeActivated();
	void onPointAdded( const QPointF& point );
	void onExecute();
	void onExecuteSettingsDialog();

private:
	Ui::OptimaPlotterClass ui;
	PlotWidget* m_plotWidget;
	QLabel* m_polynomialDegreeLabel;
	QSpinBox* m_polynomialDegreeSpinBox;
	QTranslator* m_translator;
};

#endif //OPTIMAPLOTTER_H
