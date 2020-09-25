#include "OGLUtils.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

#define MAX 1000

using namespace std;

struct DataPointsT
{
	int x;
	int y;
	int ownCluster;
	DataPointsT* next;
};

struct ClusterT
{
	int x;
	int y;
	int prevX;
	int prevY;
	int dataCount;
	int clusterID;
	ClusterT* next;
};

DataPointsT* dataFront = NULL;
ClusterT* clusterFront = NULL;

void InitDataPoints();
void InitClusters();
void SelectCluster();
int Distance(int x1, int y1, int x2, int y2);
void DrawData();
void DrawCluster();
void DrawConnections(DataPointsT* data);
void CenterCluster();
bool ClusterComplete();
void PrintOwnData();
void PrintRound(int);

int main()
{
	int round = 0;
	int width, height;
	
	srand(time(NULL));

	InitDataPoints();
	InitClusters();
	
	InitWindow(MAX, MAX);
	do
	{
		ClearDevice();
		DrawData();
		DrawCluster();
		SelectCluster();
		CenterCluster();
		PrintRound(round);
		UpdateWindow();
		round++;
	} while (!ClusterComplete());
		
	cout << endl << " Clustering Complete!" << endl;
	system("pause");
	
	CloseGraph();
	return 0;
}

//CORE
void SelectCluster()
{
	DataPointsT* curData;
	ClusterT* curClust;
	int curDist, minDist;

	curData = dataFront;
	while (curData != NULL)
	{
		minDist = MAX + 1;
		curClust = clusterFront;
		while (curClust != NULL)
		{
			curDist = Distance(curData->x, curData->y, curClust->x, curClust->y);
			if (curDist < minDist) 
			{
				minDist = curDist;
				curData->ownCluster = curClust->clusterID;
			}
			curClust = curClust->next;
		}

		DrawConnections(curData);	
		curData = curData->next;
	}
}

void CenterCluster()
{
	DataPointsT* curData;
	ClusterT* curClust;
	int curSumX, curSumY, dataCount;

	curClust = clusterFront;
	while (curClust != NULL)
	{
		curSumX = 0;
		curSumY = 0;
		dataCount = 0;

		curData = dataFront;
		while (curData != NULL)	
		{
			if (curData->ownCluster == curClust->clusterID)
			{
				curSumX += curData->x;
				curSumY += curData->y;
				dataCount++;
			}
			curData = curData->next;
		}

		curClust->prevX = curClust->x;
		curClust->prevY = curClust->y;
		curClust->x = curSumX / dataCount;	
		curClust->y = curSumY / dataCount;
		curClust = curClust->next;
	}
}


//PRINT
void PrintRound(int round)
{
	cout << endl << endl << "+----Round " << round << "----+" << endl;
	cout << endl << " [ID - OWN DATA]" << endl << endl;
	PrintOwnData();
	cout << endl;
}

void PrintOwnData()
{
	ClusterT* current;

	current = clusterFront;
	while (current != NULL)	
	{
		cout << "    [" << current->clusterID << " - " << current->dataCount << "] " << endl;
		current = current->next;
	}
}


//INIT
void InitClusters()
{
	ClusterT* rear=NULL, * newC;
	int quant;

	cout << " Set cluster quantity" << endl << " > ";
	cin >> quant;

	for (int i = 0; i < quant; i++)	
	{
		newC = new ClusterT;
		newC->next = NULL;
		newC->x = rand() % MAX + 1;
		newC->y = rand() % MAX + 1;
		newC->prevX = 0;
		newC->prevY = 0;
		newC->clusterID = i;

		if (clusterFront == NULL)
			clusterFront = newC;
		else
			rear->next = newC;
		rear = newC;
	}

	cout << " Clusters succesfully initialized!" << endl;
	system("pause");
	system("cls");
}

void InitDataPoints()
{
	DataPointsT* rear=NULL, * newC;
	int quant;

	cout << " Set Data Points quantity" << endl << " > ";
	cin >> quant;

	for (int i = 0; i < quant; i++)	
	{
		newC = new DataPointsT;
		newC->next = NULL;
		newC->x = rand() % MAX + 1;
		newC->y = rand() % MAX + 1;
		newC->ownCluster = -1;

		if (dataFront == NULL)
			dataFront = newC;
		else
			rear->next = newC;
		rear = newC;
	}

	cout << " Data Points succesfully initialized!" << endl << endl;
}


//DRAWING
void DrawData()
{
	DataPointsT* current;
	int rad = 3;

	SetColor(255, 255, 255);
	current = dataFront;
	while (current != NULL)
	{
		Circle(current->x, current->y, rad);
		current = current->next;
	}
}

void DrawCluster()
{
	ClusterT* current;
	int rad = 6;

	SetColor(0, 255, 0);
	current = clusterFront;
	while (current != NULL)	
	{
		Circle(current->x, current->y, rad);
		current->dataCount = 0;
		current = current->next;
	}
}

void DrawConnections(DataPointsT* data)
{
	ClusterT* cluster;
	cluster = clusterFront;

	while (cluster->clusterID != data->ownCluster)	
		cluster = cluster->next;

	cluster->dataCount++;
	
	SetColor(0, 255, 255);
	Line(data->x, data->y, cluster->x, cluster->y);
}


//OTHERS
bool ClusterComplete()
{
	ClusterT* curClust;

	curClust = clusterFront;
	while (curClust != NULL)	//se non ho spostato nessun cluster nell'ultimo ciclo, ho finito
	{
		if ((curClust->prevX != curClust->x) || (curClust->prevY != curClust->y))
			return false;
		curClust = curClust->next;
	}

	return true;
}

int Distance(int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
		return abs(y1 - y2);
	else if (y1 == y2)
		return abs(x1 - x2);
	else
		return sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
}
