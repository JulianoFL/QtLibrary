#include <iostream>
#include <chrono>
#include <map>
#include <string>
#include "KitchenControllerLib.h"
#include <list>
#include <boost/algorithm/string.hpp>


//KitchenProduct Class ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
KitchenProduct::KitchenProduct(std::string Name, Support::KitchenAreas Area) : Name{ Name }, Area{ Area } {}


//ProductsStorage Class ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ProductsStorage::ProductsStorage()
{
    PStorages[Support::KitchenAreas::Desert] = std::list<KitchenProduct>();
    PStorages[Support::KitchenAreas::Drink] = std::list<KitchenProduct>();
    PStorages[Support::KitchenAreas::Fries] = std::list<KitchenProduct>();
    PStorages[Support::KitchenAreas::Grill] = std::list<KitchenProduct>();
    PStorages[Support::KitchenAreas::Salad] = std::list<KitchenProduct>();


    PStorages[Support::KitchenAreas::Desert].push_front(KitchenProduct("Sunday", Support::KitchenAreas::Desert));
    PStorages[Support::KitchenAreas::Desert].push_front(KitchenProduct("IceCream", Support::KitchenAreas::Desert));

    PStorages[Support::KitchenAreas::Drink].push_front(KitchenProduct("Coke", Support::KitchenAreas::Drink));
    PStorages[Support::KitchenAreas::Drink].push_front(KitchenProduct("Fanta", Support::KitchenAreas::Drink));

    PStorages[Support::KitchenAreas::Fries].push_front(KitchenProduct("Oil", Support::KitchenAreas::Fries));
    PStorages[Support::KitchenAreas::Fries].push_front(KitchenProduct("Salt", Support::KitchenAreas::Fries));

    PStorages[Support::KitchenAreas::Grill].push_front(KitchenProduct("Oil", Support::KitchenAreas::Grill));
    PStorages[Support::KitchenAreas::Grill].push_front(KitchenProduct("Frier", Support::KitchenAreas::Grill));

    PStorages[Support::KitchenAreas::Salad].push_front(KitchenProduct("Tomato", Support::KitchenAreas::Salad));
    PStorages[Support::KitchenAreas::Salad].push_front(KitchenProduct("Letuce", Support::KitchenAreas::Salad));
};


void ProductsStorage::NewAreaProducts(std::list<KitchenProduct> const NewProducts)
{
    for (auto NewProduct : NewProducts)
    {
        for (auto OldProduct : PStorages[NewProduct.Area])
        {
            if (boost::algorithm::to_lower_copy(NewProduct.Name) == boost::algorithm::to_lower_copy(OldProduct.Name))
            {
                throw std::exception(("Already exists a product with that name in that area : " + NewProduct.Name).c_str());
            }
        }

        PStorages[NewProduct.Area].push_back(NewProduct);
    }
};

std::map<Support::KitchenAreas, std::list<KitchenProduct>> ProductsStorage::GetProducts()
{
    return PStorages;
};

KitchenProduct ProductsStorage::GetProduct(int Id)
{
    for (auto const& Pair : PStorages)
    {
        for (auto Product : Pair.second)
        {
            if (Product.Id == Id) {

                KitchenProduct* P = &Product;

                return *P;
            }
        }
    }

    //return nullptr;
};


//Orders Class ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Orders::Orders()
{
    //Creates the empty area pair for each type to start
    for (auto Areas : { Support::KitchenAreas::Fries, Support::KitchenAreas::Grill, Support::KitchenAreas::Salad, Support::KitchenAreas::Drink, Support::KitchenAreas::Desert })
    {
        AreasQueue.insert(std::make_pair(Areas, new CQueue<KitchenEntry>()));
    }
};


void Orders::NewOrder(std::list<KitchenEntry> Entries)
{
    for (auto const Item : Entries)
    {
        try
        {
            AreasQueue[Item.Product.Area]->Push(Item);
        }
        catch (const std::exception& E)
        {
            throw "";
        }        
    }
}

KitchenEntry Orders::GetAndRemoveNextEntry(Support::KitchenAreas Area)
{
    KitchenEntry NextEntry;

    if (AreasQueue[Area]->TryPop(NextEntry))
        return NextEntry;
    else
        throw std::exception("No new entries");
}

std::list<KitchenEntry> Orders::ReadAreaEntries(Support::KitchenAreas Area)
{
    return AreasQueue[Area]->ReturnQueueCopy();
}