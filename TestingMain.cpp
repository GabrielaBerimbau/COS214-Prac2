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

void testCompositePattern() {
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

    cout << "Removing last topping added: ";
    vegetarianDeluxe->removeLast();
    cout << "Vegetarian Deluxe: " << vegetarianDeluxe->getName() << " - " << "Price: R" << vegetarianDeluxe->getPrice() << endl << endl;

    cout << "Composite Pattern tests completed!" << endl << endl;
}


void testDecoratorPattern() {
    cout << "=================== Testing Decorator ==================== " << endl << endl;

    // Create base toppings for decorator testing
    PizzaComponent* pepperoniTopping = new Topping("Pepperoni", 20.00);
    PizzaComponent* vegetarianGroup = new ToppingGroup("Vegetarian");
    vegetarianGroup->add(new Topping("Mushroom", 12.00));
    vegetarianGroup->add(new Topping("Green Peppers", 10.00));
    vegetarianGroup->add(new Topping("Onions", 8.00));

    //Pepperoni with extra cheese
    Pizza* pepperoni2 = new BasePizza("Pepperoni Pizza", pepperoniTopping);
    pepperoni2->printPizza(); 
    cout << endl;
    Pizza* extraCheesePepperoni = new ExtraCheese(pepperoni2);
    extraCheesePepperoni->printPizza();

    cout << endl;

    Pizza* veg = new BasePizza("Vegetarian", vegetarianGroup);
    veg->printPizza();
    cout << endl;
    Pizza* vegExtraCheese = new ExtraCheese(veg);
    Pizza* vegStuffedCrust = new StuffedCrust(vegExtraCheese);
    vegStuffedCrust->printPizza();
    cout << endl;

    cout << "Decorator Pattern tests completed!" << endl << endl;
}


void testStrategyPattern() {
    cout << "=================== Testing Strategy ==================== " << endl << endl;
    //Pepperoni Pizza
    PizzaComponent* pepperoni = new Topping("Pepperoni", 20.00);
    Pizza* pepperoniPizza = new BasePizza("Pepperoni", pepperoni);
    cout << "Pepperoni pizza: Price: R" << pepperoniPizza->getPrice() << endl;

    //Vegetarian Pizza
    PizzaComponent* mushrooms = new Topping("Mushroom", 12.00);
    PizzaComponent* greenPeppers = new Topping("Green Peppers", 10.00);
    PizzaComponent* onions = new Topping("Onions", 8.00);
    //Creating toppings group for vegetarian 
    PizzaComponent* vegetarian = new ToppingGroup("Vegetarian");
    vegetarian->add(mushrooms);
    vegetarian->add(greenPeppers);
    vegetarian->add(onions);
    Pizza* vegetarianPizza = new BasePizza("Vegetarian", vegetarian);
    cout << "Vegetarian pizza: Price: R" << vegetarianPizza->getPrice() << endl;
    

    //Meat Lovers Pizza
    PizzaComponent* beefSausage = new Topping("Beef Sausage", 25.00);
    PizzaComponent* salami = new Topping("Salami", 22.00);
    PizzaComponent* meatLovers = new ToppingGroup("Meat Lovers");
    meatLovers->add(pepperoni);
    meatLovers->add(beefSausage);
    meatLovers->add(salami);
    Pizza* meatLoversPizza = new BasePizza("MeatLovers", meatLovers);
    cout << "Meat Lovers pizza: Price: R" << meatLoversPizza->getPrice() << endl;

    //Vegetarian deluxe
    PizzaComponent* feta = new Topping("Feta Cheese", 18.00);
    PizzaComponent* olives = new Topping("Olives", 15.00);
    PizzaComponent* vegetarianDeluxe = new ToppingGroup("Vegetarian Deluxe");
    vegetarianDeluxe->add(vegetarian);
    vegetarianDeluxe->add(feta);
    vegetarianDeluxe->add(olives);
    Pizza* vegetarianDeluxePizza = new BasePizza("Vegetarian Deluxe", vegetarianDeluxe);
    cout << "Vegetarian Deluxe: Price: R" << vegetarianDeluxePizza->getPrice() << endl << endl;

    DiscountStrategy* famDiscount = new FamilyDiscount();
    cout << "Price of Vegetarian Deluxe after family discount: R" << famDiscount->applyDiscount(vegetarianDeluxePizza->getPrice(), 1) << endl;

    DiscountStrategy* regDiscount = new RegularPrice();
    cout << "Price of Vegetarian Deluxe after regular discount: R" << regDiscount->applyDiscount(vegetarianDeluxePizza->getPrice(), 1) << endl;

    //order with multiple pizzas
    DiscountStrategy* bulkDiscount = new BulkDiscount();
    double totalPrice = pepperoniPizza->getPrice() + meatLoversPizza->getPrice() + vegetarianPizza->getPrice() + vegetarianDeluxePizza->getPrice();
    cout << "Total price: R" << totalPrice << endl;
    cout << "Price of 4 pizzas after bulk discount: R" << bulkDiscount->applyDiscount(totalPrice, 4) << endl;
    totalPrice += meatLoversPizza->getPrice();
    cout << "Total price: R" << totalPrice << endl;
    cout << "Price of 4 pizzas after bulk discount: R" << bulkDiscount->applyDiscount(totalPrice, 5) << endl;
}


