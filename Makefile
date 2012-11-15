##
## Makefile
##  
## Made by wingsit
## Modified by eacousineau
## Login   <wingsitwingsit-desktop>
##
## Started on  Wed Sep 15 17:45:25 2010 wingsit
## Last update Wed Sep 15 17:45:25 2010 wingsit
## 
##############################
# Complete this to make it ! #
##############################

################
# Optional add #
################
INCLUDE   = -I. -I/usr/include/eigen3          # path of include file
CFLAGS  = -O4 -Wall -msse2 -fopenmp      # option for obj
LFLAGS  = -O4 -Wall -msse2 -fopenmp     # option for exe (-lefence ...)
LFLAGS += -L.           # path for librairies ... 

BASE_TARGET = simple
BASE_OBJS = simple.o EigenQP.o
BASE_HEADERS = 

STATIC_TARGET = simple_static
STATIC_OBJS = simple_static.o
STATIC_HEADERS = EigenQPStatic.hpp

#####################
# Macro Definitions #
#####################
CXX = g++
CFLAGS  += $(INCLUDE)

.PHONY: all clean
##############################
# Basic Compile Instructions #
##############################

all:	$(BASE_TARGET) $(STATIC_TARGET)
clean:
	-rm -f $(BASE_TARGET) $(STATIC_TARGET) *.o
	
$(STATIC_TARGET): $(STATIC_OBJS) $(STATIC_HEADERS)
	$(CXX) $(STATIC_OBJS) $(LFLAGS) -o $(STATIC_TARGET)
	
$(BASE_TARGET): $(BASE_OBJS) $(BASE_HEADERS)
	$(CXX) $(BASE_OBJS)  $(LFLAGS) -o $(BASE_TARGET)

.cpp.o:
	$(CXX) $(IPATH) $(CFLAGS) -c $< 
