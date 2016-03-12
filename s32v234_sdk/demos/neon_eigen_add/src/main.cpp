#include <Dense>

#include <stdint.h>
#include <cstdlib>
#include <stdio.h>

using namespace Eigen;
using namespace std;

int main()
{
	// C initialization
	int fieldM[4][4];

	int counter = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fieldM[i][j] = counter++;
		}
	}

	int fieldN[4][4];

	counter = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			fieldN[i][j] = counter++;
		}
	}

	int fieldK[4][4];

	// Eigen initialization
	Matrix4i m(4,4);

	counter = 0;
	for (int i = 0; i < m.rows(); i++)
	{
		for (int j = 0; j < m.cols(); j++)
		{
			m(i, j) = counter++;
		}
	}

	Matrix4i n(4, 4);

	counter = 0;
	for (int i = 0; i < n.rows(); i++)
	{
		for (int j = 0; j < n.cols(); j++)
		{
			n(i, j) = counter++;
		}
	}	
	
	Matrix4i k(4, 4);

	// Matrix addition
	// C version
 	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j ++)
		{
			fieldK[i][j] = fieldM[i][j] + fieldN[i][j];
		}
	}

	// Eigen mversion
	k = m + n;

	// Show result
	// C result
	printf(" \n C result \n");

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf(" %d ", fieldK[i][j]);
		}
	}

	// Eigen result
	printf(" \n Eigen result \n");
	for (int i = 0; i < k.rows(); i++)
	{
		for(int j = 0; j < k.cols(); j ++)
		{
			printf(" %i ", k(i,j));
		}
	}	

}