void testObserverPattern() {
    cout << "=================== Testing Observer ==================== " << endl << endl;
    
    // Create menus (subjects)
    PizzaMenu regularMenu;
    SpecialsMenu specialsMenu;
    
    // Create observers
    Customer customer1("Mario");
    Customer customer2("Luigi");
    Website website("RomeosPizza.com");
    
    // Test adding observers
    regularMenu.addObserver(&customer1);
    regularMenu.addObserver(&customer2);
    regularMenu.addObserver(&website);
    
    specialsMenu.addObserver(&customer1);
    specialsMenu.addObserver(&website);
    
    cout << "\n--- Testing Regular Menu Updates ---\n";
    
    // Create pizzas for observer testing
    PizzaComponent* pepperoniTopping = new Topping("Pepperoni", 20.00);
    Pizza* pepperoniPizza = new ExtraCheese(new BasePizza("Pepperoni Special", pepperoniTopping));
    
    PizzaComponent* vegGroup = new ToppingGroup("Vegetarian");
    vegGroup->add(new Topping("Mushroom", 12.00));
    vegGroup->add(new Topping("Green Peppers", 10.00));
    Pizza* vegetarianPizza = new BasePizza("Vegetarian Pizza", vegGroup);
    
    // Test adding pizzas (should notify all observers)
    regularMenu.addPizza(pepperoniPizza);
    assert(regularMenu.getPizzas().size() == 1);
    
    regularMenu.addPizza(vegetarianPizza);
    assert(regularMenu.getPizzas().size() == 2);
    
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
    
    cout << "\n--- Testing Observer Removal ---\n";
    
    // Remove an observer and test
    regularMenu.removeObserver(&customer2);
    
    PizzaComponent* hawaiianGroup = new ToppingGroup("Hawaiian");
    hawaiianGroup->add(new Topping("Ham", 18.00));
    hawaiianGroup->add(new Topping("Pineapple", 8.00));
    Pizza* hawaiianPizza = new BasePizza("Hawaiian Pizza", hawaiianGroup);
    
    regularMenu.addPizza(hawaiianPizza);
    // Should only notify customer1 and website now
    
    cout << "Observer Pattern tests completed!" << endl << endl;
}

