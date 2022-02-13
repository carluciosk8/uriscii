CC = g++
CFLAGS = -g -Wall -c
LDFLAGS = -g -Wall

SOURCES_COMMON = src/logic.cpp src/word.cpp src/reg.cpp src/adder.cpp src/alu.cpp src/extend.cpp src/memory.cpp src/reg_file.cpp src/control.cpp
SOURCES_URISC = $(SOURCES_COMMON) src/urisc.cpp src/main.cpp
SOURCES_URISCP = $(SOURCES_COMMON) src/forward.cpp src/jumpctrl.cpp src/control_pipe.cpp src/urisc_pipe.cpp src/main_pipe.cpp

OBJECTS_COMMON=$(SOURCES_COMMON:.cpp=.o)
OBJECTS_URISC=$(SOURCES_URISC:.cpp=.o)
OBJECTS_URISCP=$(SOURCES_URISCP:.cpp=.o)

EXECUTABLE_URISC = urisc
EXECUTABLE_URISCP = uriscp


all: $(SOURCES_URISC) $(SOURCES_URISCP) $(EXECUTABLE_URISC) $(EXECUTABLE_URISCP)

$(EXECUTABLE_URISC): $(OBJECTS_URISC)
	$(CC) $(LDFLAGS) $(OBJECTS_URISC) -o $@

$(EXECUTABLE_URISCP): $(OBJECTS_URISCP)
	$(CC) $(LDFLAGS) $(OBJECTS_URISCP) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f src/*.o $(EXECUTABLE_URISC) $(EXECUTABLE_URISCP)

test: $(EXECUTABLE_URISC)
	./$(EXECUTABLE_URISC) -a tests/test61.out -s
	@echo "Assert r4 == 3D (61 in hexadecimal)"

testp: $(EXECUTABLE_URISCP)
	./$(EXECUTABLE_URISCP) -a tests/test61.out -s
	@echo "Assert r4 == 3D (61 in hexadecimal)"
