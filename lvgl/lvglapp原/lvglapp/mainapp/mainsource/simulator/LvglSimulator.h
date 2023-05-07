#ifndef LVGLSIMULATOR_H
#define LVGLSIMULATOR_H

#include  "lvgl/lvgl.h"
#include  "lv_cpp/core/lvcpp_startup.h"
#include  "mainstart/mainappstart.h"

#if QTSIM_PLATFORM

#include  <QGraphicsScene>
#include  <QGraphicsView>
#include  <QTimer>

#include  "serialtool.h"

class LvglScene : public QGraphicsScene
{
  Q_OBJECT
 public:
  LvglScene(LvcppStartupSYS* API, QObject *parent = nullptr);

 protected:
  virtual void drawBackground(QPainter *painter, const QRectF &rect) override;

 private:
  LvcppStartupSYS* lvglAPI;
};

class LvglSimulator : public QGraphicsView
{
  Q_OBJECT
 public:
  explicit LvglSimulator(QWidget *parent = nullptr);
  ~LvglSimulator() override;

  void threadstop();
  void restartconnect();
  void setZoomLevel(int level);
  QSize get_size(void) {return simu_size;}

  void  start_serialtool(void);

  void Exec(void);

 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;


public slots:
  void  serial_button();
  //void  serial_recvdata();

private slots:
  void  update_scene();
  void  update_lvgl();


 private:
  LvcppStartupSYS* lvglSYS;
  MainAPPStart* lvglAPP;
  LvcppMainScreen* mainscreen;

  SerialTool* serialtool;

  LvglScene* m_scene;
  QSize simu_size;

  QTimer *m_timer_5ms;
  QTimer *m_timer_15ms;

  LvcppStartupSYS* sysInitial(void);
};

#endif

#endif  // LVGLSIMULATOR_H
