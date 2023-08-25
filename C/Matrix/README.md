///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------//
// Programming Assignment 4 -------------------------------------------------//
// Introduction to Data Structures and Algorithms ---------------------------//
// by Morgan Lloyd, moclloyd@ucsc.edu ---------------------------------------//
//---------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////

Files Submitted:

List.h		Header file for the List ADT.
		Written by me

List.c		Implementation file for the List ADT. 
		Written by me. Queue.c example was referenced in some areas.

ListTest.c	Test client for List ADT.
		Written by me.

Matrix.c	Implementation file for the Matrix ADT.
		Written by me.

Matrix.h	Header file for the Matrix ADT.
		Written by me.

MatrixTest.c	Test client for the Matrix ADT.
		Written by me.

Sparse.c	Client file for the Matrix ADT.
		Written by me.
		Usage:
		./Sparse <input file> <output file>

Makefile	Makefile for pa4
		Altered from class webpage.
		Usage:
		make                     makes Sparse
  		make MatrixTest          makes MatrixTest
  		make ListTest            makes ListTest
  		make clean               removes all binaries
  		make SparseCheck         runs Sparse in valgrind on in5
  		make MatrixCheck         runs MatrixTest in valgrind
  		make ListCheck           runs ListTest in valgrind
    