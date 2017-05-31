#ifndef SCURVETRAJGEN_SCURVEQTWIDGET_HPP_
#define SCURVETRAJGEN_SCURVEQTWIDGET_HPP_

#include "SCurveProfile.hpp"

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QLineEdit>

class QComboBox;
class QCheckBox;
class QLineEdit;

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
class QLineSeries;
class QScatterSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

class SCurveQtWidget: public QWidget
{
  Q_OBJECT
  public:
    explicit SCurveQtWidget(QWidget *parent = 0);
    ~SCurveQtWidget();

  private Q_SLOTS:
    void updateUI();

  private:
    QComboBox *createThemeBox() const;
    QComboBox *createAnimationBox() const;
    QComboBox *createLegendBox() const;
    void connectSignals();
    QChart *createPositionChart() const;
    QChart *createVelocityChart() const;
    QChart *createAccelerationChart() const;
    QChart *createJerkChart() const;
  public slots:
    void callback_si_text_edit ( QString text );
    void callback_slider_si(int a);
    void callback_slider_vi(int a);
    void callback_slider_ai(int a);
    void callback_slider_sf(int a);
    void callback_slider_vf(int a);
    void callback_slider_af(int a);
    void callback_slider_vmax(int a);
    void callback_slider_amax(int a);
    void callback_slider_jmax(int a);
    void re_print_curves();

  private:
    SCurveProfile s_curve;
    QList<QChartView *> m_charts;
    QLineSeries* s_series;
    QLineSeries* v_series;
    QLineSeries* a_series;
    QLineSeries* j_series;
    QLineSeries* s_zero_series, *s_zero_series_y;
    QLineSeries* v_zero_series, *v_zero_series_y;
    QLineSeries* a_zero_series, *a_zero_series_y;
    QLineSeries* j_zero_series, *j_zero_series_y;
    QLineSeries* a_min_series;
    QLineSeries* j_min_series;
    QLineSeries* v_max_series;
    QLineSeries* a_max_series;
    QLineSeries* j_max_series;
    QLineEdit* line_edit;
    QSlider* slider_si;
    QScatterSeries* s_bounds, *v_bounds, *a_bounds;
    QChart* s_chart;
    QChart* v_chart;
    QChart* a_chart;
    QChart* j_chart;
    qreal s_init;
    qreal v_init;
    qreal a_init;
    qreal s_final;
    qreal v_final;
    qreal a_final;
    qreal v_max;
    qreal a_max;
    qreal j_max;

    QComboBox *m_themeComboBox;
    QCheckBox *m_antialiasCheckBox;
    QComboBox *m_animatedComboBox;
    QComboBox *m_legendComboBox;
};

#endif //SCURVETRAJGEN_SCURVEQTWIDGET_HPP_