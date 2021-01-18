//
// Dialog for changing app settings
//

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "cell.h"
#include "colortab.h"
#include "screenshottab.h"
#include <QDialog>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTabWidget>

namespace Ui {
    // Main Dialog for changing settings
    class SettingsDialog : public QDialog {
        Q_OBJECT

    public:
        explicit SettingsDialog(QColor &outline, QColor &dead, QColor &alive, QWidget* parent = nullptr);


        signals:
        void updateChanges();


    private slots:
        /**
         * Closes the settings dialog.
         */
        void closeDialog();

        /**
         * Applies any changes made to settings. Does not close the dialog.
         */
        void applyChanges();

        /**
         * Applies any changes made to settings and closes the dialog.
         */
        void applyChangesAndClose();

    private:
        QTabWidget* tabWidget;
        QDialogButtonBox* box;
        QPushButton* okayButton;
        QPushButton* applyButton;
        QPushButton* cancelButton;
        ColorTab* colorTab;
        ScreenShotTab* screenShotTab;


        /**
         * Initializes the main widget and each tab for each setting item
         */
        void initializeTabs(QColor& outline, QColor& dead, QColor& alive);

        /**
         * Initializes the okay, apply and cancel buttons;
         */
        void initializeButtons();
    };
}
#endif //SETTINGSDIALOG_H
