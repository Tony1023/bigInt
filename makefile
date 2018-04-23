CPPFLAGS = -Wall -std=c++11
CXX = clang++
BIN = bin

run: test
	./test

test: test.cpp $(BIN)/bigInt.o $(BIN)/p_int.o $(BIN)/negativeExcept.o
	$(CXX) $(CPPFLAGS) $^ -o test

$(BIN)/p_int.o: p_int.cpp p_int.h $(BIN)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN)/negativeExcept.o: negativeExcept.cpp negativeExcept.h $(BIN)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN)/bigInt.o: bigInt.cpp bigInt.h $(BIN)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN)/.dirstamp:
	mkdir -p $(BIN)
	touch $(BIN)/.dirstamp

.PHONY: clean
clean:
	rm -rf $(BIN) test
