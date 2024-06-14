#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>


class Support {
public:
	/// <summary>
	/// Enum that's represents each area of the Kitchen
	/// </summary>
	enum KitchenAreas { Fries = 0, Grill, Salad, Drink, Desert };

	static std::string KitchenAreasName(KitchenAreas Area)
	{
		switch (Area)
		{
		case Fries:
			return "Fries";
		case Grill:
			return "Grill";
		case Salad:
			return "Salad";
		case Drink:
			return "Drink";
		case Desert:
			return "Desert";
		}
	}
};
