//
// Manipulable view for entire game board
//

#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>


class View : public QGraphicsView{
    Q_OBJECT
public:
    explicit View(QWidget* parent = nullptr);

public slots:
    void resetZoom();

protected:
    void wheelEvent(QWheelEvent* event) override;

private:
    double scaleFactor;
    int maxZoomInTimes;
    int currZoomInTimes;
};


#endif //VIEW_H
