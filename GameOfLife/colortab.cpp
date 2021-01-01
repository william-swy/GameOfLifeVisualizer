#include "colortab.h"
#include <QGridLayout>
#include <QColorDialog>


Ui::ColorTab::ColorTab(QColor& outline, QColor& dead, QColor& alive, QWidget *parent) : QWidget(parent){
    outlineColor = &outline;
    deadColor = &dead;
    aliveColor = &alive;

    // color labels
    deadCellColor = new QLabel(this);
    aliveCellColor = new QLabel(this);
    edgeColor = new QLabel(this);

    // color buttons
    deadCellButton = new QPushButton(this);
    aliveCellButton = new QPushButton(this);
    edgeButton = new QPushButton(this);
    reset = new QPushButton(this);

    // set text
    deadCellColor->setText(tr("Dead Cell Colour"));
    aliveCellColor->setText(tr("Alive Cell Colour"));
    edgeColor->setText(tr("Cell Edge Colour"));
    reset->setText(tr("Reset Colors"));

    setInitialColors();

    auto* gridLayout = new QGridLayout;
    gridLayout->addWidget(deadCellColor, 0,0,1,1);
    gridLayout->addWidget(aliveCellColor, 1,0,1,1);
    gridLayout->addWidget(edgeColor, 2,0,1,1);
    gridLayout->addWidget(deadCellButton, 0, 1, 1,1);
    gridLayout->addWidget(aliveCellButton, 1, 1, 1,1);
    gridLayout->addWidget(edgeButton, 2, 1, 1,1);
    gridLayout->addWidget(new QWidget, 3,0,1,1);
    gridLayout->addWidget(reset,3,1,1,1);
    setLayout(gridLayout);

    initializeConnections();

    tmpOutline = *outlineColor;
    tmpDead = *deadColor;
    tmpAlive = *aliveColor;
}

void Ui::ColorTab::setInitialColors() {
    QString outlineCol = QString("background-color: %1").arg(outlineColor->name());
    QString deadCol = QString("background-color: %1").arg(deadColor->name());
    QString aliveCol = QString("background-color: %1").arg(aliveColor->name());
    edgeButton->setStyleSheet(outlineCol);
    deadCellButton->setStyleSheet(deadCol);
    aliveCellButton->setStyleSheet(aliveCol);
}

void Ui::ColorTab::applyColorChanges() {
    *outlineColor = tmpOutline;
    *deadColor = tmpDead;
    *aliveColor = tmpAlive;
}

void Ui::ColorTab::changeOutlineColor() {
    QColor out = QColorDialog::getColor();
    if (out.isValid()) {
        QString outlineCol = QString("background-color: %1").arg(out.name());
        edgeButton->setStyleSheet(outlineCol);
        tmpOutline = out;
    }
}

void Ui::ColorTab::changeDeadColor() {
    QColor dead = QColorDialog::getColor();
    if (dead.isValid()) {
        QString deadCol = QString("background-color: %1").arg(dead.name());
        deadCellButton->setStyleSheet(deadCol);
        tmpDead = dead;
    }
}

void Ui::ColorTab::changeAliveColor() {
    QColor alive = QColorDialog::getColor();
    if (alive.isValid()) {
        QString aliveCol = QString("background-color: %1").arg(alive.name());
        aliveCellButton->setStyleSheet(aliveCol);
        tmpAlive = alive;
    }
}

void Ui::ColorTab::initializeConnections() {
    connect(deadCellButton, SIGNAL(clicked(bool)), this, SLOT(changeDeadColor()));
    connect(aliveCellButton, SIGNAL(clicked(bool)), this, SLOT(changeAliveColor()));
    connect(edgeButton, SIGNAL(clicked(bool)), this, SLOT(changeOutlineColor()));
    connect(reset, SIGNAL(clicked(bool)), this, SLOT(resetColors()));
}

void Ui::ColorTab::resetColors() {
    tmpOutline = QColor(Qt::black);
    tmpDead = QColor(Qt::white);
    tmpAlive = QColor(Qt::black);
}
