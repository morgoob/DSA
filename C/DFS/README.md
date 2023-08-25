///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------//
// Programming Assignment 3 -------------------------------------------------//
// Introduction to Data Structures and Algorithms ---------------------------//
// by Morgan Lloyd, moclloyd@ucsc.edu ---------------------------------------//
//---------------------------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////

Files Submitted:

List.h		Header file for the List ADT. Included in List.c, Graph.c,
		Graph.h, GraphTest.c, and FindComponents.c
		Written by me

List.c		Implementation file for the List ADT. 
		Written by me. Queue.c example was referenced in some areas.

Graph.c		Implementation file for the Graph ADT.
		Written by me. Pseudocode on webpage was referenced.
		In function DFS(), time is local and &time is passed to
		Visit()
		
Graph.h		Header file for Graph ADT. Included in Graph.c, GraphTest.c,
		and FindComponents.c

GraphTest.c	Test client for Graph ADT.
		Written by me.

FindComponents.c
		Client program using Graph ADT. Finds strongly connected
		components of a digraph.
		Usage: ./FindComponents <input file> <output file>

Makefile	Makefile for pa3
		Altered from class webpage.
		Usage:
		make			makes FindPath
		make GraphTest		makes GraphTest
		make clean 		removes all binaries
		make checkFind		checks FindComponents for memory leaks 
		make checkTest		checks GraphTest for memory leaks
		