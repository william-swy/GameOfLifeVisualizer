//
// tab to change the color the gameBoard
//

#ifndef COLORTAB_H
#define COLORTAB_H

#include <QColor>
#include <QLabel>
#include <QPushButton>

namespace Ui {
    class ColorTab : public QWidget{
        Q_OBJECT

    public:
        explicit ColorTab(QColor& outline, QColor& dead, QColor& alive, QWidget* parent = nullptr);

        void applyColorChanges();

    private slots:
        /**
         * Prompts a dialog to change the color of the outline
         */
        void changeOutlineColor();
        void changeDeadColor();
        void changeAliveColor();
        void resetColors();

    private:
        QLabel *deadCellColor;
        QLabel *aliveCellColor;
        QLabel *edgeColor;

        QPushButton *deadCellButton;
        QPushButton *aliveCellButton;
        QPushButton *edgeButton;
        QPushButton *reset;

        QColor* outlineColor;
        QColor* deadColor;
        QColor* aliveColor;

        QColor tmpOutline;
        QColor tmpDead;
        QColor tmpAlive;

        /**
         * Sets the colors of the buttons
         */
        void setInitialColors();

        /**
         * Connects signals from buttons to the slots of ColorTab.
         */
        void initializeConnections();
    };
}



#endif //COLORTAB_H
