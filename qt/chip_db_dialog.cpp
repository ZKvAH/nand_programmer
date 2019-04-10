#include "chip_db_dialog.h"
#include "ui_chip_db_dialog.h"

#define HEADER_LONG_WIDTH 100
#define HEADER_SHORT_WIDTH 50

ChipDbDialog::ChipDbDialog(ChipDb *chipDb, QWidget *parent) : QDialog(parent),
    ui(new Ui::ChipDbDialog), chipDbTableModel(chipDb, parent)
{
    ui->setupUi(this);
    chipDbProxyModel.setSourceModel(&chipDbTableModel);
    ui->chipDbTableView->setModel(&chipDbProxyModel);
    ui->chipDbTableView->setColumnWidth(CHIP_PARAM_NAME, HEADER_LONG_WIDTH);
    ui->chipDbTableView->setColumnWidth(CHIP_PARAM_PAGE_SIZE,
        HEADER_LONG_WIDTH);
    ui->chipDbTableView->setColumnWidth(CHIP_PARAM_BLOCK_SIZE,
        HEADER_LONG_WIDTH);
    ui->chipDbTableView->setColumnWidth(CHIP_PARAM_SIZE, HEADER_LONG_WIDTH);
    for (int i = CHIP_PARAM_SIZE + 1; i < CHIP_PARAM_NUM; i++)
        ui->chipDbTableView->setColumnWidth(i, HEADER_SHORT_WIDTH);

    connect(ui->addChipDbButton, SIGNAL(clicked()), this,
        SLOT(slotAddChipDbButtonClicked()));
    connect(ui->delChipDbButton, SIGNAL(clicked()), this,
        SLOT(slotDelChipDbButtonClicked()));
    connect(ui->okCancelButtonBox->button(QDialogButtonBox::Ok),
        SIGNAL(clicked()), this, SLOT(slotOkButtonClicked()));
    connect(ui->okCancelButtonBox->button(QDialogButtonBox::Cancel),
        SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
}

ChipDbDialog::~ChipDbDialog()
{
    delete ui;
}

void ChipDbDialog::slotAddChipDbButtonClicked()
{
    chipDbTableModel.addRow();
}

void ChipDbDialog::slotDelChipDbButtonClicked()
{
    QModelIndexList selection = ui->chipDbTableView->selectionModel()->
        selectedRows();

    if (!selection.count())
        return;

    chipDbTableModel.delRow(selection.at(0).row());
}

void ChipDbDialog::slotOkButtonClicked()
{
    chipDbTableModel.commit();
}

void ChipDbDialog::slotCancelButtonClicked()
{
    chipDbTableModel.reset();
}
