#include "PizzaComponent.h"
#include "Topping.h"
#include "ToppingGroup.h"
#include "Pizza.h"
#include "BasePizza.h"
#include "ExtraCheese.h"
#include "StuffedCrust.h"
#include <iostream>
using namespace std;

int main() {

    // ============================== Testing Composite ===========================

    cout << "=================== Testing Composite ==================== " << endl << endl;

    //Pepperoni Pizza
    PizzaComponent* pepperoni = new Topping("Pepperoni", 20.00);
    cout << "Pepperoni pizza: " << pepperoni->getName() << " - " << "Price: R" << pepperoni->getPrice() << endl;

    //Vegetarian Pizza
    PizzaComponent* mushrooms = new Topping("Mushroom", 12.00);
    PizzaComponent* greenPeppers = new Topping("Green Peppers", 10.00);
    PizzaComponent* onions = new Topping("Onions", 8.00);
    //Creating toppings group for vegetarian 
    PizzaComponent* vegetarian = new ToppingGroup("Vegetarian");
    vegetarian->add(mushrooms);
    vegetarian->add(greenPeppers);
    vegetarian->add(onions);
    cout << "Vegetarian pizza: " << vegetarian->getName() << " - " << "Price: R" << vegetarian->getPrice() << endl;
    

    //Meat Lovers Pizza
    PizzaComponent* beefSausage = new Topping("Beef Sausage", 25.00);
    PizzaComponent* salami = new Topping("Salami", 22.00);
    PizzaComponent* meatLovers = new ToppingGroup("Meat Lovers");
    meatLovers->add(pepperoni);
    meatLovers->add(beefSausage);
    meatLovers->add(salami);
    cout << "Meat Lovers pizza: " << meatLovers->getName() << " - " << "Price: R" << meatLovers->getPrice() << endl;


    //Vegetarian deluxe
    PizzaComponent* feta = new Topping("Feta Cheese", 18.00);
    PizzaComponent* olives = new Topping("Olives", 15.00);
    PizzaComponent* vegetarianDeluxe = new ToppingGroup("Vegetarian Deluxe");
    vegetarianDeluxe->add(vegetarian);
    vegetarianDeluxe->add(feta);
    vegetarianDeluxe->add(olives);
    cout << "Vegetarian Deluxe: " << vegetarianDeluxe->getName() << " - " << "Price: R" << vegetarianDeluxe->getPrice() << endl << endl;

    // ============================================================================


    // ============================== Testing Decorator ===========================

    cout << "=================== Testing Decorator ==================== " << endl << endl;

    //Pepperoni with extra cheese
    Pizza* pepperoni2 = new BasePizza("Pepperoni Pizza", pepperoni);
    pepperoni2->printPizza(); 
    cout << endl;
    Pizza* extraCheesePepperoni = new ExtraCheese(pepperoni2);
    extraCheesePepperoni->printPizza();

    cout << endl;

    Pizza* veg = new BasePizza("Vegetarian", vegetarian);
    veg->printPizza();
    cout << endl;
    Pizza* vegExtraCheese = new ExtraCheese(veg);
    Pizza* vegStuffedCrust = new StuffedCrust(vegExtraCheese);
    vegStuffedCrust->printPizza();
    cout << endl;


    // ============================================================================


    // ============================== Testing Strategy ===========================



    return 0;
}

