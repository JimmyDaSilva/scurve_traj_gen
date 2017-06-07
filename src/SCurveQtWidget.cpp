#include "SCurveQtWidget.hpp"
#include <iostream>

#include <iostream>
#include <vector>
#include <cmath>

QT_CHARTS_USE_NAMESPACE

SCurveQtWidget::SCurveQtWidget(QWidget *parent) :
    QWidget(parent),
    m_themeComboBox(createThemeBox()),
    m_antialiasCheckBox(new QCheckBox("Anti-aliasing")),
    m_animatedComboBox(createAnimationBox()),
    m_legendComboBox(createLegendBox())
{
  // Inital values
  s_init = 0.0;
  v_init = 0.0;
  a_init = 0.0;
  s_final = 3.0;
  v_final = 0.0;
  a_final = 0.0;
  v_max = 1.0;
  a_max = 2.0;
  j_max = 5.0;
  
  // Compute first SCurve
  s_curve.config(s_init,v_init,a_init,s_final,v_final,a_final,v_max,a_max,j_max);
  s_curve.set_period(0.001);
  s_curve.compute_curves();
  
  connectSignals();
  // create layout
  QGridLayout *baseLayout = new QGridLayout();
  QHBoxLayout *settingsLayout = new QHBoxLayout();
  settingsLayout->addWidget(new QLabel("Theme:"));
  settingsLayout->addWidget(m_themeComboBox);
  settingsLayout->addWidget(new QLabel("Animation:"));
  settingsLayout->addWidget(m_animatedComboBox);
  settingsLayout->addWidget(new QLabel("Legend:"));
  settingsLayout->addWidget(m_legendComboBox);
  settingsLayout->addWidget(m_antialiasCheckBox);
  settingsLayout->addStretch();
  baseLayout->addLayout(settingsLayout, 0, 0, 1, 3);
  
  //create charts
  QChartView *chartView;
  
  s_bounds = new QScatterSeries();
  s_bounds->append(0, s_init);
  s_bounds->append(s_curve.t_vect_[s_curve.t_vect_.size()-1], s_final);
  
  v_bounds = new QScatterSeries();
  v_bounds->append(0, v_init);
  v_bounds->append(s_curve.t_vect_[s_curve.t_vect_.size()-1], v_final);
  
  a_bounds = new QScatterSeries();
  a_bounds->append(0, a_init);
  a_bounds->append(s_curve.t_vect_[s_curve.t_vect_.size()-1], a_final);
  
  s_zero_series = new QLineSeries();
  s_zero_series->setPen(QPen((Qt::black),1));
  s_zero_series->setUseOpenGL(true);
  s_zero_series->append(-100, 0);
  s_zero_series->append(100, 0);
  
  s_zero_series_y = new QLineSeries();
  s_zero_series_y->setPen(QPen((Qt::black),1));
  s_zero_series_y->setUseOpenGL(true);
  s_zero_series_y->append(0, -100);
  s_zero_series_y->append(0, 100);
  
  v_zero_series = new QLineSeries();
  v_zero_series->setPen(QPen((Qt::black),1));
  v_zero_series->setUseOpenGL(true);
  v_zero_series->append(-100, 0);
  v_zero_series->append(100, 0);
  
  v_zero_series_y = new QLineSeries();
  v_zero_series_y->setPen(QPen((Qt::black),1));
  v_zero_series_y->setUseOpenGL(true);
  v_zero_series_y->append(0, -100);
  v_zero_series_y->append(0, 100);
  
  a_zero_series = new QLineSeries();
  a_zero_series->setPen(QPen((Qt::black),1));
  a_zero_series->setUseOpenGL(true);
  a_zero_series->append(-100, 0);
  a_zero_series->append(100, 0);
  
  a_zero_series_y = new QLineSeries();
  a_zero_series_y->setPen(QPen((Qt::black),1));
  a_zero_series_y->setUseOpenGL(true);
  a_zero_series_y->append(0, -100);
  a_zero_series_y->append(0, 100);
  
  j_zero_series = new QLineSeries();
  j_zero_series->setPen(QPen((Qt::black),1));
  j_zero_series->setUseOpenGL(true);
  j_zero_series->append(-100, 0);
  j_zero_series->append(100, 0);
  
  j_zero_series_y = new QLineSeries();
  j_zero_series_y->setPen(QPen((Qt::black),1));
  j_zero_series_y->setUseOpenGL(true);
  j_zero_series_y->append(0, -100000);
  j_zero_series_y->append(0, 100000);
  
  v_max_series = new QLineSeries();
  v_max_series->setPen(QPen(Qt::red,1, Qt::DotLine));
  v_max_series->setUseOpenGL(true);
  v_max_series->append(-100, v_max);
  v_max_series->append(100, v_max);
  
  v_min_series = new QLineSeries();
  v_min_series->setPen(QPen(Qt::red,1, Qt::DotLine));
  v_min_series->setUseOpenGL(true);
  v_min_series->append(-100, -v_max);
  v_min_series->append(100, -v_max);
  
  a_max_series = new QLineSeries();
  a_max_series->setPen(QPen(Qt::red,1, Qt::DotLine));
  a_max_series->setUseOpenGL(true);
  a_max_series->append(-100, a_max);
  a_max_series->append(100, a_max);
  
  a_min_series = new QLineSeries();
  a_min_series->setPen(QPen(Qt::red,1, Qt::DotLine));
  a_min_series->setUseOpenGL(true);
  a_min_series->append(-100, -a_max);
  a_min_series->append(100, -a_max);
  
  j_max_series = new QLineSeries();
  j_max_series->setPen(QPen(Qt::red,1, Qt::DotLine));
  j_max_series->setUseOpenGL(true);
  j_max_series->append(-100, j_max);
  j_max_series->append(100, j_max);
  
  j_min_series = new QLineSeries();
  j_min_series->setPen(QPen(Qt::red,1, Qt::DotLine));
  j_min_series->setUseOpenGL(true);
  j_min_series->append(-100, -j_max);
  j_min_series->append(100, -j_max);

  
  s_chart = new QChart();
  s_series = new QLineSeries(s_chart);
  s_series->setUseOpenGL(true);
  s_chart->addSeries(s_series);
  s_chart->addSeries(s_zero_series);
  s_chart->addSeries(s_zero_series_y);
  s_chart->addSeries(s_bounds);
  s_chart->createDefaultAxes();
  s_chart->setTitle("Position");
  chartView = new QChartView(s_chart);
  baseLayout->addWidget(chartView, 1, 0);
  m_charts << chartView;
  
  v_chart = new QChart();
  v_series = new QLineSeries(v_chart);
  v_series->setUseOpenGL(true);
  v_chart->addSeries(v_series);
  v_chart->addSeries(v_zero_series);
  v_chart->addSeries(v_zero_series_y);
  v_chart->addSeries(v_max_series);
  v_chart->addSeries(v_min_series);
  v_chart->addSeries(v_bounds);
  v_chart->createDefaultAxes();
  v_chart->setTitle("Velocity");
  chartView = new QChartView(v_chart);
  baseLayout->addWidget(chartView, 1, 1);
  m_charts << chartView;
  
  a_chart = new QChart();
  a_series = new QLineSeries(a_chart);
  a_series->setUseOpenGL(true);
  a_chart->addSeries(a_series);
  a_chart->addSeries(a_zero_series);
  a_chart->addSeries(a_zero_series_y);
  a_chart->addSeries(a_max_series);
  a_chart->addSeries(a_min_series);
  a_chart->addSeries(a_bounds);
  a_chart->createDefaultAxes();
  a_chart->setTitle("Acceleration");
  chartView = new QChartView(a_chart);
  baseLayout->addWidget(chartView, 2, 0);
  m_charts << chartView;
  
  j_chart = new QChart();
  j_series = new QLineSeries(j_chart);
  j_series->setUseOpenGL(true);
  j_chart->addSeries(j_series);
  j_chart->addSeries(j_zero_series);
  j_chart->addSeries(j_zero_series_y);
  j_chart->addSeries(j_max_series);
  j_chart->addSeries(j_min_series);
  j_chart->createDefaultAxes();
  j_chart->setTitle("Jerk");
  chartView = new QChartView(j_chart);
  baseLayout->addWidget(chartView, 2, 1);
  m_charts << chartView;
  
//   re_print_curves();
  
  // create sliders    
  QGridLayout* sliders_layout = new QGridLayout();
  sliders_layout->addWidget(new QLabel("Start"),0,0);
  sliders_layout->addWidget(new QLabel("End"),0,1);
  sliders_layout->addWidget(new QLabel("Max"),0,2);
  
  slider_si = new QSlider(Qt::Horizontal);
  slider_si->setRange(-100,100);
  slider_si->setValue(s_init*100);
  QObject::connect(slider_si,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_si(int)));
  sliders_layout->addWidget(slider_si,1,0);
  
  slider_vi = new QSlider(Qt::Horizontal);
  slider_vi->setRange(-200,200);
  slider_vi->setValue(v_init*100);
  QObject::connect(slider_vi,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_vi(int)));
  sliders_layout->addWidget(slider_vi,2,0);
  
  slider_ai = new QSlider(Qt::Horizontal);
  slider_ai->setRange(-200,200);
  slider_ai->setValue(a_init*100);
  QObject::connect(slider_ai,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_ai(int)));
  sliders_layout->addWidget(slider_ai,3,0);
  
  slider_sf = new QSlider(Qt::Horizontal);
  slider_sf->setRange(100,300);
  slider_sf->setValue(s_final*100);
  QObject::connect(slider_sf,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_sf(int)));
  sliders_layout->addWidget(slider_sf,1,1);
  
  slider_vf = new QSlider(Qt::Horizontal);
  slider_vf->setRange(-200,200);
  slider_vf->setValue(v_final*100);
  QObject::connect(slider_vf,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_vf(int)));
  sliders_layout->addWidget(slider_vf,2,1);
  
  slider_af = new QSlider(Qt::Horizontal);
  slider_af->setRange(-200,200);
  slider_af->setValue(a_final*100);
  QObject::connect(slider_af,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_af(int)));
  sliders_layout->addWidget(slider_af,3,1);
  
  slider_vmax = new QSlider(Qt::Horizontal);
  slider_vmax->setRange(100,200);
  slider_vmax->setValue(v_max*100);
  QObject::connect(slider_vmax,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_vmax(int)));
  sliders_layout->addWidget(slider_vmax,1,2);
  
  slider_amax = new QSlider(Qt::Horizontal);
  slider_amax->setRange(100,300);
  slider_amax->setValue(a_max*100);
  QObject::connect(slider_amax,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_amax(int)));
  sliders_layout->addWidget(slider_amax,2,2);
  
  slider_jmax = new QSlider(Qt::Horizontal);
  slider_jmax->setRange(500,10000);
  slider_jmax->setValue(j_max*100);
  QObject::connect(slider_jmax,SIGNAL(valueChanged(int)),this,SLOT(callback_slider_jmax(int)));
  sliders_layout->addWidget(slider_jmax,3,2);
  
  baseLayout->addLayout(sliders_layout, 3, 0);
  
  QGridLayout* edits_layout = new QGridLayout();
  edits_layout->addWidget(new QLabel("Start"),0,0);
  edits_layout->addWidget(new QLabel("End"),0,1);
  edits_layout->addWidget(new QLabel("Max"),0,2);
  line_edit = new QLineEdit;
  QString text("0");
  line_edit->setText(text);
  line_edit->setValidator(new QDoubleValidator);
  line_edit->setFixedWidth(40);
  QObject::connect(line_edit,SIGNAL(textChanged(QString)),this,SLOT(callback_si_text_edit(QString)));
  
  edits_layout->addWidget(line_edit,1,0);
  
  baseLayout->addLayout(edits_layout,3,1);
  
  setLayout(baseLayout);

  // Set defaults
  m_antialiasCheckBox->setChecked(true);
  updateUI();
  
  re_print_curves();
}

