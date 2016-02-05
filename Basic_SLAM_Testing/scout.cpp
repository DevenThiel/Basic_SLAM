/*************
*
*	Deven Thiel
*
*	05.08.2015
*
*	Scout class implimentation for artificially intelligent object
*
*************/

#include "scout.h"

//default constructor
Scout::Scout (int vRange)
{
	//start the internal map with just this one square
	//The assumption is that the scout starts in an unobstructed location that
	//	does not contain the target. the goal is to end up in a target adjacent
	//	location, so we might not have to move still.
	Map.addElement();
	Map[0].addElement();
	Map[0][0] = new square;
	Map[0][0]->obstructed = false;
	Map[0][0]->viewed = true;
	Map[0][0]->visited = true;
	
	viewRange = vRange;
	steps = 0;
	
	current.x = 0;
	current.y = 0;
	
	mapSize.x = 1;
	mapSize.y = 1;
	
	mapOffset.x = 0;
	mapOffset.y = 0;
	
	found = false;
	target.x = 0;
	target.y = 0;
}
	
//default destructor
Scout::~Scout ()
{
	//need to destroy the whole map.
	for (int i = 0; i < mapSize.x; i++)
	{
		for (int j = 0; j < mapSize.y; j++)
		{
			if (Map[i][j] != NULL)
			{
				delete Map[i][j];
			}
		}
	}
}
	
//scout stats
void Scout::setViewRange (int inint)
{
	viewRange = inint;
}

int Scout::getViewRange ()
{
	return viewRange;
}

void Scout::setSteps (int inint)
{
	steps = inint;
}

int Scout::getSteps ()
{
	return steps;
}

void Scout::incSteps ()
{
	steps++;
}

//map
void Scout::setCoordCurrent (int inX, int inY)
{
	current.x = inX;
	current.y = inY;
}

void Scout::setCoordCurrent (coord * inCoord)
{
	current.x = inCoord->x;
	current.y = inCoord->y;
}

coord * Scout::getCoordCurrent()
{
	coord * temp;
	temp = new coord;
	temp->x = current.x;
	temp->y = current.y;
		
	return temp;
}
	
void Scout::setMapSquare (int inX, int inY, bool inObstructed, bool inViewed, bool inVisited)
{
	while (inX >= mapSize.x || inX < 0 || inY >= mapSize.y || inY < 0)
	{
		if (inY >= mapSize.y && inX > 0 && inX < mapSize.x)
		{
			growMap('w');
		}
		else if (inY < 0 && inX > 0 && inX < mapSize.x)
		{
			growMap('x');
		}
		else if (inX < 0 && inY > 0 && inY < mapSize.y)
		{
			growMap('a');
		}
		else if (inX >= mapSize.x && inY > 0 && inY < mapSize.y)
		{
			growMap('d');
		}
		else if (inX >= mapSize.x && inY >= mapSize.y)
		{
			growMap('e');
		}
		else if (inX >= mapSize.x && inY < 0)
		{
			growMap('c');
		}
		else if (inX < 0 && inY < 0)
		{
			growMap('z');
		}
		else if (inX < 0 && inY >= mapSize.y)
		{
			growMap('q');
		}
	}
		Map[inX][inY]->obstructed = inObstructed;
		Map[inX][inY]->viewed = inViewed;
		Map[inX][inY]->visited = inVisited;	
}

void Scout::setMapSquare (coord * inCoord, square * inSquare)
{
	setMapSquare(inCoord->x, inCoord->y, inSquare->obstructed, inSquare->viewed, inSquare->visited);
}

square * Scout::getMapSquare (int inX, int inY)
{
	return Map[inX][inY];
}

square * Scout::getMapSquare (coord * inCoord)
{
	return getMapSquare(inCoord->x, inCoord->y);
}

void Scout::addMapSquare (int inX, int inY, bool inObstructed, bool inViewed, bool inVisited)
{
	setMapSquare (inX, inY, inObstructed, inViewed, inVisited);
}

