#include "PizzaComponent.h"
#include "Topping.h"
#include "ToppingGroup.h"
#include "Pizza.h"
#include "BasePizza.h"
#include "ExtraCheese.h"
#include "StuffedCrust.h"
#include "DiscountStrategy.h"
#include "FamilyDiscount.h"
#include "RegularPrice.h"
#include "BulkDiscount.h"
#include "PizzaMenu.h"
#include "SpecialsMenu.h"
#include "Customer.h"
#include "Website.h"
#include "ContextState.h"
#include "StateOrder.h"
#include "StateReview.h"
#include "StateConfirm.h"
#include "StateComplete.h"
#include <iostream>
#include <cassert>
using namespace std;


int getIntInput() {
    int choice;
    while (!(cin >> choice)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(1000, '\n'); // Clear buffer with reasonable limit
    }
    return choice;
}

Pizza* applyExtras(Pizza* basePizza, int extraChoice) {
    switch (extraChoice) {
        case 1: // Extra Cheese only
            return new ExtraCheese(basePizza);
        case 2: // Stuffed Crust only
            return new StuffedCrust(basePizza);
        case 3: // Both extras
            return new StuffedCrust(new ExtraCheese(basePizza));
        case 4: // No extras
        default:
            return basePizza;
    }
}

Pizza* createSelectedPizza(int choice) {
    switch (choice) {
        case 1: // Pepperoni
            return new BasePizza("Pepperoni Pizza", new Topping("Pepperoni", 20.00));
        
        case 2: // Hawaiian
            {
                PizzaComponent* hawaiianToppings = new ToppingGroup("Hawaiian");
                hawaiianToppings->add(new Topping("Ham", 16.00));
                hawaiianToppings->add(new Topping("Pineapple", 14.00));
                return new BasePizza("Hawaiian", hawaiianToppings);
            }
        
        case 3: // Meat Lovers
            {
                PizzaComponent* meatLovers = new ToppingGroup("Meat Lovers");
                meatLovers->add(new Topping("Pepperoni", 20.00));
                meatLovers->add(new Topping("Beef Sausage", 25.00));
                meatLovers->add(new Topping("Salami", 22.00));
                return new BasePizza("Meat Lovers", meatLovers);
            }
        
        case 4: // BBQ Chicken
            {
                PizzaComponent* bbqToppings = new ToppingGroup("BBQ Chicken");
                bbqToppings->add(new Topping("Grilled Chicken", 25.00));
                bbqToppings->add(new Topping("BBQ Sauce", 5.00));
                bbqToppings->add(new Topping("Onions", 8.00));
                return new BasePizza("BBQ Chicken", bbqToppings);
            }
        
        case 5: // BAF
            {
                PizzaComponent* bafToppings = new ToppingGroup("BAF");
                bafToppings->add(new Topping("Bacon", 20.00));
                bafToppings->add(new Topping("Avocado", 19.00));
                bafToppings->add(new Topping("Feta Cheese", 18.00));
                return new BasePizza("Bacon, Avocado, Feta", bafToppings);
            }
        
        case 6: // Vegetarian
            {
                PizzaComponent* vegetarianGroup = new ToppingGroup("Vegetarian");
                vegetarianGroup->add(new Topping("Mushrooms", 12.00));
                vegetarianGroup->add(new Topping("Green Peppers", 10.00));
                vegetarianGroup->add(new Topping("Onions", 8.00));
                return new BasePizza("Vegetarian", vegetarianGroup);
            }
        
        case 7: // Vegetarian Deluxe
            {
                PizzaComponent* vegetarianDeluxe = new ToppingGroup("Vegetarian Deluxe");
                vegetarianDeluxe->add(new Topping("Mushrooms", 12.00));
                vegetarianDeluxe->add(new Topping("Green Peppers", 10.00));
                vegetarianDeluxe->add(new Topping("Onions", 8.00));
                vegetarianDeluxe->add(new Topping("Feta Cheese", 18.00));
                vegetarianDeluxe->add(new Topping("Olives", 15.00));
                return new BasePizza("Vegetarian Deluxe", vegetarianDeluxe);
            }
        
        case 8: // The Greek
            {
                PizzaComponent* greekToppings = new ToppingGroup("The Greek");
                greekToppings->add(new Topping("Feta Cheese", 18.00));
                greekToppings->add(new Topping("Black Olives", 10.00));
                greekToppings->add(new Topping("Onions", 8.00));
                greekToppings->add(new Topping("Tomatoes", 7.00));
                return new BasePizza("The Greek", greekToppings);
            }
        
        case 9: // Build Your Own Pizza
            return nullptr;
        
        default:
            return nullptr;
    }
}

