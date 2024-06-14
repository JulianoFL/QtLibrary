#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <KitchenControllerLib.h>
#include <QStandardItemModel> 
#include <QString>
#include <QComboBox>

//I:\Programas\Qt\6.7.1\msvc2019_64\bin\windeployqt.exe

namespace Ui {
    class MainWindow; // Forward declaration for the UI class
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ProductsStorage Storage;
    Orders KitchenOrders;


    QStandardItemModel* Tv_ProductsModel;

    QStandardItemModel* Lv_FriesEntriesModel;
    QStandardItemModel* Lv_GrillEntriesModel;
    QStandardItemModel* Lv_SaladEntriesModel;
    QStandardItemModel* Lv_DrinkEntriesModel;
    QStandardItemModel* Lv_DesertEntriesModel;


    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    void PopulateProductsView();

    void PopulateEntriesView();

private slots:
    void Bt_NewOrderClicked();

    void Cb_PopulateNewProductArea(QComboBox* ComboBox);

    void Bt_GetNextDesertEntry();
    void Bt_GetNextDrinksEntry();
    void Bt_GetNextFriesEntry();
    void Bt_GetNextGrillEntry();
    void Bt_GetNextSaladEntry();

    void Bt_AddNewProduct();
};



class KProducts {
public:
    KProducts(const int Id, const QString& Name, const QString& Area) : Id(Id), Name(Name), Area(Area) {}

    int GetId() const { return Id; }
    QString GetName() const { return Name; }
    QString GetArea() const { return Area; }

private:
    int Id;
    QString Name;
    QString Area;
};

class KEntries {
public:
    KEntries(const QString& Name) : Name(Name) {}

    QString GetName() const { return Name; }

private:
    QString Name;
};


#endif // MAINWINDOW_H
