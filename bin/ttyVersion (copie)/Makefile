CC=gcc
CXX=g++
RM=rm -rf
CPPFLAGS=-g $(ncusesw5-config --cflags)
LDFLAGS=-g $(ncusesw5-config --ldflags)
LDLIBS=$(ncusesw5-config  --libs)

SRCS=main.cpp ../../lib/interfacetty/interfacetty.cpp ../../lib/gründ/commun.cpp ../../lib/gründ/parser.cpp ../../lib/gründ/preParser.cpp ../../lib/gründ/Head.cpp ../../lib/gründ/Field.hpp ../../lib/gründ/Record.hpp ../../lib/gründ/recordSet.hpp ../../lib/gründ/table.hpp Vokabel.cpp pedagogie.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main -fpermissive $(OBJS) $(LDLIBS) 

main.o: main.cpp

interfacetty.o: ../../lib/interfacetty/interfacetty.cpp
commun.o: 	../../lib/gründ/commun.cpp

parser.o: 	../../lib/gründ/parser.cpp
preParser.o:	../../lib/gründ/preParser.cpp
Head.o:   	../../lib/gründ/Head.cpp
table.o:	../../lib/gründ/table.hpp
Record.o: 	../../lib/gründ/Record.hpp
recordSet.o:	../../lib/gründ/recordSet.hpp
Field.o:  	../../lib/gründ/Field.hpp


Vokabel.o: 	Vokabel.cpp
pedagogie.o: 	pedagogie.cpp


clean:
	$(RM) *.o ../../lib/gründ/*.o ../../lib/interfacetty/*.o ../../lib/parser/*.o ../../lib/preParser/*.o ../../lib/recordSet/*.o ../../lib/table/*.o

