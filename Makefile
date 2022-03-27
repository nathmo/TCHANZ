#
#  \file   Makefile
#  \author Nathann Morand et Felipe Ramirez
#  \date   MARS 2022
#  \brief  Makefile du projet pour la compilation des dépendances et le linkage

CXX         = g++
CXXFLAGS    = -g -Wall -std=c++11
OFILESBUILD = projet.o error_squarecell.o fourmi.o fourmiliere.o message.o nourriture.o simulation.o squarecell.o textstorage.o entity.o
OFILESTEST  = testsuit.o error_squarecell.o fourmi.o fourmiliere.o message.o nourriture.o simulation.o squarecell.o textstorage.o entity.o

build: projet
all: projet

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet
# ----------------------------------------------------------------------------------------------------------------------
error_squarecell.o : error_squarecell.cc error_squarecell.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

fourmi.o : fourmi.cc fourmi.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

fourmiliere.o : fourmiliere.cc fourmiliere.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

message.o : message.cc message.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

nourriture.o : nourriture.cc nourriture.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

simulation.o : simulation.cc simulation.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

entity.o : entity.cc entity.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

squarecell.o : squarecell.cc squarecell.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

textstorage.o : textstorage.cc textstorage.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

projet.o : projet.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

testsuit.o : testsuit.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ----------------------------------------------------------------------------------------------------------------------

projet :  $(OFILESBUILD)
	$(CXX) $(OFILESBUILD) -o $@

test : $(OFILESTEST)
	@echo " *** Lance les test définit dans testsuit ***"
	$(CXX) $(OFILESTEST) -o $@
	./test