#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <boost/algorithm/string.hpp>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this); // This connects the .ui file with the class

    connect(ui->Bt_NewOrder, &QPushButton::clicked, this, &MainWindow::Bt_NewOrderClicked);

    connect(ui->Bt_GetNextDesertEntry, &QPushButton::clicked, this, &MainWindow::Bt_GetNextDesertEntry);
    connect(ui->Bt_GetNextDriknsEntry, &QPushButton::clicked, this, &MainWindow::Bt_GetNextDrinksEntry);
    connect(ui->Bt_GetNextFriesEntry, &QPushButton::clicked, this, &MainWindow::Bt_GetNextFriesEntry);
    connect(ui->Bt_GetNextSaladEntry, &QPushButton::clicked, this, &MainWindow::Bt_GetNextSaladEntry);
    connect(ui->Bt_GetNextGrillEntry, &QPushButton::clicked, this, &MainWindow::Bt_GetNextGrillEntry);

    connect(ui->Bt_AddNewProduct, &QPushButton::clicked, this, &MainWindow::Bt_AddNewProduct);

    Cb_PopulateNewProductArea(ui->Cb_NewProductArea);

    Tv_ProductsModel = new QStandardItemModel(this);
    Tv_ProductsModel->setHorizontalHeaderLabels({ "Id", "Area", "Name" });
    ui->Tv_Products->setModel(Tv_ProductsModel);
    ui->Tv_Products->resizeColumnsToContents();


    Lv_DesertEntriesModel = new QStandardItemModel(this);
    ui->Lv_DesertEntries->setModel(Lv_DesertEntriesModel);

    Lv_DrinkEntriesModel = new QStandardItemModel(this);
    ui->Lv_DrinksEntries->setModel(Lv_DrinkEntriesModel);

    Lv_FriesEntriesModel = new QStandardItemModel(this);
    ui->Lv_FriesEntries->setModel(Lv_FriesEntriesModel);

    Lv_SaladEntriesModel = new QStandardItemModel(this);
    ui->Lv_SaladEntries->setModel(Lv_SaladEntriesModel);

    Lv_GrillEntriesModel = new QStandardItemModel(this);
    ui->Lv_GrillEntries->setModel(Lv_GrillEntriesModel);



    PopulateProductsView();
    PopulateEntriesView();
}


/// <summary>
/// Updates Entries
/// </summary>
void MainWindow::PopulateEntriesView()
{    
    Lv_DesertEntriesModel->clear();

    QList<KEntries> KDesertEntries;

    auto DesertEntries = KitchenOrders.ReadAreaEntries(Support::Desert);

    if (!DesertEntries.empty())
    {
        for (auto Entries : DesertEntries)
        {
            KDesertEntries.append(KEntries(QString::fromStdString(Entries.Product.Name)));
        }

        // Preencher o TableView com os produtos
        foreach(const KEntries & Entry, KDesertEntries) {
            QStandardItem* Item = new QStandardItem(Entry.GetName());
            Lv_DesertEntriesModel->appendRow(Item);
        }
    }


    Lv_DrinkEntriesModel->clear();

    QList<KEntries> KDrinksEntries;

    auto DrinkEntries = KitchenOrders.ReadAreaEntries(Support::Drink);

    if (!DrinkEntries.empty())
    {
        for (auto Entries : DrinkEntries)
        {
            KDrinksEntries.append(KEntries(QString::fromStdString(Entries.Product.Name)));
        }

        // Preencher o TableView com os produtos
        foreach(const KEntries & Entry, KDrinksEntries) {
            QStandardItem* Item = new QStandardItem(Entry.GetName());
            Lv_DrinkEntriesModel->appendRow(Item);
        }
    }


    Lv_FriesEntriesModel->clear();

    QList<KEntries> KFriesEntries;

    auto FriesEntries = KitchenOrders.ReadAreaEntries(Support::Fries);

    if (!FriesEntries.empty())
    {
        for (auto Entries : FriesEntries)
        {
            KFriesEntries.append(KEntries(QString::fromStdString(Entries.Product.Name)));
        }

        // Preencher o TableView com os produtos
        foreach(const KEntries & Entry, KFriesEntries) {
            QStandardItem* Item = new QStandardItem(Entry.GetName());
            Lv_FriesEntriesModel->appendRow(Item);
        }
    }


    Lv_SaladEntriesModel->clear();

    QList<KEntries> KSaladEntries;

    auto SaladEntries = KitchenOrders.ReadAreaEntries(Support::Salad);

    if (!SaladEntries.empty())
    {
        for (auto Entries : SaladEntries)
        {
            KSaladEntries.append(KEntries(QString::fromStdString(Entries.Product.Name)));
        }

        // Preencher o TableView com os produtos
        foreach(const KEntries & Entry, KSaladEntries) {
            QStandardItem* Item = new QStandardItem(Entry.GetName());
            Lv_SaladEntriesModel->appendRow(Item);
        }
    }


    Lv_GrillEntriesModel->clear();

    QList<KEntries> KGrillEntries;

    auto GrillEntries = KitchenOrders.ReadAreaEntries(Support::Grill);

    if (!GrillEntries.empty())
    {
        for (auto Entries : GrillEntries)
        {
            KGrillEntries.append(KEntries(QString::fromStdString(Entries.Product.Name)));
        }

        // Preencher o TableView com os produtos
        foreach(const KEntries & Entry, KGrillEntries) {
            QStandardItem* Item = new QStandardItem(Entry.GetName());
            Lv_GrillEntriesModel->appendRow(Item);
        }
    }
}

