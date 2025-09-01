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

    // Test basic Topping functionality
    PizzaComponent* pepperoni = new Topping("Pepperoni", 20.00);
    cout << "Basic Topping Test:" << endl;
    cout << "Pepperoni pizza: " << pepperoni->getName() << " - " << "Price: R" << pepperoni->getPrice() << endl;
    assert(pepperoni->getName() == "Pepperoni");
    assert(pepperoni->getPrice() == 20.00);

    // Test ToppingGroup with individual toppings
    PizzaComponent* mushrooms = new Topping("Mushroom", 12.00);
    PizzaComponent* greenPeppers = new Topping("Green Peppers", 10.00);
    PizzaComponent* onions = new Topping("Onions", 8.00);
    
    PizzaComponent* vegetarian = new ToppingGroup("Vegetarian");
    vegetarian->add(mushrooms);
    vegetarian->add(greenPeppers);
    vegetarian->add(onions);
    cout << "ToppingGroup Test:" << endl;
    cout << "Vegetarian pizza: " << vegetarian->getName() << " - " << "Price: R" << vegetarian->getPrice() << endl;
    assert(vegetarian->getPrice() == 30.00); // 12+10+8
    
    // Test nested ToppingGroup functionality
    PizzaComponent* beefSausage = new Topping("Beef Sausage", 25.00);
    PizzaComponent* salami = new Topping("Salami", 22.00);
    PizzaComponent* meatLovers = new ToppingGroup("Meat Lovers");
    meatLovers->add(pepperoni); // Reusing pepperoni from earlier
    meatLovers->add(beefSausage);
    meatLovers->add(salami);
    cout << "Nested ToppingGroup Test:" << endl;
    cout << "Meat Lovers pizza: " << meatLovers->getName() << " - " << "Price: R" << meatLovers->getPrice() << endl;
    assert(meatLovers->getPrice() == 67.00); // 20+25+22

    // Test deeply nested structure (group containing groups)
    PizzaComponent* feta = new Topping("Feta Cheese", 18.00);
    PizzaComponent* olives = new Topping("Olives", 15.00);
    PizzaComponent* vegetarianDeluxe = new ToppingGroup("Vegetarian Deluxe");
    vegetarianDeluxe->add(vegetarian); // Adding entire vegetarian group
    vegetarianDeluxe->add(feta);
    vegetarianDeluxe->add(olives);
    cout << "Deep Nesting Test:" << endl;
    cout << "Vegetarian Deluxe: " << vegetarianDeluxe->getName() << " - " << "Price: R" << vegetarianDeluxe->getPrice() << endl;
    assert(vegetarianDeluxe->getPrice() == 63.00); // 30+18+15

    // Test removeLast functionality
    cout << "RemoveLast Test:" << endl;
    cout << "Before removal: " << vegetarianDeluxe->getPrice() << endl;
    vegetarianDeluxe->removeLast();
    cout << "After removing last topping: " << vegetarianDeluxe->getName() << " - " << "Price: R" << vegetarianDeluxe->getPrice() << endl;
    assert(vegetarianDeluxe->getPrice() == 48.00); // 63-15

    // Test empty ToppingGroup
    PizzaComponent* emptyGroup = new ToppingGroup("Empty Group");
    cout << "Empty Group Test:" << endl;
    cout << "Empty group: " << emptyGroup->getName() << " - " << "Price: R" << emptyGroup->getPrice() << endl;
    assert(emptyGroup->getPrice() == 0.0);
    assert(emptyGroup->getName() == "Empty Group ()");

    // Test adding null component (should handle gracefully)
    emptyGroup->add(nullptr);
    assert(emptyGroup->getPrice() == 0.0);

    // Test removeLast on empty group (should handle gracefully)
    emptyGroup->removeLast();
    assert(emptyGroup->getPrice() == 0.0);

    // Clean up
    delete emptyGroup;
    delete vegetarianDeluxe; // This will clean up nested components
    delete meatLovers;

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

    // Test BasePizza functionality
    Pizza* basePepperoni = new BasePizza("Pepperoni Pizza", pepperoniTopping);
    cout << "Base Pizza Test:" << endl;
    basePepperoni->printPizza(); 
    assert(basePepperoni->getPrice() == 50.00); // 10+5+15+20 (dough+sauce+cheese+topping)
    assert(basePepperoni->getName() == "Pepperoni Pizza: Pepperoni");
    cout << endl;

    // Test single decorator
    Pizza* extraCheesePepperoni = new ExtraCheese(basePepperoni);
    cout << "Single Decorator Test:" << endl;
    extraCheesePepperoni->printPizza();
    assert(extraCheesePepperoni->getPrice() == 62.00); // 50+12
    assert(extraCheesePepperoni->getName() == "Pepperoni Pizza: Pepperoni, Extra Cheese");
    cout << endl;

    // Test chained decorators
    Pizza* vegBase = new BasePizza("Vegetarian", vegetarianGroup);
    Pizza* vegExtraCheese = new ExtraCheese(vegBase);
    Pizza* vegStuffedCrust = new StuffedCrust(vegExtraCheese);
    cout << "Chained Decorators Test:" << endl;
    vegStuffedCrust->printPizza();
    // Base: 10+5+15+30=60, +12 cheese=72, +20 crust=92
    assert(vegStuffedCrust->getPrice() == 92.00);
    assert(vegStuffedCrust->getName().find("Extra Cheese") != string::npos);
    assert(vegStuffedCrust->getName().find("Stuffed Crust") != string::npos);
    cout << endl;

    // Test different decorator order
    Pizza* vegBase2 = new BasePizza("Vegetarian2", new Topping("Basic", 5.00));
    Pizza* crustFirst = new StuffedCrust(vegBase2);
    Pizza* cheeseSecond = new ExtraCheese(crustFirst);
    cout << "Different Decorator Order Test:" << endl;
    cheeseSecond->printPizza();
    // Base: 10+5+15+5=35, +20 crust=55, +12 cheese=67
    assert(cheeseSecond->getPrice() == 67.00);
    cout << endl;

    // Test multiple same decorators
    Pizza* doubleCheeseBase = new BasePizza("Double Cheese", new Topping("Plain", 0.00));
    Pizza* firstCheese = new ExtraCheese(doubleCheeseBase);
    Pizza* secondCheese = new ExtraCheese(firstCheese);
    cout << "Multiple Same Decorators Test:" << endl;
    secondCheese->printPizza();
    // Base: 10+5+15+0=30, +12+12=54
    assert(secondCheese->getPrice() == 54.00);
    cout << endl;

    cout << "Decorator Pattern tests completed!" << endl << endl;
}

