# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable names
TEST_TARGET = testing
DEMO_TARGET = demo

# Source files (add all your .cpp files here except the main files)
SOURCES = BasePizza.cpp \
          BulkDiscount.cpp \
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
          StuffedCrust.cpp \
          Topping.cpp \
          ToppingGroup.cpp \
          Website.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Main source files
TEST_MAIN = TestingMain.cpp
DEMO_MAIN = DemoMain.cpp

# Default target - runs the testing main (required by FitchFork)
run: $(TEST_TARGET)
	./$(TEST_TARGET)

# Build testing executable
$(TEST_TARGET): $(OBJECTS) $(TEST_MAIN:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(OBJECTS) $(TEST_MAIN:.cpp=.o)

# Build demo executable
$(DEMO_TARGET): $(OBJECTS) $(DEMO_MAIN:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $(DEMO_TARGET) $(OBJECTS) $(DEMO_MAIN:.cpp=.o)

# Build demo and run it
demo: $(DEMO_TARGET)
	./$(DEMO_TARGET)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build both executables
all: $(TEST_TARGET) $(DEMO_TARGET)

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TEST_MAIN:.cpp=.o) $(DEMO_MAIN:.cpp=.o) $(TEST_TARGET) $(DEMO_TARGET)

# Remove only object files
clean-obj:
	rm -f $(OBJECTS) $(TEST_MAIN:.cpp=.o) $(DEMO_MAIN:.cpp=.o)

# Rebuild everything from scratch
rebuild: clean all

# Show help information
help:
	@echo "Available targets:"
	@echo "  run        - Build and run testing main (default, used by FitchFork)"
	@echo "  demo       - Build and run demo main"
	@echo "  all        - Build both testing and demo executables"
	@echo "  clean      - Remove all generated files"
	@echo "  clean-obj  - Remove only object files"
	@echo "  rebuild    - Clean and rebuild everything"
	@echo "  help       - Show this help message"

# Declare phony targets
.PHONY: run demo all clean clean-obj rebuild help