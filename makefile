CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall 
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
#LDFLAGS = -lboost_date_time

OBJS = main.o graph.o
# fileIO.o vertexClass.o

SRCS = main.cpp graph.cpp
# fileIO.cpp vertexClass.cpp

HEADERS = graph.h
# fileIO.h vertexClass.h

#target: dependencies
#	rule to build
#

Program: ${OBJS} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS} -o Program

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

Debug: 
