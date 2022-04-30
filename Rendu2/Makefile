#
#  \file   Makefile
#  \author Nathann Morand et Felipe Ramirez
#  \date   MARS 2022
#  \brief  Makefile du projet pour la compilation des dépendances et le linkage

CXX         = g++
CXXFLAGS    = -g -Wall -std=c++11
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
OFILESBUILD = projet.o error_squarecell.o fourmi.o fourmiliere.o message.o nourriture.o simulation.o squarecell.o textstorage.o entity.o gui.o graphic.o
OFILESTEST  = testsuit.o error_squarecell.o fourmi.o fourmiliere.o message.o nourriture.o simulation.o squarecell.o textstorage.o entity.o gui.o graphic.o

build: projet
all: projet

clean:
	@echo " *** EFFACE MODULES OBJET ET EXECUTABLE ***"
	@/bin/rm -f *.o *.x *.cc~ *.h~ projet test
# ----------------------------------------------------------------------------------------------------------------------
error_squarecell.o : error_squarecell.cc error_squarecell.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

fourmi.o : fourmi.cc fourmi.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

fourmiliere.o : fourmiliere.cc fourmiliere.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

message.o : message.cc message.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

nourriture.o : nourriture.cc nourriture.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

simulation.o : simulation.cc simulation.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

entity.o : entity.cc entity.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

squarecell.o : squarecell.cc squarecell.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

textstorage.o : textstorage.cc textstorage.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

gui.o : gui.cc gui.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

graphic.o : graphic.cc graphic.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

projet.o : projet.cc
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

testsuit.o : testsuit.cc
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@

# ----------------------------------------------------------------------------------------------------------------------

projet :  $(OFILESBUILD)
	$(CXX) $(OFILESBUILD) $(LINKING) -o $@ $(LDLIBS)

test : $(OFILESTEST)
	@echo " *** Lance les test définit dans testsuit ***"
	$(CXX) $(OFILESTEST) $(LINKING) -o $@ $(LDLIBS)
	./test