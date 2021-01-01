//
// tab to change the screen recording settings
//

#ifndef SCREENSHOTTAB_H
#define SCREENSHOTTAB_H

#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>

namespace Ui {
    class ScreenShotTab : public QWidget{
        Q_OBJECT

    public:
        explicit ScreenShotTab(QWidget* parent = nullptr);

        signals:
            /**
             * Signals that the framerate for GIF generation has changed.
             * @param val The value that the framerate has changed to.
             */
            void framerateChanged(int val);

        /**
         * Signals that the dimension of the generated GIF has changed.
         * @param width The width of the output GIF in pixels. -1 for keep aspect ratio.
         * @param height The height of the output GIF in pixels. -1 for keep aspect ratio.
         */
        void dimChanged(int width, int height);

    private slots:
        /**
         * Sets widthSpin to the opposite state. From enabled to disabled or from disabled to enabled.
         */
        void widthTicked();

        /**
         * Sets heightSpin to the opposite state. From enabled to disabled or from disabled to enabled.
         */
        void heightTicked();

    private:
        const int minDim = 1;
        const int maxDim = 3000;

        QLabel *frameRate;
        QLabel *width;
        QLabel *height;

        QSpinBox *frameSpin;
        QSpinBox *widthSpin;
        QSpinBox *heightSpin;

        QCheckBox *widthCheck;
        QCheckBox *heightCheck;

        /**
         * Sets label descriptions
         */
        void setupLabels();

        /**
         * Sets checkbox descriptions
         */
        void setupCheckboxes();

        /**
         * Sets spinboxes valid ranges
         */
        void setupSpinboxes();
    };
}

#endif //SCREENSHOTTAB_H
