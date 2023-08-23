CC = $(shell wx-config --cxx)
CFLAGS := -Wall -g -std=c++20 -Wl,--rpath,/usr/local/lib/
SOURCES := $(wildcard src/*.cpp)
INCLUDE := inc
INC_FLAGS := $(addprefix -I,$(INCLUDE))
WX_CONFIG = $(shell wx-config --cxxflags --libs)
TARGET := ./out/fixlator

$(TARGET): $(SOURCES)
	$(CC) $(CFLGAS) -o $(TARGET) $(SOURCES) $(INC_FLAGS) $(WX_CONFIG)

.PHONY:	clean
clean:
	rm $(TARGET)