void Scout::addMapSquare (coord * inCoord, square * inSquare)
{
	setMapSquare(inCoord->x, inCoord->y, inSquare->obstructed, inSquare->viewed, inSquare->visited);
}

void Scout::delMapSquare (int inX, int inY)
{
	delete Map[inX][inY];
	Map[inX][inY] = NULL;
}

void Scout::delMapSquare (coord * inCoord)
{
	delMapSquare(inCoord->x, inCoord->y);
}
	
void Scout::setMapSize (int inMapSizeX, int inMapSizeY)
{
	mapSize.x = inMapSizeX;
	mapSize.y = inMapSizeY;
}

void Scout::setMapSize (coord * mapCoord)
{
	mapSize.x = mapCoord->x;
	mapSize.y = mapCoord->y;
}

coord * Scout::getMapSize ()
{ 
	coord * temp;
	temp = new coord;
	temp->x = mapSize.x;
	temp->y = mapSize.y;

	return temp;
}
	
void Scout::setMapOffset (int inMapOffsetX, int inMapOffsetY)
{
	mapOffset.x = inMapOffsetX;
	mapOffset.y = inMapOffsetY;
}
		
void Scout::setMapOffset (coord * inCoord)
{
	mapOffset.x = inCoord->x;
	mapOffset.x = inCoord->y;
}
		
coord * Scout::getMapOffset ()
{
	coord * temp;
	temp = new coord;
	temp->x = mapOffset.x;
	temp->y = mapOffset.y;
	
	return temp;
}
	
void Scout::setTargetFound (bool inbool)
{
	found = inbool;
}

bool Scout::getTargetFound ()
{
	return found;
}

void Scout::setTargetCoord (int inX, int inY)
{
	target.x = inX;
	target.y = inY;
}

void Scout::setTargetCoord (coord * inCoord)
{
	setTargetCoord(inCoord->x, inCoord->y);
}

coord * Scout::getTargetCoord ()
{
	return &target;
}

//functionality
//grows map by 1 row, 1 column or both/
void Scout::growMap(char inChar)
{
	//w - up
	//x - down
	//a - left
	//d - right
	//q - up & left
	//e - up & right
	//z - down & left
	//c - down & right
	
	switch (inChar)
	{
		case 'w':
			addRow();
			break;
		case 'x':
			addRow();
			shiftRow();
			break;
		case 'a':
			addColumn();
			shiftColumn();
			break;
		case 'd':
			addColumn();
			break;
		case 'q':
			addColumn();
			addRow();
			shiftColumn();
			break;
		case 'e':
			addColumn();
			addRow();
			break;
		case 'z':
			addColumn();
			addRow();
			shiftColumn();
			shiftRow();
			break;
		case 'c':
			addColumn();
			addRow();
			shiftRow();
			break;
		default:
			cout << "error" << endl;
	}
}

void Scout::addColumn ()
{
	//add 1 to outer array
	Map.addElement();
	
	//add y size to new inner array
	for (int i = 0; i < mapSize.y; i++)
	{
		Map[Map.getLength()].addElement();
	}
	
	//add 1 to X size
	mapSize.x ++;
}

void Scout::addRow ()
{
	//add 1 to each of the inner arrays
	for (int i = 0; i < mapSize.x; i++)
	{
		Map[i].addElement();
	}
	
	//add 1 to Y size
	mapSize.y++;
}

void Scout::shiftColumn ()
{
	//move every square 1 to the right
	for (int i = 0; i < (mapSize.x - 1); i++)
	{
		for (int j = 0; j < mapSize.y; j++)
		{
			Map[i+1][j] = Map[i][j];
		}
	}
	
	//zero the extra column
	for (int j = 0; j < mapSize.y; j++)
	{
		Map[0][j] = NULL;
	}
	
	//update offset
	mapOffset.x ++;
}

