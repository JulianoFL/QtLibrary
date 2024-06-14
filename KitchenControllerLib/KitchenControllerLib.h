#pragma once

#ifdef KITCHENCONTROLLERLIB_EXPORTS
#define KITCHENCONTROLLERLIB __declspec(dllexport)
#else
#define KITCHENCONTROLLERLIB __declspec(dllimport)
#endif

#include <iostream>
#include <chrono>
#include <map>
#include <string>
#include "Enums.h"
#include <list>
#include "CQueue.h"

/// <summary>
/// Base class that's is used by Kitchen classes. Just for architecture. No real functionality
/// </summary>
class BaseKitchen
{
public:
    //This ID property are just for class structure and test. Probably this will come from a database in a real application. This one has no real mea
    int Id = rand();
};


/// <summary>
/// Class that's represents a product in a kitchen area
/// </summary>
class KITCHENCONTROLLERLIB KitchenProduct : public BaseKitchen
{
public:
    std::string Name;
    Support::KitchenAreas Area = Support::KitchenAreas::Desert;

    KitchenProduct(std::string Name, Support::KitchenAreas Area);
    KitchenProduct() = default;
};


/// <summary>
/// Class that's represents an order entry in a kitchen area
/// </summary>
class KITCHENCONTROLLERLIB KitchenEntry : public BaseKitchen {
public:
    int OrderId = 0;

    time_t OrderTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    KitchenProduct Product;



    KitchenEntry(int OrderId, KitchenProduct Product) : OrderId{ OrderId }, Product{ Product }
    {

    }
    KitchenEntry() = default;
};


/// <summary>
/// Class that storages the products of the kitchen
/// </summary>
class KITCHENCONTROLLERLIB ProductsStorage
{    
public:
    std::map<Support::KitchenAreas, std::list<KitchenProduct>> PStorages;

    /// <summary>
    /// Add a new product to the kitchen area
    /// </summary>
    /// <param name="NewProducts">The new product object</param>
    void NewAreaProducts(std::list<KitchenProduct> const NewProducts);

    /// <summary>
    /// Get the products from the kitchen areas
    /// </summary>
    /// <returns>Map with the area and the products from</returns>
    std::map<Support::KitchenAreas, std::list<KitchenProduct>> GetProducts();

    /// <summary>
    /// Return a product by it's Id
    /// </summary>
    /// <param name="Id">Product's Id</param>
    KitchenProduct GetProduct(int Id);


    ProductsStorage();
};

/// <summary>
/// Class thats represents the orders controller of the kitchen
/// </summary>
class KITCHENCONTROLLERLIB Orders
{
private:
    std::map<Support::KitchenAreas, CQueue<KitchenEntry>*> AreasQueue;

public:    
    /// <summary>
    /// Adds new order (multiple entries to one or multiple kitchen area)
    /// </summary>
    /// <param name="Entries">List of entries (products of a area)</param>
    void NewOrder(std::list<KitchenEntry> Entries);

    /// <summary>
    /// Get the first product of a area and remove it from queue
    /// </summary>
    /// <param name="Area">The area that should be read from</param>
    /// <returns>The entry of the area or thrown a simple exception with a error message</returns>
    KitchenEntry GetAndRemoveNextEntry(Support::KitchenAreas Area);

    /// <summary>
    /// Read the current queue of the area. *Do not* modifies the queue
    /// </summary>
    /// <param name="Area">The queue area</param>
    /// <returns>A copy of the queue entries area</returns>
    std::list<KitchenEntry> ReadAreaEntries(Support::KitchenAreas Area);

    Orders();
};


