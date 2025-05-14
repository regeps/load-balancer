CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iheader
SRC = src/request.cpp src/webserver.cpp src/loadbalancer.cpp src/main.cpp
OUT = app

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

run: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
