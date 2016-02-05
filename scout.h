/*************
*
*	Deven Thiel
*
*	05.08.2015
*
*	Scout class outline for artificially intelligent object
*
*************/

#ifndef SCOUT_H
#define SCOUT_H

#include "cmath"

#include "dArray.h"

struct square
{
	bool obstructed;
	bool viewed;
	bool visited;
};

struct coord
{
	int x;
	int y;
};

class Scout
{
	public:
	
		//default constructor
		Scout (int);
	
		//default destructor
		~Scout ();
	
		//scout stats
		void setViewRange (int);
		int getViewRange ();
	
		void setSteps (int);
		int getSteps ();
		void incSteps ();
	
		//map
		void setCoordCurrent (int, int);
		void setCoordCurrent (coord *);
		coord * getCoordCurrent();
	
		void setMapSquare (int, int, bool, bool, bool);
		void setMapSquare (coord *, square *);
		square * getMapSquare (int, int);
		square * getMapSquare (coord*);
	
		void addMapSquare (int, int, bool, bool, bool);
		void addMapSquare (coord *, square *);
		void delMapSquare (int, int);
		void delMapSquare (coord *);
	
		void setMapSize (int, int);
		void setMapSize (coord *);
		coord * getMapSize ();
	
		void setMapOffset (int, int);
		void setMapOffset (coord *);
		coord * getMapOffset ();
	
		void setTargetFound (bool);
		bool getTargetFound ();
		void setTargetCoord (int, int);
		void setTargetCoord (coord *);
		coord * getTargetCoord ();
	
		//functionality
		//grows map by 1 row, 1 column or both/
		void growMap(char);
	
		void addColumn ();
		void addRow ();
		void shiftColumn ();
		void shiftRow ();
	
		void addPathSquare (square *);
		void clearPath();
		square * getPathStep (int);
	
		int getShell (int, int);
		int getShell (coord *);
	
		int viewSize (int);
	
		//runs the whole thing
		coord * runScout (coord *, square *);
	
		//make 1 move
		coord * move ();
	
		//observe everything in view range
		void look (coord *, square *);
	
		//returns next move
		coord * pathfinder ();
	
		//returns next move directly to target
		coord * direct ();
		
		//returns next move when exploring
		coord * explore ();
	
		//returns next move when traversing explored area
		coord * traverse ();
	
		//updates map with observations
		void observe (coord *, square *);
	
	private:
	
		//scout stats
		int viewRange;
		int steps;
		
		//current position
		coord current;
	
		//internal map
		DArray<DArray<square *> > Map;
		coord mapSize;
		//offset to origin / location of start
		coord mapOffset;
	
		//path saved
		DArray<square *> path;
	
		//target
		bool found;
		coord target;
};

#endif