void testObserverPattern() {
    cout << "=================== Testing Observer ==================== " << endl << endl;
    
    // Create menus (subjects)
    PizzaMenu regularMenu;
    SpecialsMenu specialsMenu;
    
    // Create observers
    Customer customer1("Mario");
    Customer customer2("Luigi");
    Customer customer3("Peach");
    Website website("RomeosPizza.com");
    Website website2("PizzaDeals.co.za");
    
    // Test Customer getName functionality
    assert(customer1.getName() == "Mario");
    assert(website.getSiteName() == "RomeosPizza.com");
    
    cout << "Testing observer registration:" << endl;
    
    // Test adding observers to regular menu
    regularMenu.addObserver(&customer1);
    regularMenu.addObserver(&customer2);
    regularMenu.addObserver(&website);
    
    // Test adding observers to specials menu
    specialsMenu.addObserver(&customer1);
    specialsMenu.addObserver(&customer3);
    specialsMenu.addObserver(&website2);
    
    cout << "\n--- Testing Regular Menu Updates ---\n";
    
    // Create pizzas for observer testing
    PizzaComponent* pepperoniTopping = new Topping("Pepperoni", 20.00);
    Pizza* pepperoniPizza = new ExtraCheese(new BasePizza("Pepperoni Special", pepperoniTopping));
    
    PizzaComponent* vegGroup = new ToppingGroup("Vegetarian");
    vegGroup->add(new Topping("Mushroom", 12.00));
    vegGroup->add(new Topping("Green Peppers", 10.00));
    Pizza* vegetarianPizza = new BasePizza("Vegetarian Pizza", vegGroup);
    
    // Test adding pizzas (should notify all registered observers)
    regularMenu.addPizza(pepperoniPizza);
    assert(regularMenu.getPizzas().size() == 1);
    
    regularMenu.addPizza(vegetarianPizza);
    assert(regularMenu.getPizzas().size() == 2);
    
    // Test menu display functionality
    cout << "\nTesting menu display:" << endl;
    regularMenu.displayMenu();
    assert(regularMenu.getTotalMenuValue() > 0);
    
    // Test getPizzaByName functionality
    Pizza* foundPizza = regularMenu.getPizzaByName("Pepperoni");
    assert(foundPizza != nullptr);
    Pizza* notFoundPizza = regularMenu.getPizzaByName("Hawaiian");
    assert(notFoundPizza == nullptr);
    
    // Test removing pizzas (should notify all observers)
    regularMenu.removePizza(pepperoniPizza);
    assert(regularMenu.getPizzas().size() == 1);
    
    cout << "\n--- Testing Specials Menu Updates ---\n";
    
    // Test specials menu (different notification style)
    PizzaComponent* specialGroup = new ToppingGroup("Tuesday Special");
    specialGroup->add(new Topping("Pepperoni", 20.00));
    specialGroup->add(new Topping("Extra Sauce", 5.00));
    Pizza* tuesdaySpecial = new StuffedCrust(new BasePizza("Tuesday Special", specialGroup));
    
    specialsMenu.addPizza(tuesdaySpecial);
    assert(specialsMenu.getPizzas().size() == 1);
    assert(specialsMenu.getMenuType() == "Specials Menu");
    
    cout << "\n--- Testing Observer Removal ---\n";
    
    // Remove an observer and test
    regularMenu.removeObserver(&customer2);
    
    PizzaComponent* hawaiianGroup = new ToppingGroup("Hawaiian");
    hawaiianGroup->add(new Topping("Ham", 18.00));
    hawaiianGroup->add(new Topping("Pineapple", 8.00));
    Pizza* hawaiianPizza = new BasePizza("Hawaiian Pizza", hawaiianGroup);
    
    regularMenu.addPizza(hawaiianPizza);
    // Should only notify customer1 and website now (not customer2)
    
    cout << "\n--- Testing Remove by Name ---\n";
    
    // Test removePizzaByName functionality
    // The pizza name includes the full composite structure plus decorator
    cout << "Actual pizza name: " << tuesdaySpecial->getName() << endl;
    string fullPizzaName = tuesdaySpecial->getName();
    specialsMenu.removePizzaByName(fullPizzaName);
    assert(specialsMenu.getPizzas().size() == 0);
    
    // Test removing non-existent pizza
    regularMenu.removePizzaByName("Non-Existent Pizza");
    
    cout << "\n--- Testing Edge Cases ---\n";
    
    // Test adding null observer
    regularMenu.addObserver(nullptr); // Should handle gracefully
    
    // Test removing non-existent observer
    regularMenu.removeObserver(&customer3); // customer3 was never added to regularMenu
    
    // Test with empty menu
    SpecialsMenu emptyMenu;
    emptyMenu.displayMenu();
    assert(emptyMenu.getTotalMenuValue() == 0.0);
    assert(emptyMenu.getPizzas().size() == 0);
    
    cout << "Observer Pattern tests completed!" << endl << endl;
}

