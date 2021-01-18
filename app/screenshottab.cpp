//
// Created by bigblue on 2021-01-01.
//

#include "screenshottab.h"
#include <QGridLayout>


Ui::ScreenShotTab::ScreenShotTab(QWidget *parent) : QWidget(parent){
    // label initialize
    frameRate = new QLabel(this);
    width = new QLabel(this);
    height = new QLabel(this);

    // spinbox initialize
    frameSpin = new QSpinBox(this);
    widthSpin = new QSpinBox(this);
    heightSpin = new QSpinBox(this);

    // checkbox initialize
    widthCheck = new QCheckBox(this);
    heightCheck = new QCheckBox(this);

    reset = new QPushButton(this);
    reset->setText(tr("Reset Recording Settings"));

    // label setup
    setupLabels();

    // checkbox setup
    setupCheckboxes();

    // spinbox setup
    setupSpinboxes();

    auto* gridLayout = new QGridLayout;
    gridLayout->addWidget(frameRate, 0,0,1,1);
    gridLayout->addWidget(width, 1,0,1,1);
    gridLayout->addWidget(height, 2,0,1,1);
    gridLayout->addWidget(frameSpin,0,1,1,1);
    gridLayout->addWidget(widthSpin, 1, 1, 1,1);
    gridLayout->addWidget(heightSpin, 2, 1, 1,1);
    gridLayout->addWidget(new QWidget, 0,2,1,1);
    gridLayout->addWidget(widthCheck, 1, 2, 1,1);
    gridLayout->addWidget(heightCheck, 2, 2, 1,1);
    gridLayout->addWidget(new QWidget, 3,1,1,2);
    gridLayout->addWidget(reset,3,2,1,1);
    setLayout(gridLayout);
}

void Ui::ScreenShotTab::setupLabels() {
    frameRate->setText(tr("Framerate (fps)"));
    width->setText("Output Width (px)");
    height->setText("Output Height (px)");
}

void Ui::ScreenShotTab::setupCheckboxes() {
    widthCheck->setText(tr("Keep Width Aspect Ratio"));
    heightCheck->setText(tr("Keep Height Aspect Ratio"));
    widthCheck->setChecked(true);
    heightCheck->setChecked(true);

    connect(widthCheck, SIGNAL(stateChanged(int)), this, SLOT(widthTicked()));
    connect(heightCheck, SIGNAL(stateChanged(int)), this, SLOT(heightTicked()));
}

void Ui::ScreenShotTab::setupSpinboxes() {
    frameSpin->setMinimum(minDim);
    frameSpin->setMaximum(maxDim);
    frameSpin->setValue(10);

    widthSpin->setMinimum(minDim);
    widthSpin->setMaximum(maxDim);
    widthSpin->setEnabled(false);

    heightSpin->setMinimum(minDim);
    heightSpin->setMaximum(maxDim);
    heightSpin->setEnabled(false);
}

void Ui::ScreenShotTab::widthTicked() {
    if (widthSpin->isEnabled())
        widthSpin->setEnabled(false);
    else
        widthSpin->setEnabled(true);
}

void Ui::ScreenShotTab::heightTicked() {
    if(heightSpin->isEnabled())
        heightSpin->setEnabled(false);
    else
        heightSpin->setEnabled(true);
}