SCurveQtWidget::~SCurveQtWidget()
{
}

void SCurveQtWidget::connectSignals()
{
    connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_antialiasCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_animatedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_legendComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
}

QComboBox *SCurveQtWidget::createThemeBox() const
{
    // settings layout
    QComboBox *themeComboBox = new QComboBox();
    themeComboBox->addItem("Light", QChart::ChartThemeLight);
    themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    themeComboBox->addItem("Qt", QChart::ChartThemeQt);
    return themeComboBox;
}

QComboBox *SCurveQtWidget::createAnimationBox() const
{
    // settings layout
    QComboBox *animationComboBox = new QComboBox();
    animationComboBox->addItem("No Animations", QChart::NoAnimation);
    animationComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    animationComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    animationComboBox->addItem("All Animations", QChart::AllAnimations);
    return animationComboBox;
}

QComboBox *SCurveQtWidget::createLegendBox() const
{
    QComboBox *legendComboBox = new QComboBox();
    legendComboBox->addItem("No Legend ", 0);
    legendComboBox->addItem("Legend Top", Qt::AlignTop);
    legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    legendComboBox->addItem("Legend Right", Qt::AlignRight);
    return legendComboBox;
}

void SCurveQtWidget::re_print_curves(){
  s_curve.compute_curves();
  s_series->clear();
  v_series->clear();
  a_series->clear();
  j_series->clear();
  
  if (s_curve.s_vect_.size()>0){
    qreal min_s, max_s, min_v, max_v, min_a, max_a;
    for(int i=0; i<s_curve.t_vect_.size()-1;i++){
      s_series->append(s_curve.t_vect_[i], s_curve.s_vect_[i]);
      v_series->append(s_curve.t_vect_[i], s_curve.v_vect_[i]);
      a_series->append(s_curve.t_vect_[i], s_curve.a_vect_[i]);
      j_series->append(s_curve.t_vect_[i], s_curve.j_vect_[i]);
      if (i==0){
        min_s = s_curve.s_vect_[i];
        max_s = s_curve.s_vect_[i];
        min_v = s_curve.v_vect_[i];
        max_v = s_curve.v_vect_[i];
        min_a = s_curve.a_vect_[i];
        max_a = s_curve.a_vect_[i];
      }
      else{
        min_s = qMin(min_s, s_curve.s_vect_[i]);
        max_s = qMax(max_s, s_curve.s_vect_[i]);
        min_v = qMin(min_v, s_curve.v_vect_[i]);
        max_v = qMax(max_v, s_curve.v_vect_[i]);
        min_a = qMin(min_a, s_curve.a_vect_[i]);
        max_a = qMax(max_a, s_curve.a_vect_[i]);
      }
    }

    v_min_series->clear();
    v_min_series->append(-100, -v_max);
    v_min_series->append(100, -v_max);
    
    v_max_series->clear();
    v_max_series->append(-100, v_max);
    v_max_series->append(100, v_max);
    
    a_max_series->clear();
    a_max_series->append(-100, a_max);
    a_max_series->append(100, a_max);
    
    a_min_series->clear();
    a_min_series->append(-100, -a_max);
    a_min_series->append(100, -a_max);
    
    j_max_series->clear();
    j_max_series->append(-100, j_max);
    j_max_series->append(100, j_max);
    
    j_min_series->clear();
    j_min_series->append(-100, -j_max);
    j_min_series->append(100, -j_max);
    
    s_bounds->clear();
    s_bounds->append(0, s_init);
    s_bounds->append(s_curve.t_vect_[s_curve.t_vect_.size()-1], s_final);
    
    v_bounds->clear();
    v_bounds->append(0, v_init);
    v_bounds->append(s_curve.t_vect_[s_curve.t_vect_.size()-1], v_final);
    
    a_bounds->clear();
    a_bounds->append(0, a_init);
    a_bounds->append(s_curve.t_vect_[s_curve.t_vect_.size()-1], a_final);
    
    s_chart->axisX()->setRange(-0.1,s_curve.t_vect_[s_curve.t_vect_.size()-1]+0.1);
    s_chart->axisY()->setRange(qMin(min_s*1.2,-0.2),max_s*1.2);
    v_chart->axisX()->setRange(-0.1,s_curve.t_vect_[s_curve.t_vect_.size()-1]+0.1);
    v_chart->axisY()->setRange(qMin(min_v*1.2,-0.2),qMax(v_max,max_v)*1.2);
    a_chart->axisX()->setRange(-0.1,s_curve.t_vect_[s_curve.t_vect_.size()-1]+0.1);
    a_chart->axisY()->setRange(-a_max*1.2,a_max*1.2);
    j_chart->axisX()->setRange(-0.1,s_curve.t_vect_[s_curve.t_vect_.size()-1]+0.1);
    j_chart->axisY()->setRange(-j_max*1.2,j_max*1.2);
  }
  update_sliders();
}

