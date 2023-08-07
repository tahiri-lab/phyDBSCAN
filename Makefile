CXX = g++
CXXFLAGS = -std=c++17 -I./include
LDFLAGS =
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
HEADERS = $(wildcard include/*.h)
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = phyDBSCAN

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)