void Scout::shiftRow ()
{
	//move every square 1 up
	for (int i = 0; i < mapSize.x; i++)
	{
		for (int j = 0; j < (mapSize.y - 1); j++)
		{
			Map[i][j+1] = Map[i][j];
		}
	}
	
	//zero the extra row
	for (int i = 0; i < mapSize.x; i++)
	{
		Map[i][0] = NULL;
	}
	
	//update offset
	mapOffset.y ++;
}

void Scout::addPathSquare (square * inSquare)
{
	path.addElement();
	path[path.getLength() - 1] = inSquare;
}

void Scout::clearPath()
{
	while (path.getLength() != 0)
	{
		path.deleteElement();
	}
}

square * Scout::getPathStep (int inint)
{
	return path[inint];
}

int Scout::getShell (int inX, int inY)
{
	int x = 0;
	int y = 0;
	
	x = abs(inX - mapOffset.x);
	y = abs(inY - mapOffset.y);
	
	if (x >= y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

int Scout::getShell (coord * inCoord)
{
	return getShell(inCoord->x, inCoord->y);
}

int viewSize (int n)
{
	if (n == 0)
	{
		return 0;
	}
	
	return n*4 + viewSize(n -1);
}

//runs the whole thing.
coord * Scout::runScout (coord * inCoordArr, square * inSquareArr)
{
	//calls move, and look
	
	//paramenter is an array of square's of size viewrange
	look(inCoordArr,inSquareArr);
	
	//moves the scout based on known map
	return move ();
}
	
//make 1 move
coord * Scout::move ()
{
	//performs actual move after calling pathfinder
	
	coord * next;
	next = pathfinder ();
	
	current.x = next->x;
	current.y = next->y;
	steps++;
	
	return next;
}
	
//observe everything in view range
void Scout::look (coord * inCoordArr, square * inSquareArr)
{
	//use observe which element of the array
	for (int i = 0; i < viewSize(viewRange); i++)
	{
		observe(&inCoordArr[i],&inSquareArr[i]);
	}
}
	
//returns next move
coord * Scout::pathfinder ()
{
	//check if the target is found, if it is, move directly to it.
	if (found)
	{
		//move directly to target
		return direct();	
	}
	//else whole known map, if there are unvisited, unobstructed, viewed squares, call traverse
		//search whole map for viewed but not visited, if any are found, traverse.
	//else call explore
	return explore();
}

//returns next move directly to target
coord * Scout::direct ()
{
	//TODO
	//choose move in direction furthest
	// if it's obstructed,choose the other.
	coord * move;
	move = NULL;
	
	if (abs(current.x - target.x) >= abs(current.y - target.y))
	{
		if ( current.x > target.x)
		{
			if (!(Map[current.x - 1][current.y]->obstructed))
			{
				move->x = current.x - 1;
				move->y = current.y;
				return move;
			}
		}
		else 
		{
			if (!(Map[current.x + 1][current.y]->obstructed))
			{
				move->x = current.x + 1;
				move->y = current.y;
				return move;
			}
		}
	}
	else
	{
		if ( current.y > target.y)
		{
			if (!(Map[current.x][current.y - 1]->obstructed))
			{
				move->x = current.x;
				move->y = current.y - 1;
				return move;
			}
		}
		else 
		{
			if (!(Map[current.x][current.y + 1]->obstructed))
			{
				move->x = current.x;
				move->y = current.y + 1;
				return move;
			}
		}
	}
	return move;
}
		
//returns next move when exploring
coord * Scout::explore ()
{
	square * temp;
	temp = NULL;
	
	coord * move;
	move = new coord;
	
	//number 1
	// find the move 1 shell down (if it exists), if the origin is the same
	// distance away in x and y, there is no 1 step into a lower shell.
	
	if (abs(current.x - mapOffset.x) > abs(current.y - mapOffset.y))
	{
		if (current.x > mapOffset.x)
		{
			if ((temp = Map[current.x - 1][current.y]) != NULL)
			{
				if (temp->obstructed == false && temp->viewed == true && temp->visited == false)
				{
					move->x = current.x - 1;
					move->y = current.y;
					return move;
				}
			}
		}
		else if (current.x < mapOffset.x)
		{
			if ((temp = Map[current.x + 1][current.y]) != NULL)
			{
				if (temp->obstructed == false && temp->viewed == true && temp->visited == false)
				{
					move->x = current.x + 1;
					move->y = current.y;
					return move;
				}
			}
		}
	}
	else if (abs(current.x - mapOffset.x) < abs(current.y - mapOffset.y))
	{
		if (current.y > mapOffset.y)
		{
			if ((temp = Map[current.x][current.y - 1]) != NULL)
			{
				if (temp->obstructed == false && temp->viewed == true && temp->visited == false)
				{
					move->x = current.x;
					move->y = current.y - 1;
					return move;
				}
			}
		}
		else if (current.y < mapOffset.y)
		{
			if ((temp = Map[current.x][current.y + 1]) != NULL)
			{
				if (temp->obstructed == false && temp->viewed == true && temp->visited == false)
				{
					move->x = current.x;
					move->y = current.y + 1;
					return move;
				}
			}
		}
	}
	//if they are equal, so there is no step down a shell	

	//number 2
	//	find the two moves possible in the same shell. if there are two that are 
	//	ubstructed and unviewed...
	//	if the last move was up a shell, move opposite of the last move within a
	//	shell (2)
	//	if the last move was in the same shell (2) move in the same direction
	//	if the last move was down a shell, move the opposite direction of the last
	//	(2) move.
	//	if no previous move, choose x+ or y+

	// number 3
	//	find the 1 or 2 possible moves to the next shell up. if there are two, 
	//	choose the one that allows you to continue moving straight ahead

	// number 4
	//	find the 1 or 2 possible moves in the next shell that are unobstructed, but
	//	not unvisited. if there are 2, choose the most recent one visited.

	// number 5
	//	find the two moves possible in the same shell, if there are more than 1 
	//	unobstructed, but previously visited, move to the most recently visited.
	
	// number 6
	//	find the move 1 shell down that is unobstructed, but visited. move here.
	if (abs(current.x - mapOffset.x) > abs(current.y - mapOffset.y))
	{
		if (current.x > mapOffset.x)
		{
			if ((temp = Map[current.x - 1][current.y]) != NULL)
			{
				if (temp->obstructed == false && temp->viewed == true)
				{
					move->x = current.x - 1;
					move->y = current.y;
					return move;
				}
			}
		}
		else if (current.x < mapOffset.x)
		{
			if ((temp = Map[current.x + 1][current.y]) != NULL)
			{
				if (temp->obstructed == false && temp->viewed == true)
				{
					move->x = current.x + 1;
					move->y = current.y;
					return move;
				}
			}
		}
	}
	else if (abs(current.x - mapOffset.x) < abs(current.y - mapOffset.y))
	{
		if (current.y > mapOffset.y)
		{
			if ((temp = Map[current.x][current.y - 1]) != NULL)
			{
				if (temp->obstructed == false && temp->viewed == true)
				{
					move->x = current.x;
					move->y = current.y - 1;
					return move;
				}
			}
		}
		else if (current.y < mapOffset.y)
		{
			if ((temp = Map[current.x][current.y + 1]) != NULL)
			{
				if (temp->obstructed == false && temp->viewed == true)
				{
					move->x = current.x;
					move->y = current.y + 1;
					return move;
				}
			}
		}
	}
	
	// number 7 
	//	if you reach this, there's no where else to go.
	return NULL;
	
}
	
//returns next move when traversing explored area
coord * Scout::traverse ()
{
	//the base algo with view range in mind
	
	//TODO
	
	return NULL;
}
	
//updates map with observations
void Scout::observe (coord * inCoord, square * inSquare)
{
	//get view data
	square * temp;
	temp = Map[inCoord->x][inCoord->y];
	temp->obstructed = inSquare->obstructed;
	temp->viewed = true;
	temp->visited = true;
	
	if (inSquare->viewed)
	{
		found = true;
		target.x = inCoord->x;
		target.y = inCoord->y;
	}
}