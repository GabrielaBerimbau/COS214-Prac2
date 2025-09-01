# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executables
TARGET = pizza_demo
TEST_TARGET = test_pizza

# Source files
COMMON_SOURCES = BasePizza.cpp \
          BulkDiscount.cpp \
          ContextState.cpp \
          Customer.cpp \
          DiscountStrategy.cpp \
          ExtraCheese.cpp \
          FamilyDiscount.cpp \
          Menus.cpp \
          Observer.cpp \
          Pizza.cpp \
          PizzaDecorator.cpp \
          PizzaMenu.cpp \
          RegularPrice.cpp \
          SpecialsMenu.cpp \
          StateComplete.cpp \
          StateConfirm.cpp \
          StateOrder.cpp \
          StateReview.cpp \
          StuffedCrust.cpp \
          Topping.cpp \
          ToppingGroup.cpp \
          Website.cpp 

MAIN_SOURCE = DemoMain.cpp
TEST_MAIN_SOURCE = TestingMain.cpp

# Object files
COMMON_OBJECTS = $(COMMON_SOURCES:.cpp=.o)
MAIN_OBJECT = $(MAIN_SOURCE:.cpp=.o)
TEST_MAIN_OBJECT = $(TEST_MAIN_SOURCE:.cpp=.o)

# Default target
all: $(TARGET) $(TEST_TARGET)

# Build main application
$(TARGET): $(COMMON_OBJECTS) $(MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(COMMON_OBJECTS) $(MAIN_OBJECT)

# Build test application
$(TEST_TARGET): $(COMMON_OBJECTS) $(TEST_MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(COMMON_OBJECTS) $(TEST_MAIN_OBJECT)

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run test program
run: $(TEST_TARGET)
	./$(TEST_TARGET)

# Run demo program
demo: $(TARGET)
	./$(TARGET)

# Coverage analysis
cov: clean
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -c $(COMMON_SOURCES) $(TEST_MAIN_SOURCE)
	$(CXX) $(CXXFLAGS) $(COVERAGE_FLAGS) -o $(TEST_TARGET) *.o
	./$(TEST_TARGET)
	gcov *.cpp
	@echo ""
	@echo "=== Coverage Summary ==="
	@grep "Lines executed" *.cpp.gcov 2>/dev/null | head -10 || echo "Coverage files generated. Use 'ls *.gcov' to see all files."
	@echo ""
	@echo "To view detailed coverage for a specific file, use: less <filename>.cpp.gcov"

# Clean up
clean:
	rm -f *.o *.gcda *.gcno *.gcov $(TARGET) $(TEST_TARGET)

.PHONY: all run run-demo cov clean