# Titan Sovereign Build System
CXX = g++
CXXFLAGS = -O3 -mavx512f -std=c++20 -march=native
TARGET = SovereignVault

all: $(TARGET)

$(TARGET): SovereignVault_Titan_V3.cpp
	$(CXX) $(CXXFLAGS) SovereignVault_Titan_V3.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
