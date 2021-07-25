//
// Manipulable view for entire game board
//

#pragma once

#include <QGraphicsView>

class View : public QGraphicsView {
  Q_OBJECT
public:
  explicit View(QWidget* parent = nullptr);

public slots:
  /**
   * Resets app zoom level to default.
   */
  void resetZoom();

protected:
  /**
   * Event listener to change app zoom level based on wheel scroll event. If consecutive zoom in or
   * zoom out times exceeds, `maxZoomInTimes` stop zoom in or zoom out respectively.
   * @param event The mouse wheel scroll event.
   */
  void wheelEvent(QWheelEvent* event) override;

private:
  double scaleFactor;
  int maxZoomInTimes;
  int currZoomInTimes;
};