/// <summary>
/// Updates Products 
/// </summary>
void MainWindow::PopulateProductsView()
{
    // Criar uma lista de objetos KProducts
    QList<KProducts> products;

    for (auto [Area, Products] : Storage.PStorages)
    {
        for (auto Product : Products)
        {
            products.append(KProducts(Product.Id, QString::fromStdString(Support::KitchenAreasName(Area)), QString::fromStdString(Product.Name)));
        }
    }

    // Limpar o modelo
    Tv_ProductsModel->clear();

    // Definir novamente os cabeçalhos das colunas após limpar o modelo
    Tv_ProductsModel->setHorizontalHeaderLabels({ "Id", "Area", "Name" });

    // Preencher o TableView com os produtos
    for (const KProducts& product : products) {
        QList<QStandardItem*> rowItems;

        int Id = product.GetId();
        QString Name = product.GetName();
        QString Area = product.GetArea();

        rowItems.append(new QStandardItem(QString::number(Id)));
        rowItems.append(new QStandardItem(Name));
        rowItems.append(new QStandardItem(Area));

        Tv_ProductsModel->appendRow(rowItems);
    }
}

/// <summary>
/// Creates a new order
/// </summary>

void MainWindow::Bt_NewOrderClicked() {

    QModelIndexList SelectedRows = ui->Tv_Products->selectionModel()->selectedRows();


    if (SelectedRows.isEmpty())
    {
        QMessageBox::warning(this, "Aviso", "Select the products from list above");
        return;
    }

    QString SelectedItems;


    std::list<KitchenEntry> Entries = std::list<KitchenEntry>();

    foreach(const QModelIndex & index, SelectedRows)
    {
        int Id = ui->Tv_Products->model()->data(ui->Tv_Products->model()->index(index.row(), 0)).toInt();
        /*QString name = ui->Tv_Products->model()->data(ui->Tv_Products->model()->index(index.row(), 1)).toString();
        QString area = ui->Tv_Products->model()->data(ui->Tv_Products->model()->index(index.row(), 2)).toString();
        SelectedItems += QString("Row %1: Id %2, %3, %4\n").arg(index.row() + 1).arg(id).arg(name).arg(area);*/


        int OrderId = rand();
        KitchenProduct Prod = Storage.GetProduct(Id);

        if (Prod.Id != 0)
        {
            KitchenEntry Entry = KitchenEntry(OrderId, Prod);

            Entries.push_front(Entry);
        }
    }

    if (!Entries.empty())
    {
        KitchenOrders.NewOrder(Entries);

        PopulateEntriesView();
    }


    ui->Tv_Products->clearSelection();


    //// Exibir uma mensagem de informação
    //QMessageBox::information(this, "Informação", "Esta é uma mensagem de informação.");

    //// Exibir uma mensagem de aviso
    //QMessageBox::warning(this, "Aviso", "Esta é uma mensagem de aviso.");

    //// Exibir uma mensagem de erro crítico
    //QMessageBox::critical(this, "Erro Crítico", "Esta é uma mensagem de erro crítico.");

    //// Exibir uma mensagem de pergunta
    //QMessageBox::StandardButton reply;
    //reply = QMessageBox::question(this, "Pergunta", "Você quer continuar?",
    //    QMessageBox::Yes | QMessageBox::No);
    //if (reply == QMessageBox::Yes) {
    //    QMessageBox::information(this, "Continuar", "Você escolheu continuar.");
    //}
    //else {
    //    QMessageBox::information(this, "Parar", "Você escolheu parar.");
    //}
}