void SCurveQtWidget::update_sliders(){
  slider_si->setValue(s_curve.si_*100);
  slider_vi->setValue(s_curve.vi_*100);
  slider_ai->setValue(s_curve.ai_*100);
  slider_sf->setValue(s_curve.sf_*100);
  slider_vf->setValue(s_curve.vf_*100);
  slider_af->setValue(s_curve.af_*100);
  slider_vmax->setValue(s_curve.v_max_*100);
  slider_amax->setValue(s_curve.a_max_*100);
  slider_jmax->setValue(s_curve.j_max_*100);
}

void SCurveQtWidget::callback_si_text_edit ( QString text ) {
  s_init = text.toDouble();
  s_curve.set_s_init(s_init);
  re_print_curves();
}

void SCurveQtWidget::callback_slider_si ( int a ) {
  s_init = a /100.0;
  s_curve.set_s_init(s_init);
  line_edit->setText(QString::number(s_init));
  re_print_curves();
}
void SCurveQtWidget::callback_slider_vi ( int a ) {
  v_init = a /100.0;
  s_curve.set_v_init(v_init);
  re_print_curves();
}
void SCurveQtWidget::callback_slider_ai ( int a ) {
  a_init = a /100.0;
  s_curve.set_a_init(a_init);
  re_print_curves();
}
void SCurveQtWidget::callback_slider_sf ( int a ) {
  s_final = a/100.0;
  s_curve.set_s_final(s_final);
  re_print_curves();
}
void SCurveQtWidget::callback_slider_vf ( int a ) {
  v_final = a/100.0;
  s_curve.set_v_final(v_final);
  re_print_curves();
}
void SCurveQtWidget::callback_slider_af ( int a ) {
  a_final = a/100.0;
  s_curve.set_a_final(a_final);
  re_print_curves();
}
void SCurveQtWidget::callback_slider_vmax ( int a ) {
  v_max = a/100.0;
  s_curve.set_v_max(v_max);
  re_print_curves();
}
void SCurveQtWidget::callback_slider_amax ( int a ) {
  a_max = a/100.0;
  s_curve.set_a_max(a_max);
  re_print_curves();
}

void SCurveQtWidget::callback_slider_jmax ( int a ) {
  j_max = a/100.0;
  s_curve.set_j_max(j_max);
  re_print_curves();
}
void SCurveQtWidget::updateUI()
{
    QChart::ChartTheme theme = (QChart::ChartTheme) m_themeComboBox->itemData(m_themeComboBox->currentIndex()).toInt();

    if (m_charts.at(0)->chart()->theme() != theme) {
        foreach (QChartView *chartView, m_charts)
            chartView->chart()->setTheme(theme);

        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }

    bool checked = m_antialiasCheckBox->isChecked();
    foreach (QChartView *chart, m_charts)
        chart->setRenderHint(QPainter::Antialiasing, checked);

    QChart::AnimationOptions options(m_animatedComboBox->itemData(m_animatedComboBox->currentIndex()).toInt());
    if (m_charts.at(0)->chart()->animationOptions() != options) {
        foreach (QChartView *chartView, m_charts)
            chartView->chart()->setAnimationOptions(options);
    }

    Qt::Alignment alignment(m_legendComboBox->itemData(m_legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        foreach (QChartView *chartView, m_charts)
            chartView->chart()->legend()->hide();
    } else {
        foreach (QChartView *chartView, m_charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }
}