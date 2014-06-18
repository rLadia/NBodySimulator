CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic

TEST_EXECUTABLE=RunTests

OBJ_DIR=tests/objects
SRC_DIR=src
TEST_DIR=tests

src = gravity.cpp \
			model.cpp \
			modelobject.cpp \
			nbodysimulator.cpp \
			overlap.cpp \

test_src = display.cpp \
					 main.cpp \
					 tablelogger.cpp \
					 test_data.cpp \
					 test_file.cpp \
					 test_model.cpp \
					 util.cpp \

objects = $(src:%.cpp=$(OBJ_DIR)/%.o)
test_objects = $(test_src:%.cpp=$(OBJ_DIR)/%.o)

test: $(objects) $(test_objects)
	$(CXX) $(CXXFLAGS) $(objects) $(test_objects) -o $(TEST_EXECUTABLE) 

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $(TESTINCLUDE) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm $(TEST_EXECUTABLE) $(objects) $(test_objects) 2>/dev/null
