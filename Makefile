# Titan Sovereign Build System - V6.1.0-Omni
# Optimized for Alaa Aljohani's SovereignVault Core

CXX = g++
# Optimized flags for AVX-512, RDSEED Hardware Entropy, and C++20 Standards
CXXFLAGS = -O3 -mavx512f -mavx512vl -mavx512bw -mavx512dq -mrdseed -std=c++20 -march=native
TARGET = SovereignVault

all: $(TARGET)

$(TARGET): SovereignVault_Titan.cpp
	$(CXX) $(CXXFLAGS) SovereignVault_Titan.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
