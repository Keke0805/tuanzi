#include "LvglSimulator.h"

#if QTSIM_PLATFORM

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

LvglScene::LvglScene(LvcppStartupSYS* API, QObject *parent) : QGraphicsScene(parent)
{
    lvglAPI = API;
}

void LvglScene::drawBackground(QPainter *painter, const QRectF &rect)
{
  painter->save();

  m_buffer_fbdisp_t m_buf = lvglAPI->framer_buff();
  QImage img(m_buf.size.width, m_buf.size.height, QImage::Format_ARGB32);
  memcpy(img.bits(), m_buf.buf, m_buf.length);
  QPixmap img_bmp = QPixmap::fromImage(img);
  painter->drawPixmap(sceneRect(), img_bmp, rect);

  painter->setPen(Qt::black);
  painter->setBrush(Qt::NoBrush);
  painter->drawRect(sceneRect());
  painter->restore();

}

LvglSimulator::LvglSimulator(QWidget *parent) : QGraphicsView(parent)
{
  lvglSYS = sysInitial();
  simu_size.setWidth(lvglSYS->get_width());
  simu_size.setHeight(lvglSYS->get_height());
  this->resize(simu_size.width()+10,simu_size.height()+10);

  m_scene = new LvglScene(lvglSYS, this);
  m_scene->setSceneRect(0, 0, simu_size.width(),simu_size.height());

  setScene(m_scene);

  m_timer_15ms = new QTimer(this);
  connect(m_timer_15ms, &QTimer::timeout, this, &LvglSimulator::update_scene);
  m_timer_15ms->start(15);

  m_timer_5ms = new QTimer(this);
  connect(m_timer_5ms, &QTimer::timeout, this, &LvglSimulator::update_lvgl);
  m_timer_5ms->start(5);

  setCacheMode(QGraphicsView::CacheBackground);

  mainscreen = nullptr;
}

LvglSimulator::~LvglSimulator()
{
  delete m_timer_15ms;
  delete m_timer_5ms;
  delete m_scene;
}

LvcppStartupSYS* LvglSimulator::sysInitial(void)
{
    simu_size.setWidth(SCREEN_HOR_SIZE);
    simu_size.setHeight(SCREEN_VER_SIZE);
    LvcppStartupSYS* lvglOpt = new LvcppStartupSYS(simu_size.width(), simu_size.height());
    lvglOpt->sysfont_init(DEFAULT_FONT_NAME, DEFAULT_FONT_SIZE, DEFAULT_FONT_TYPE);

    lvglOpt->display_init(LV_DISP_ROT_NONE);

    return lvglOpt;
}

void LvglSimulator::start_serialtool(void)
{
    if(mainscreen == nullptr)
    {
       mainscreen = lvglSYS->mainScreen();
    }

    serialtool = new SerialTool(mainscreen->get_obj());
    connect(serialtool, &SerialTool::button_send, this, &LvglSimulator::serial_button);
}

void LvglSimulator::serial_button()
{
    Exec();
}

void LvglSimulator::Exec(void)
{
    if(mainscreen == nullptr)
    {
       mainscreen = lvglSYS->mainScreen();
    }

    lvglAPP = new MainAPPStart(mainscreen);
}

void LvglSimulator::setZoomLevel(int level)
{
  QTransform transform;
  const qreal zoom = (level < 0 ? ((10.0 + level + 0.5) / 10) : (level == 0 ? 1 : 1.0 + 0.05 * level));
  transform.scale(zoom, zoom);
  qDebug() << "Zoom:" << zoom;
  setTransform(transform);
}

void LvglSimulator::mousePressEvent(QMouseEvent *event)
{
   const QPoint pos = mapToScene(event->pos()).toPoint();
   if((pos.x() >= 0)&&(pos.y() >= 0)&&(pos.x() <= simu_size.width())&&((pos.y() <= simu_size.height())))
   {
       if(event->buttons() == Qt::LeftButton)
       {
          lvglSYS->updateMouseStatus(pos.x(), pos.y(), LV_INDEV_STATE_PR);
       }
   }

   QGraphicsView::mousePressEvent(event);
}

void LvglSimulator::mouseDoubleClickEvent(QMouseEvent *event)
{
  QGraphicsView::mouseDoubleClickEvent(event);
}

void LvglSimulator::mouseReleaseEvent(QMouseEvent *event)
{
  const QPoint pos = mapToScene(event->pos()).toPoint();
  lvglSYS->updateMouseStatus(pos.x(), pos.y(), LV_INDEV_STATE_REL);

  QGraphicsView::mouseReleaseEvent(event);
}

void LvglSimulator::mouseMoveEvent(QMouseEvent *event)
{
   const QPoint pos = mapToScene(event->pos()).toPoint();
   if((pos.x() >= 0)&&(pos.y() >= 0)&&(pos.x() <= simu_size.width())&&((pos.y() <= simu_size.height())))
   {
       if(event->buttons() == Qt::LeftButton)
       {
          lvglSYS->updateMouseStatus(pos.x(), pos.y(), LV_INDEV_STATE_PR);
       }
   }

   QGraphicsView::mouseMoveEvent(event);
}

void LvglSimulator::update_scene()
{
   m_scene->invalidate(m_scene->sceneRect(), QGraphicsScene::BackgroundLayer);
}

void LvglSimulator::update_lvgl()
{
   lvglSYS->tick_event();
}

#endif