/// <summary>
/// Get next entry on the Desert Area
/// </summary>
void MainWindow::Bt_GetNextDesertEntry()
{
    try
    {
        KitchenEntry Entry = KitchenOrders.GetAndRemoveNextEntry(Support::Desert);

        ui->La_CurrentDesertEntry->setText(QString::fromStdString(Entry.Product.Name));
    }
    catch (const std::exception& Error)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(Error.what()));
    }

    PopulateEntriesView();
}

/// <summary>
/// Get next entry on the Drinks Area
/// </summary>
void MainWindow::Bt_GetNextDrinksEntry()
{
    try
    {
        KitchenEntry Entry = KitchenOrders.GetAndRemoveNextEntry(Support::Drink);

        ui->La_CurrentDrinksEntry->setText(QString::fromStdString(Entry.Product.Name));
    }
    catch (const std::exception& Error)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(Error.what()));
    }

    PopulateEntriesView();
}

/// <summary>
/// Get next entry on the Fries Area
/// </summary>
void MainWindow::Bt_GetNextFriesEntry()
{
    try
    {
        KitchenEntry Entry = KitchenOrders.GetAndRemoveNextEntry(Support::Fries);

        ui->La_CurrentFriesEntry->setText(QString::fromStdString(Entry.Product.Name));
    }
    catch (const std::exception& Error)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(Error.what()));
    }

    PopulateEntriesView();
}

/// <summary>
/// Get next entry on the Grill Area
/// </summary>
void MainWindow::Bt_GetNextGrillEntry()
{
    try
    {
        KitchenEntry Entry = KitchenOrders.GetAndRemoveNextEntry(Support::Grill);

        ui->La_CurrentGrillEntry->setText(QString::fromStdString(Entry.Product.Name));
    }
    catch (const std::exception& Error)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(Error.what()));
    }

    PopulateEntriesView();
}

/// <summary>
/// Get next entry on the Salad Area
/// </summary>
void MainWindow::Bt_GetNextSaladEntry()
{
    try
    {
        KitchenEntry Entry = KitchenOrders.GetAndRemoveNextEntry(Support::Salad);

        ui->La_CurrentSaladEntry->setText(QString::fromStdString(Entry.Product.Name));
    }
    catch (const std::exception& Error)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(Error.what()));
    }

    PopulateEntriesView();
}


/// <summary>
/// Add new product to kitchen area
/// </summary>
void MainWindow::Bt_AddNewProduct()
{
    if(ui->Te_NewProductName->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Type the new product name. For multiple products use ;");
    }
    else 
    {
        std::list<std::string> SplitedString;

        try
        {
            Support::KitchenAreas SelectedArea = static_cast<Support::KitchenAreas>(ui->Cb_NewProductArea->currentData().toInt());

            boost::split(SplitedString, ui->Te_NewProductName->toPlainText().toStdString(), boost::is_any_of(std::string(1, ';')));

            std::list<KitchenProduct> NewProducts;

            for (auto NewProd : SplitedString)
            {
                NewProducts.push_front(KitchenProduct(NewProd, SelectedArea));
            }

            Storage.NewAreaProducts(NewProducts);

            ui->Te_NewProductName->clear();

            PopulateProductsView();
        }
        catch (const std::exception& Error)
        {
            QMessageBox::critical(this, "Error", "There is a error in the products names. For multiple products use ;");
            return;
        }
    }

}


/// <summary>
/// Add the kitchen areas to ComboBox on init
/// </summary>
void MainWindow::Cb_PopulateNewProductArea(QComboBox* ComboBox) {
    ComboBox->addItem(QString::fromStdString(Support::KitchenAreasName(Support::Fries)), QVariant(Support::Fries));
    ComboBox->addItem(QString::fromStdString(Support::KitchenAreasName(Support::Grill)), QVariant(Support::Grill));
    ComboBox->addItem(QString::fromStdString(Support::KitchenAreasName(Support::Salad)), QVariant(Support::Salad));
    ComboBox->addItem(QString::fromStdString(Support::KitchenAreasName(Support::Drink)), QVariant(Support::Drink));
    ComboBox->addItem(QString::fromStdString(Support::KitchenAreasName(Support::Desert)), QVariant(Support::Desert));
}


MainWindow::~MainWindow()
{
    delete ui;
}
