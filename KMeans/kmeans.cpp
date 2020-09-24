#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>

#define MAX 600

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
	int clusterID;
	ClusterT* next;
};

DataPointsT* dataFront = NULL;
ClusterT* clusterFront = NULL;

void InitDataPoints();
void InitClusters();
void SelectCluster();
int Distance(int x1, int y1, int x2, int y2);
void DrawCluster();
void CenterCluster();
bool ClusterComplete();


int main()
{
	srand(time(NULL));
	InitDataPoints();
	InitClusters();

	do
	{
		system("cls");
		DrawCluster();
		SelectCluster();
		CenterCluster();
		system("pause");
	} while (!ClusterComplete());

	cout << " Clustering Complete!" << endl;
	system("pause");
	return 0;
}

void InitClusters()
{
	ClusterT* rear=NULL, *newC;
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

	cout << endl << " Clusters succesfully initialized!" << endl;
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

	cout << endl << " Data Points succesfully initialized!" << endl;
	system("pause");
	system("cls");
}

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

		curData = curData->next;
	}
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

void DrawCluster()
{
	DataPointsT* curData;
	ClusterT* curClust;
	
	curClust = clusterFront;
	while (curClust != NULL)
	{
		cout << " Clusters " << endl;
		cout << "{" << curClust->x << ";" << curClust->y << "-" << curClust->clusterID << "} " << endl;
		curData = dataFront;
		while (curData != NULL)
		{
			if (curData->ownCluster == curClust->clusterID)
			{
				cout << " [" << curData->x << ";" << curData->y << "]";
			}
			curData = curData->next;
		}
		cout << endl << endl;
		curClust = curClust->next;
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

bool ClusterComplete()
{
	ClusterT* curClust;

	curClust = clusterFront;
	while (curClust != NULL)	
	{
		if ((curClust->prevX != curClust->x) || (curClust->prevY != curClust->y))
			return false;
		curClust = curClust->next;
	}

	return true;
}