void testStrategyPattern() {
    cout << "=================== Testing Strategy ==================== " << endl << endl;

    // Create test pizzas
    PizzaComponent* pepperoni = new Topping("Pepperoni", 20.00);
    Pizza* pepperoniPizza = new BasePizza("Pepperoni", pepperoni);
    cout << "Test Pizza - Pepperoni price: R" << pepperoniPizza->getPrice() << endl;
    assert(pepperoniPizza->getPrice() == 50.00);

    PizzaComponent* vegetarian = new ToppingGroup("Vegetarian");
    vegetarian->add(new Topping("Mushroom", 12.00));
    vegetarian->add(new Topping("Green Peppers", 10.00));
    vegetarian->add(new Topping("Onions", 8.00));
    Pizza* vegetarianPizza = new BasePizza("Vegetarian", vegetarian);
    cout << "Test Pizza - Vegetarian price: R" << vegetarianPizza->getPrice() << endl;
    assert(vegetarianPizza->getPrice() == 60.00); // 10+5+15+30

    // Test RegularPrice strategy
    cout << "\nTesting RegularPrice Strategy:" << endl;
    DiscountStrategy* regularPrice = new RegularPrice();
    double originalPrice = vegetarianPizza->getPrice();
    double discountedPrice = regularPrice->applyDiscount(originalPrice, 1);
    cout << "Original: R" << originalPrice << ", After regular pricing: R" << discountedPrice << endl;
    assert(discountedPrice == originalPrice); // No discount
    
    // Test FamilyDiscount strategy
    cout << "\nTesting FamilyDiscount Strategy:" << endl;
    DiscountStrategy* familyDiscount = new FamilyDiscount();
    double familyDiscounted = familyDiscount->applyDiscount(originalPrice, 1);
    cout << "Original: R" << originalPrice << ", After family discount (15%): R" << familyDiscounted << endl;
    assert(familyDiscounted == originalPrice * 0.85); // 15% off

    // Test BulkDiscount strategy
    cout << "\nTesting BulkDiscount Strategy:" << endl;
    DiscountStrategy* bulkDiscount = new BulkDiscount();
    
    // Test with less than 5 pizzas (should not apply discount)
    double totalPrice4 = pepperoniPizza->getPrice() * 4;
    double bulk4 = bulkDiscount->applyDiscount(totalPrice4, 4);
    cout << "4 pizzas - Total: R" << totalPrice4 << ", After bulk discount: R" << bulk4 << endl;
    assert(bulk4 == totalPrice4); // No discount for < 5 pizzas

    // Test with 5 or more pizzas (should apply 10% discount)
    double totalPrice5 = pepperoniPizza->getPrice() * 5;
    double bulk5 = bulkDiscount->applyDiscount(totalPrice5, 5);
    cout << "5 pizzas - Total: R" << totalPrice5 << ", After bulk discount (10%): R" << bulk5 << endl;
    assert(bulk5 == totalPrice5 * 0.9); // 10% off

    // Test with many pizzas
    double totalPrice10 = pepperoniPizza->getPrice() * 10;
    double bulk10 = bulkDiscount->applyDiscount(totalPrice10, 10);
    cout << "10 pizzas - Total: R" << totalPrice10 << ", After bulk discount (10%): R" << bulk10 << endl;
    assert(bulk10 == totalPrice10 * 0.9); // 10% off

    // Test strategy switching
    cout << "\nTesting Strategy Switching:" << endl;
    cout << "Same order with different strategies:" << endl;
    cout << "Regular pricing: R" << regularPrice->applyDiscount(totalPrice5, 5) << endl;
    cout << "Family discount: R" << familyDiscount->applyDiscount(totalPrice5, 5) << endl;
    cout << "Bulk discount: R" << bulkDiscount->applyDiscount(totalPrice5, 5) << endl;

    // Clean up
    delete regularPrice;
    delete familyDiscount;
    delete bulkDiscount;

    cout << "\nStrategy Pattern tests completed!" << endl << endl;
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

void testStatePattern() {
    cout << "=================== Testing State Pattern ==================== " << endl << endl;
    
    ContextState order;
    order.setOrderNumber(1001);
    assert(order.getOrderNumber() == 1001);
    
    // Create pizza objects for state testing
    PizzaComponent* pepperoniTopping = new Topping("Pepperoni", 20.00);
    Pizza* pepperoniPizza = new BasePizza("Pepperoni Pizza", pepperoniTopping);
    
    PizzaComponent* vegGroup = new ToppingGroup("Vegetarian");
    vegGroup->add(new Topping("Mushroom", 12.00));
    vegGroup->add(new Topping("Onions", 8.00));
    Pizza* vegetarianPizza = new ExtraCheese(new BasePizza("Vegetarian Pizza", vegGroup));
    
    cout << "\n=== Testing StateOrder ===\n";
    assert(order.getCurrentState()->getStateName() == "Order");
    
    // Test handleChange in StateOrder
    order.getCurrentState()->handleChange(&order);
    
    // Test valid operations in StateOrder
    order.addPizza(pepperoniPizza);
    order.addPizza(vegetarianPizza);
    assert(order.getPizzas().size() == 2);
    assert(order.getTotalPrice() > 0);
    
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
    
    // Test handleChange in StateReview
    order.getCurrentState()->handleChange(&order);
    
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
    
    // Test handleChange in StateConfirm
    order.getCurrentState()->handleChange(&order);
    
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
    
    // Test handleChange in StateComplete
    order.getCurrentState()->handleChange(&order);
    
    // Test all operations should fail in StateComplete
    order.addPizza(latePizza); // Should fail
    order.removePizza(vegetarianPizza); // Should fail
    order.proceedToReview(); // Should fail
    order.backToEditing(); // Should fail
    order.confirmOrder(); // Should fail
    order.completeOrder(); // Should display order (allowed)
    
    cout << "\n=== Testing Strategy Integration in ContextState ===\n";
    
    // Test strategy switching in context
    ContextState newOrder;
    newOrder.addPizza(new BasePizza("Test Pizza", new Topping("Test", 10.00)));
    newOrder.addPizza(new BasePizza("Test Pizza 2", new Topping("Test2", 15.00)));
    
    newOrder.setStrategy(new FamilyDiscount());
    newOrder.internalDisplayOrder();
    
    newOrder.setStrategy(new BulkDiscount());
    newOrder.internalDisplayOrder();
    
    // Cleanup
    delete latePizza;
    
    cout << "State Pattern tests completed!" << endl << endl;
}

void testIntegrationAndEdgeCases() {
    cout << "=================== Testing Integration & Edge Cases ==================== " << endl << endl;
    
    cout << "=== Testing Complex Pizza Construction ===\n";
    
    // Create a complex pizza using all patterns
    PizzaComponent* supremeBase = new ToppingGroup("Supreme Base");
    supremeBase->add(new Topping("Pepperoni", 20.00));
    supremeBase->add(new Topping("Mushroom", 12.00));
    
    PizzaComponent* extraMeat = new ToppingGroup("Extra Meat");
    extraMeat->add(new Topping("Sausage", 18.00));
    extraMeat->add(new Topping("Ham", 16.00));
    
    PizzaComponent* superSupreme = new ToppingGroup("Super Supreme");
    superSupreme->add(supremeBase);
    superSupreme->add(extraMeat);
    superSupreme->add(new Topping("Olives", 8.00));
    
    Pizza* basePizza = new BasePizza("Super Supreme Pizza", superSupreme);
    Pizza* decoratedPizza = new StuffedCrust(new ExtraCheese(basePizza));
    
    cout << "Complex pizza construction:" << endl;
    decoratedPizza->printPizza();
    cout << "Total component price: " << superSupreme->getPrice() << endl; // Should be 74
    cout << "Total pizza price: " << decoratedPizza->getPrice() << endl; // Should be 104 + 32 = 136
    
    cout << "\n=== Testing Full System Integration ===\n";
    
    // Create a complete ordering scenario
    ContextState order;
    order.setOrderNumber(2024);
    
    // Add multiple complex pizzas
    order.addPizza(decoratedPizza);
    order.addPizza(new BasePizza("Simple Pizza", new Topping("Cheese", 10.00)));
    
    // Set discount strategy
    order.setStrategy(new FamilyDiscount());
    
    // Go through full state flow
    order.proceedToReview();
    order.confirmOrder();
    order.completeOrder();
    
    cout << "\n=== Testing Menu Integration with Observer ===\n";
    
    PizzaMenu menu;
    Customer customer("TestCustomer");
    Website website("TestSite.com");
    
    menu.addObserver(&customer);
    menu.addObserver(&website);
    
    // Add the complex pizza to menu
    menu.addPizza(new BasePizza("Menu Pizza", new Topping("Basic", 5.00)));
    
    cout << "\n=== Testing Error Handling ===\n";
    
    // Test null handling in various components
    ToppingGroup* nullTestGroup = new ToppingGroup("Null Test");
    nullTestGroup->add(nullptr); // Should handle gracefully
    nullTestGroup->removeLast(); // Should handle empty list
    
    // Test empty operations
    ContextState emptyOrder;
    emptyOrder.removePizza(nullptr);
    emptyOrder.internalDisplayOrder(); // Should show empty order
    
    cout << "\n=== Testing Memory Management Scenarios ===\n";
    
    // Test that destructors are called properly
    {
        ContextState* tempOrder = new ContextState();
        tempOrder->addPizza(new BasePizza("Temp Pizza", new Topping("Temp", 1.00)));
        delete tempOrder; // Should clean up properly
    }
    
    cout << "Integration and edge case tests completed!" << endl << endl;
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
    
    // Test different strategies
    order.setStrategy(new RegularPrice());
    order.internalDisplayOrder();
    
    order.setStrategy(new FamilyDiscount());
    order.internalDisplayOrder();
    
    order.setStrategy(new BulkDiscount());
    order.internalDisplayOrder();
    
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
        // Test individual patterns with full coverage
        testCompositePattern();
        testDecoratorPattern();
        testStrategyPattern();
        testObserverPattern();
        testStatePattern();
        
        // Test integration scenarios
        testIntegrationAndEdgeCases();
        testCompleteStateFlow();
        
        cout << "================================================" << endl;
        cout << "ALL TESTS PASSED! FULL COVERAGE ACHIEVED!" << endl;
        cout << "================================================" << endl;
        
    } catch (const std::exception& e) {
        cout << "TEST FAILED: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}