int main() {

    cout << "========== WELCOME TO ROMEO'S PIZZA ========== " << endl << endl;
    cout << "Take a look at our menu:" << endl << endl;

    //Available toppings
    PizzaComponent* pepperoni = new Topping("Pepperoni", 20.00);
    PizzaComponent* mushrooms = new Topping("Mushrooms", 12.00);
    PizzaComponent* greenPeppers = new Topping("Green Peppers", 10.00);
    PizzaComponent* onions = new Topping("Onions", 8.00);
    PizzaComponent* beefSausage = new Topping("Beef Sausage", 25.00);
    PizzaComponent* salami = new Topping("Salami", 22.00);
    PizzaComponent* fetaCheese = new Topping("Feta Cheese", 18.00);
    PizzaComponent* olives = new Topping("Olives", 15.00);
    PizzaComponent* ham = new Topping("Ham", 16.00);
    PizzaComponent* pineapple = new Topping("Pineapple", 14.00);
    PizzaComponent* grilledChicken = new Topping("Grilled Chicken", 25.00);
    PizzaComponent* bacon = new Topping("Bacon", 20.00);
    PizzaComponent* avocado = new Topping("Avocado", 19.00);
    PizzaComponent* blackOlives = new Topping("Black Olives", 10.00);
    PizzaComponent* tomatoes = new Topping("Tomatoes", 7.00);

    Pizza* pepperoniPizza = new BasePizza("Pepperoni Pizza", pepperoni);
    cout << "1. ";
    pepperoniPizza->printPizza(); 

    PizzaComponent* hawaiianToppings = new ToppingGroup("Hawaiian");
    hawaiianToppings->add(ham);
    hawaiianToppings->add(pineapple);
    Pizza* hawaiianPizza = new BasePizza("Hawaiian", hawaiianToppings);
    cout << "2. ";
    hawaiianPizza->printPizza();

    PizzaComponent* meatLovers = new ToppingGroup("Meat Lovers");
    meatLovers->add(pepperoni);
    meatLovers->add(beefSausage);
    meatLovers->add(salami);
    Pizza* meatLoversPizza = new BasePizza("Meat Lovers", meatLovers);
    cout << "3. ";
    meatLoversPizza->printPizza();

    PizzaComponent* bbqToppings = new ToppingGroup("BBQ Chicken");
    bbqToppings->add(grilledChicken);
    bbqToppings->add(new Topping("BBQ Sauce", 5.00));
    bbqToppings->add(onions);
    Pizza* bbqChickenPizza = new BasePizza("BBQ Chicken", bbqToppings);
    cout << "4. ";
    bbqChickenPizza->printPizza();

    PizzaComponent* bafToppings = new ToppingGroup("BAF");
    bafToppings->add(bacon);
    bafToppings->add(avocado);
    bafToppings->add(fetaCheese);
    Pizza* bafPizza = new BasePizza("Bacon, Avocado, Feta", bafToppings);
    cout << "5. ";
    bafPizza->printPizza();
    
    cout << endl;
    
    cout << "========== VEGETARIAN OPTIONS ==========" << endl;

    PizzaComponent* vegetarianGroup = new ToppingGroup("Vegetarian");
    vegetarianGroup->add(mushrooms);
    vegetarianGroup->add(greenPeppers);
    vegetarianGroup->add(onions);
    Pizza* vegetarianPizza = new BasePizza("Vegetarian", vegetarianGroup);
    cout << "6. ";
    vegetarianPizza->printPizza();

    PizzaComponent* vegetarianDeluxe = new ToppingGroup("Vegetarian Deluxe");
    vegetarianDeluxe->add(vegetarianGroup);
    vegetarianDeluxe->add(fetaCheese);
    vegetarianDeluxe->add(olives);
    Pizza* vegetarianDeluxePizza = new BasePizza("Vegetarian Deluxe", vegetarianDeluxe);
    cout << "7. ";
    vegetarianDeluxePizza->printPizza();
    
    PizzaComponent* greekToppings = new ToppingGroup("The Greek");
    greekToppings->add(fetaCheese);
    greekToppings->add(blackOlives);
    greekToppings->add(onions);
    greekToppings->add(tomatoes);
    Pizza* greekPizza = new BasePizza("The Greek", greekToppings);
    cout << "8. ";
    greekPizza->printPizza();

    cout << endl;

    cout << "9. Build Your Own Pizza - Starting with basics (Dough, Tomato Sauce, Cheese) R30.00 + toppings" << endl;

    cout << endl;

    cout << "========== ADD EXTRAS ==========" << endl;
    cout << "1. Extra Cheese +R12.00" << endl;
    cout << "2. Stuffed Crust +R20.00" << endl;
    cout << "3. Both Extra Cheese & Stuffed Crust +R32.00" << endl;
    cout << "4. No extras" << endl << endl;


    // Initialize order context (State Pattern)
    ContextState order;
    order.setOrderNumber(1001);
   
    cout << "========== START YOUR ORDER ==========" << endl;
    cout << "Select pizzas by entering the number (1-9), or 0 to finish ordering:" << endl << endl;

    // ordering loop
    bool ordering = true;
    while(ordering && order.getCurrentState()->getStateName() == "Order") {
        cout << "Enter your choice (1-9, or 0 to finish): ";
        int choice = getIntInput();

        if (choice == 0) {
            // no pizzas ordered yet
            if (order.getPizzas().size() == 0) {
                cout << "You have not ordered any pizzas. Please select at least one." << endl;
                continue;
            }

            // 0 entered and there are pizzas in order
            ordering = false;
            break;
        }

        if (choice < 1 || choice > 9) {
            cout << "Invalid number input. Please select a number between 1 and 9." << endl;
            continue;
        }

        Pizza* pizzaChoice = nullptr;

        // 9 - custom pizza chosen therefore build your own pizza
        if (choice == 9) {
            cout << "========== BUILD YOUR OWN PIZZA ==========" << endl;
            cout << "Starting with basics: Dough, Tomato Sauce, Cheese (R30.00)" << endl;
            cout << "Available toppings:" << endl;
            cout << "1. " << pepperoni->getName() << "-R" << pepperoni->getPrice() << endl;
            cout << "2. " << mushrooms->getName() << "-R" << mushrooms->getPrice() << endl;
            cout << "3. " << greenPeppers->getName() << "-R" << greenPeppers->getPrice() << endl;
            cout << "4. " << onions->getName() << "-R" << onions->getPrice() << endl;
            cout << "5. " << beefSausage->getName() << "-R" << beefSausage->getPrice() << endl;
            cout << "6. " << salami->getName() << "-R" << salami->getPrice() << endl;
            cout << "7. " << fetaCheese->getName() << "-R" << fetaCheese->getPrice() << endl;
            cout << "8. " << olives->getName() << "-R" << olives->getPrice() << endl;
            cout << "9. " << ham->getName() << "-R" << ham->getPrice() << endl;
            cout << "10. " << pineapple->getName() << "-R" << pineapple->getPrice() << endl;
            cout << "11. " << grilledChicken->getName() << "-R" << grilledChicken->getPrice() << endl;
            cout << "12. " << bacon->getName() << "-R" << bacon->getPrice() << endl;
            cout << "13. " << avocado->getName() << "-R" << avocado->getPrice() << endl;
            cout << "14. " << blackOlives->getName() << "-R" << blackOlives->getPrice() << endl;
            cout << "15. " << tomatoes->getName() << "-R" << tomatoes->getPrice() << endl;

            PizzaComponent* customToppings = new ToppingGroup("Custom Pizza");

            bool buildingPizza = true;
            while(buildingPizza) {
                cout << "Enter your choice (1-15, or 0 to finish): ";
                int toppingsChoice = getIntInput();

                if (toppingsChoice == 0) {
                    buildingPizza = false;
                    break;
                }


                if (toppingsChoice < 1 || toppingsChoice > 15) {
                    cout << "Invalid number input. Please select a number between 1 and 15." << endl;
                    continue;
                }

                switch (toppingsChoice) {
                    case 1:
                        customToppings->add(pepperoni);
                        cout << "Pepperoni added!" << endl;
                        break;
                    case 2:
                        customToppings->add(mushrooms);
                        cout << "Mushrooms added!" << endl;
                        break;
                    case 3:
                        customToppings->add(greenPeppers);
                        cout << "Green Peppers added!" << endl;
                        break;
                    case 4:
                        customToppings->add(onions);
                        cout << "Onions added!" << endl;
                        break;
                    case 5:
                        customToppings->add(beefSausage);
                        cout << "Beef Sausage added!" << endl;
                        break;
                    case 6:
                        customToppings->add(salami);
                        cout << "Salami added!" << endl;
                        break;
                    case 7:
                        customToppings->add(fetaCheese);
                        cout << "Feta Cheese added!" << endl;
                        break;
                    case 8:
                        customToppings->add(olives);
                        cout << "Olives added!" << endl;
                        break;
                    case 9:
                        customToppings->add(ham);
                        cout << "Ham added!" << endl;
                        break;
                    case 10:
                        customToppings->add(pineapple);
                        cout << "Pineapple added!" << endl;
                        break;
                    case 11:
                        customToppings->add(grilledChicken);
                        cout << "Grilled Chicken added!" << endl;
                        break;
                    case 12:
                        customToppings->add(bacon);
                        cout << "Bacon added!" << endl;
                        break;
                    case 13:
                        customToppings->add(avocado);
                        cout << "Avocado added!" << endl;
                        break;
                    case 14:
                        customToppings->add(blackOlives);
                        cout << "Black Olives added!" << endl;
                        break;
                    case 15:
                        customToppings->add(tomatoes);
                        cout << "Tomatoes added!" << endl;
                        break;
                }

                cout << "Current pizza price: R" << (30.00 + customToppings->getPrice()) << endl << endl;

            } //end of while building pizza loop

            pizzaChoice = new BasePizza("Custom Pizza", customToppings);

        } //end of 9 selected
        else {
            pizzaChoice = createSelectedPizza(choice); //selected pre-made pizza
        }

        if (pizzaChoice) {
            cout << "You selected: ";
            pizzaChoice->printPizza();
            
            // adding extras (Decorator Pattern)
            cout << "Would you like to add any extras? Enter choice (1-4): ";
            int extraChoice = getIntInput();
            
            // applying extras
            pizzaChoice = applyExtras(pizzaChoice, extraChoice);
            
            // Add to order (State Pattern)
            order.addPizza(pizzaChoice);
            
            cout << endl << "Added to your order:" << endl;
            pizzaChoice->printPizza();
            cout << "Current order total: R" << order.getTotalPrice() << endl;
            cout << "Items in order: " << order.getPizzas().size() << endl << endl;
        }
    }

    cout << endl;

    // Order review and completion
    if (order.getPizzas().size() > 0) {
        
        bool reviewComplete = false;
        while (!reviewComplete) {
            cout << "========== ORDER REVIEW ==========" << endl;
            order.proceedToReview();
            
            cout << "Your order contains " << order.getPizzas().size() << " pizza(s):" << endl;
            for (size_t i = 0; i < order.getPizzas().size(); i++) {
                cout << (i + 1) << ". ";
                order.getPizzas()[i]->printPizza();
            }
            
            cout << endl << "Total Price: R" << order.getTotalPrice() << endl << endl;
            
            // Allow you to go back to ordering state
            cout << "Options:" << endl;
            cout << "1. Continue to checkout" << endl;
            cout << "2. Add more pizzas" << endl;

            cout << endl;
            
            bool validReviewChoice = false;
            while (!validReviewChoice) {
                cout << "Enter your choice (1-2): ";
                int reviewChoice = getIntInput();
                
                if (reviewChoice < 1 || reviewChoice > 2) {
                    cout << "Invalid choice. Please select 1 or 2." << endl;
                    continue;
                }
                
                if (reviewChoice == 2) {
                    // Go back to ordering 
                    order.backToEditing();
                    cout << "Returning to pizza selection..." << endl << endl;

                    cout << "1. ";
                    pepperoniPizza->printPizza(); 
                    cout << "2. ";
                    hawaiianPizza->printPizza();
                    cout << "3. ";
                    meatLoversPizza->printPizza();
                    cout << "4. ";
                    bbqChickenPizza->printPizza();
                    cout << "5. ";
                    bafPizza->printPizza();
                    cout << "6. ";
                    vegetarianPizza->printPizza();
                    cout << "7. ";
                    vegetarianDeluxePizza->printPizza();
                    cout << "8. ";
                    greekPizza->printPizza();
                    cout << "9. Build Your Own Pizza - Starting with basics (Dough, Tomato Sauce, Cheese) R30.00 + toppings" << endl << endl;
                                        
                    // Resume ordering loop
                    bool continuingOrder = true;
                    while (continuingOrder && order.getCurrentState()->getStateName() == "Order") {
                        cout << "Enter your choice (1-9, or 0 to return to review): ";
                        int choice = getIntInput();

                        if (choice == 0) {
                            continuingOrder = false;
                            break;
                        }

                        if (choice < 1 || choice > 9) {
                            cout << "Invalid number input. Please select a number between 1 and 9." << endl;
                            continue;
                        }

                        Pizza* pizzaChoice = nullptr;

                        if (choice == 9) {
                            // Build Your Own Pizza
                            cout << "========== BUILD YOUR OWN PIZZA ==========" << endl;
                            cout << "Starting with basics: Dough, Tomato Sauce, Cheese (R30.00)" << endl;
                            cout << "Available toppings:" << endl;
                            cout << "1. " << pepperoni->getName() << "-R" << pepperoni->getPrice() << endl;
                            cout << "2. " << mushrooms->getName() << "-R" << mushrooms->getPrice() << endl;
                            cout << "3. " << greenPeppers->getName() << "-R" << greenPeppers->getPrice() << endl;
                            cout << "4. " << onions->getName() << "-R" << onions->getPrice() << endl;
                            cout << "5. " << beefSausage->getName() << "-R" << beefSausage->getPrice() << endl;
                            cout << "6. " << salami->getName() << "-R" << salami->getPrice() << endl;
                            cout << "7. " << fetaCheese->getName() << "-R" << fetaCheese->getPrice() << endl;
                            cout << "8. " << olives->getName() << "-R" << olives->getPrice() << endl;
                            cout << "9. " << ham->getName() << "-R" << ham->getPrice() << endl;
                            cout << "10. " << pineapple->getName() << "-R" << pineapple->getPrice() << endl;
                            cout << "11. " << grilledChicken->getName() << "-R" << grilledChicken->getPrice() << endl;
                            cout << "12. " << bacon->getName() << "-R" << bacon->getPrice() << endl;
                            cout << "13. " << avocado->getName() << "-R" << avocado->getPrice() << endl;
                            cout << "14. " << blackOlives->getName() << "-R" << blackOlives->getPrice() << endl;
                            cout << "15. " << tomatoes->getName() << "-R" << tomatoes->getPrice() << endl;

                            PizzaComponent* customToppings = new ToppingGroup("Custom Pizza");

                            bool buildingPizza = true;
                            while(buildingPizza) {
                                cout << "Enter your choice (1-15, or 0 to finish): ";
                                int toppingsChoice = getIntInput();

                                if (toppingsChoice == 0) {
                                    buildingPizza = false;
                                    break;
                                }

                                if (toppingsChoice < 1 || toppingsChoice > 15) {
                                    cout << "Invalid number input. Please select a number between 1 and 15." << endl;
                                    continue;
                                }

                                switch (toppingsChoice) {
                                    case 1:
                                        customToppings->add(new Topping("Pepperoni", 20.00));
                                        cout << "Pepperoni added!" << endl;
                                        break;
                                    case 2:
                                        customToppings->add(new Topping("Mushrooms", 12.00));
                                        cout << "Mushrooms added!" << endl;
                                        break;
                                    case 3:
                                        customToppings->add(new Topping("Green Peppers", 10.00));
                                        cout << "Green Peppers added!" << endl;
                                        break;
                                    case 4:
                                        customToppings->add(new Topping("Onions", 8.00));
                                        cout << "Onions added!" << endl;
                                        break;
                                    case 5:
                                        customToppings->add(new Topping("Beef Sausage", 25.00));
                                        cout << "Beef Sausage added!" << endl;
                                        break;
                                    case 6:
                                        customToppings->add(new Topping("Salami", 22.00));
                                        cout << "Salami added!" << endl;
                                        break;
                                    case 7:
                                        customToppings->add(new Topping("Feta Cheese", 18.00));
                                        cout << "Feta Cheese added!" << endl;
                                        break;
                                    case 8:
                                        customToppings->add(new Topping("Olives", 15.00));
                                        cout << "Olives added!" << endl;
                                        break;
                                    case 9:
                                        customToppings->add(new Topping("Ham", 16.00));
                                        cout << "Ham added!" << endl;
                                        break;
                                    case 10:
                                        customToppings->add(new Topping("Pineapple", 14.00));
                                        cout << "Pineapple added!" << endl;
                                        break;
                                    case 11:
                                        customToppings->add(new Topping("Grilled Chicken", 25.00));
                                        cout << "Grilled Chicken added!" << endl;
                                        break;
                                    case 12:
                                        customToppings->add(new Topping("Bacon", 20.00));
                                        cout << "Bacon added!" << endl;
                                        break;
                                    case 13:
                                        customToppings->add(new Topping("Avocado", 19.00));
                                        cout << "Avocado added!" << endl;
                                        break;
                                    case 14:
                                        customToppings->add(new Topping("Black Olives", 10.00));
                                        cout << "Black Olives added!" << endl;
                                        break;
                                    case 15:
                                        customToppings->add(new Topping("Tomatoes", 7.00));
                                        cout << "Tomatoes added!" << endl;
                                        break;
                                }

                                cout << "Current pizza price: R" << (30.00 + customToppings->getPrice()) << endl << endl;
                            }

                            pizzaChoice = new BasePizza("Custom Pizza", customToppings);
                        } else {
                            pizzaChoice = createSelectedPizza(choice);
                        }

                        if (pizzaChoice) {
                            cout << "You selected: ";
                            pizzaChoice->printPizza();
                            
                            cout << "Would you like to add any extras? Enter choice (1-4): ";
                            int extraChoice = getIntInput();
                            
                            pizzaChoice = applyExtras(pizzaChoice, extraChoice);
                            
                            order.addPizza(pizzaChoice);
                            
                            cout << endl << "Added to your order:" << endl;
                            pizzaChoice->printPizza();
                            cout << "Current order total: R" << order.getTotalPrice() << endl;
                            cout << "Items in order: " << order.getPizzas().size() << endl << endl;
                        }
                    }
                    
                    validReviewChoice = true; // Exit inner loop to go back to review
                } else {
                    // Continue to checkout
                    reviewComplete = true;
                    validReviewChoice = true;
                }
            }
        }
        
        cout << "Choose the appropriate discount: " << endl;
        cout << "1. Regular Price: 0%' discount" << endl;
        cout << "2. Bulk orders (5+ pizzas): 10%' discount" << endl;
        cout << "3. Family Discount: 15%' discount" << endl;

        bool validChoice = false;
        while (!validChoice) {
            cout << "Enter your discount choice (1-3): ";
            int discountChoice = getIntInput();
    
            if (discountChoice < 1 || discountChoice > 3) {
                cout << "Invalid number input. Please select a valid number (1-3)" << endl;
                continue;
            }
    
            if (discountChoice == 2 && order.getPizzas().size() >= 5) {
                order.setStrategy(new BulkDiscount());
                cout << "Bulk Discount applied!" << endl;
                validChoice = true;
            }
            else if (discountChoice == 2 && order.getPizzas().size() < 5) {
                order.setStrategy(new RegularPrice());
                cout << "Bulk discount requires 5+ pizzas. Regular pricing applied." << endl;
                validChoice = true;
            }
            else if (discountChoice == 3) {
                order.setStrategy(new FamilyDiscount());
                cout << "Family Discount applied!" << endl;
                validChoice = true;
            }
            else {
                order.setStrategy(new RegularPrice());
                cout << "Regular pricing applied!" << endl;
                validChoice = true;
            }
        }

        cout << endl;

        // Display current order
        order.internalDisplayOrder();

        cout << "Confirm your order? (y/n): ";
        char confirm;
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            order.confirmOrder();
            cout << endl << "Order confirmed! Preparing your pizzas..." << endl;
            order.completeOrder();
            cout << "Thank you for choosing Romeo's Pizza!" << endl;
        } else {
            cout << "Order cancelled. Thank you for visiting!" << endl;
        }
    } else {
        cout << "No pizzas ordered. Thank you for visiting Romeo's Pizza!" << endl;
    }

    cout << endl;

    testObserverPattern();

    // clean up memory
    delete pepperoniPizza;
    delete hawaiianPizza;
    delete meatLoversPizza;
    delete bbqChickenPizza;
    delete vegetarianPizza;
    delete vegetarianDeluxePizza;
    delete greekPizza;

    // delete individual toppings
    delete pepperoni;
    delete mushrooms;
    delete greenPeppers;
    delete onions;
    delete beefSausage;
    delete salami;
    delete fetaCheese;
    delete olives;
    delete ham;
    delete pineapple;
    delete grilledChicken;
    delete bacon;
    delete avocado;
    delete blackOlives;
    delete tomatoes;

    return 0;
}