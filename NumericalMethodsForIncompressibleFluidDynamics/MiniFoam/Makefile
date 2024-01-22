# -*- Makefile -*-
#target: dependencies
#	action

#main: main.o src/mesh/polyMesh.o
#	g++ main.o src/mesh/polyMesh.o -o main
#main.o: main.cpp 
#	g++ -c main.cpp
#src/mesh/polyMesh.o:  src/mesh/operators.hpp src/mesh/polyMesh.hpp
#	g++ -c src/mesh/polyMesh.cpp
#	mv polyMesh.o src/mesh 

src = src		#src = $(wildcard src/*)
sol = /applications/solvers
bin = platforms/bin
lib = platforms/lib

#INCLUDE_PATH=src/

all: platforms/lib/operators.o platforms/lib/fvMesh.o platforms/bin/laplacianFoam.out


platforms/bin/laplacianFoam.out: applications/solvers/laplacianFoam/laplacianFoam.cpp platforms/lib/fvMesh.o 
	g++ applications/solvers/laplacianFoam/laplacianFoam.cpp platforms/lib/fvMesh.o platforms/lib/operators.o  -o laplacianFoam.out -g
	mv laplacianFoam.out ${bin}

platforms/lib/fvMesh.o: src/finiteVolume/fvMesh/fvMesh.hpp src/finiteVolume/fvMesh/fvMesh.cpp 
	g++ -c src/finiteVolume/fvMesh/fvMesh.cpp -g
	mv fvMesh.o ${lib}

platforms/lib/operators.o: src/math/operators.hpp src/math/operators.cpp
	g++ -c src/math/operators.cpp -g
	mv operators.o ${lib}

clean:
	-rm -r platforms/bin/*.out
	-rm -r platforms/lib/*.o



# libraries:
# 	for dir in $(LIBS); do \
# 		cd $$dir; \
# 		gcc -c *.c -I../; \
# 		mv *.o ../../libraries; \
# 		cd -; \
# 	done




# ${sol}laplacianFoam.cpp
# 	g++ $(wildcard )




# all:  src/mesh/operators.o src/mesh/polyMesh.o main.o  main 

# main: main.o src/mesh/polyMesh.o src/mesh/operators.o
# 	g++ -Wall main.o src/mesh/polyMesh.o src/mesh/operators.o -o main

# main.o: main.cpp
# 	g++ -c main.cpp 

# src/mesh/polyMesh.o: src/mesh/polyMesh.cpp src/mesh/polyMesh.hpp 
# 	g++ -c src/mesh/polyMesh.cpp
# 	mv polyMesh.o src/mesh

# src/mesh/operators.o: src/mesh/operators.cpp src/mesh/operators.hpp
# 	g++ -c src/mesh/operators.cpp
# 	mv operators.o src/mesh

# clean:
# 	rm -r src/mesh/*.o;










# main.out: polyMesh.o	main.o
# 	g++ main.o polyMesh.o -o main.out
# polyMesh.o: polyMesh.cpp
# 	g++ -c polyMesh.cpp -o polyMesh.o
# main.o : main.cpp
# 	g++ -c main.cpp -o main.o
# LIBS = src/mesh src/math
# INCLUDE_PATH = src/

# main:	libraries

# libraries:
# 	mkdir libraries/
# 	for dir in $(LIBS); do \
# 		cd $$dir; \
# 		g++ -c *.cpp -I../; \
# 		mv *.o ../../libraries; \
# 		cd -; \
# 	done

# clean