void testStatePattern() {
    cout << "=================== Testing State Pattern ==================== " << endl << endl;
    
    ContextState order;
    order.setOrderNumber(1001);
    
    // Create pizza objects for state testing
    PizzaComponent* pepperoniTopping = new Topping("Pepperoni", 20.00);
    Pizza* pepperoniPizza = new BasePizza("Pepperoni Pizza", pepperoniTopping);
    
    PizzaComponent* vegGroup = new ToppingGroup("Vegetarian");
    vegGroup->add(new Topping("Mushroom", 12.00));
    vegGroup->add(new Topping("Onions", 8.00));
    Pizza* vegetarianPizza = new ExtraCheese(new BasePizza("Vegetarian Pizza", vegGroup));
    
    cout << "\n=== Testing StateOrder ===\n";
    assert(order.getCurrentState()->getStateName() == "Order");
    
    // Test valid operations in StateOrder
    order.addPizza(pepperoniPizza);
    order.addPizza(vegetarianPizza);
    assert(order.getPizzas().size() == 2);
    
    order.removePizza(pepperoniPizza);
    assert(order.getPizzas().size() == 1);
    
    // Test invalid operations in StateOrder
    order.confirmOrder(); // Should fail
    order.completeOrder(); // Should fail
    order.backToEditing(); // Should fail (already in Order)
    
    cout << "\n=== Testing StateReview ===\n";
    
    // Move to Review state
    order.proceedToReview();
    assert(order.getCurrentState()->getStateName() == "Review");
    
    // Test invalid operations in StateReview
    PizzaComponent* extraTopping = new Topping("Extra Pepperoni", 20.00);
    Pizza* extraPizza = new BasePizza("Extra Pizza", extraTopping);
    order.addPizza(extraPizza); // Should fail
    order.removePizza(vegetarianPizza); // Should fail
    order.proceedToReview(); // Should fail (already in Review)
    order.completeOrder(); // Should fail (must confirm first)
    
    cout << "\n=== Testing Bidirectional Transition ===\n";
    
    // Review -> Order (bidirectional requirement)
    order.backToEditing();
    assert(order.getCurrentState()->getStateName() == "Order");
    
    // Test can modify again in Order state
    order.addPizza(extraPizza);
    assert(order.getPizzas().size() == 2);
    
    cout << "\n=== Testing StateConfirm ===\n";
    
    // Go back to Review and confirm
    order.proceedToReview();
    order.confirmOrder();
    assert(order.getCurrentState()->getStateName() == "Confirmed");
    
    // Test invalid operations in StateConfirm
    PizzaComponent* lateTopping = new Topping("Late Addition", 15.00);
    Pizza* latePizza = new BasePizza("Late Pizza", lateTopping);
    order.addPizza(latePizza); // Should fail
    order.removePizza(vegetarianPizza); // Should fail
    order.proceedToReview(); // Should fail
    order.backToEditing(); // Should fail
    order.confirmOrder(); // Should fail (already confirmed)
    
    cout << "\n=== Testing StateComplete ===\n";
    
    // Test valid operation in StateConfirm
    order.completeOrder(); // Should work
    assert(order.getCurrentState()->getStateName() == "Complete");
    
    // Test all operations should fail in StateComplete
    order.addPizza(latePizza); // Should fail
    order.removePizza(vegetarianPizza); // Should fail
    order.proceedToReview(); // Should fail
    order.backToEditing(); // Should fail
    order.confirmOrder(); // Should fail
    order.completeOrder(); // Should display order (allowed)
    
    // Cleanup
    delete latePizza;
    
    cout << "State Pattern tests completed!" << endl << endl;
}

void testCompleteStateFlow() {
    cout << "=================== Testing Complete State Flow ==================== " << endl << endl;
    
    ContextState order;
    order.setOrderNumber(9999);
    
    // Full workflow test with integrated patterns
    assert(order.getCurrentState()->getStateName() == "Order");
    
    // Create complex pizzas using Composite + Decorator
    PizzaComponent* supremeGroup = new ToppingGroup("Supreme");
    supremeGroup->add(new Topping("Pepperoni", 20.00));
    supremeGroup->add(new Topping("Mushroom", 12.00));
    supremeGroup->add(new Topping("Olives", 15.00));
    
    Pizza* basePizza = new BasePizza("Supreme Pizza", supremeGroup);
    Pizza* decoratedPizza = new StuffedCrust(new ExtraCheese(basePizza));
    
    Pizza* simplePizza = new BasePizza("Simple Pizza", new Topping("Cheese", 10.00));
    
    order.addPizza(decoratedPizza);
    order.addPizza(simplePizza);
    assert(order.getPizzas().size() == 2);
    
    cout << "Total order price: R" << order.getTotalPrice() << endl;
    
    order.proceedToReview();
    assert(order.getCurrentState()->getStateName() == "Review");
    
    order.confirmOrder();
    assert(order.getCurrentState()->getStateName() == "Confirmed");
    
    order.completeOrder();
    assert(order.getCurrentState()->getStateName() == "Complete");
    
    cout << "Complete state flow test passed!" << endl << endl;
}

int main() {
    cout << "Starting Comprehensive Design Pattern Testing..." << endl;
    cout << "================================================" << endl << endl;
    
    try {
        // Test individual patterns
        testCompositePattern();
        testDecoratorPattern();
        testStrategyPattern();
        testStatePattern();
        testObserverPattern();
        testStatePattern();
        
        // Test integrated system
        testCompleteStateFlow();
        
        cout << "================================================" << endl;
        cout << "ALL TESTS PASSED!" << endl;
        cout << "All design patterns implemented and working correctly." << endl;
        cout << "Test coverage includes:" << endl;
        cout << "- Composite Pattern: Complex topping structures" << endl;
        cout << "- Decorator Pattern: Pizza modifications with chaining" << endl;
        cout << "- Observer Pattern: Menu notifications with Pizza objects" << endl;
        cout << "- State Pattern: Complete order workflow with bidirectional transitions" << endl;
        cout << "- Pattern Integration: All patterns working together" << endl;
        
    } catch (const std::exception& e) {
        cout << "TEST FAILED: " << e.what() << endl;
        return 1;
    }
    
    return 0;

    return 0;
}

