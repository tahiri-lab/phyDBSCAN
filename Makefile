# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = bin/poc
SRCDIR = src
INCDIR = include
OBJDIR = out
BINDIR = bin
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
DATA_FILE = resources/input_data.txt

# Création des dossiers
$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(BINDIR))

# Règles
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(DATA_FILE)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

.PHONY: all run clean
