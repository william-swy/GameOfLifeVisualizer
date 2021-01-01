#include "settingsdialog.h"
#include <QGridLayout>
#include <QVBoxLayout>

Ui::SettingsDialog::SettingsDialog(QColor &outline, QColor &dead, QColor &alive, QWidget *parent)
    : QDialog(parent) {
    initializeTabs(outline, dead, alive);
    initializeButtons();
    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(box);
    setLayout(mainLayout);
    setWindowTitle(QDialog::tr("Settings"));
    setMinimumSize(400, 400);
}

void Ui::SettingsDialog::initializeTabs(QColor& outline, QColor& dead, QColor& alive)
{
    tabWidget = new QTabWidget(this);
    colorTab = new ColorTab(outline, dead, alive, this);
    screenShotTab = new ScreenShotTab(this);
    tabWidget->addTab(colorTab, tr("Colour"));
    tabWidget->addTab(screenShotTab, tr("Recording"));
}

void Ui::SettingsDialog::initializeButtons() {
    // okay button settings
    okayButton = new QPushButton(this);
    okayButton->setText(tr("Okay"));

    // apply button settings
    applyButton = new QPushButton(this);
    applyButton->setText(tr("Apply"));

    // cancel button settings
    cancelButton = new QPushButton(this);
    cancelButton->setText(tr("Cancel"));

    // button box to hold all the buttons
    box = new QDialogButtonBox(Qt::Horizontal);
    box->addButton(okayButton, QDialogButtonBox::AcceptRole);
    box->addButton(applyButton, QDialogButtonBox::ApplyRole);
    box->addButton(cancelButton, QDialogButtonBox::RejectRole);

    // connect signals for buttons
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(closeDialog()));
    connect(okayButton, SIGNAL(clicked(bool)), this, SLOT(applyChangesAndClose()));
    connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(applyChanges()));
}

void Ui::SettingsDialog::closeDialog() {
    close();
}

void Ui::SettingsDialog::applyChanges() {
    colorTab->applyColorChanges();
    emit updateChanges();
}

void Ui::SettingsDialog::applyChangesAndClose() {
    colorTab->applyColorChanges();
    emit updateChanges();
    close();
}
