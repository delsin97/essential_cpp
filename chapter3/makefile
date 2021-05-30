app=$(patsubst %.cpp,%,$(wildcard *.cpp))

all:$(app)

%:%.cpp
	g++ $^ -o $@ -g

.PHONY:
	clean

clean:
	rm -rf $(app)