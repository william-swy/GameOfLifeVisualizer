//
// Manipulable view for entire game board
//

#pragma once

#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>

class View : public QGraphicsView {
  Q_OBJECT
public:
  explicit View(QWidget* parent = nullptr);

public slots:
  /**
   * Resets app zoom level to default.
   */
  void reset_zoom();

protected:
  /**
   * Event listener to change app zoom level based on wheel scroll event. If consecutive zoom in or
   * zoom out times exceeds, `maxZoomInTimes` stop zoom in or zoom out respectively.
   * @param event The mouse wheel scroll event.
   */
  void wheelEvent(QWheelEvent* event) override;

private:
  qreal scale_factor;
  qint32 max_zoom_in_times;
  qint32 curr_zoom_in_times;
};
