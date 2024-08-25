# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -I./src/headers

# Source files
SRCDIR = src
OBJDIR = build
SRCEXT = cpp
OBJEXT = o
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(SOURCES:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.$(OBJEXT))

# Output executable
TARGET = snaildb

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build .o files from .cpp files
$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove build files
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean