#include <iostream>
#include <fstream>
#include "matrix.h"
using namespace std;

matrix::matrix(int rows, int cols)
{
	ROWS = rows;
	COLS = cols;
	m = new float*[ROWS];				// allocate the rows

	for(int i = 0; i < ROWS; ++i)
	{
		m[i] = new float[COLS];		// allocate the columns
	}

	zero();							// set to zero matrix
}

matrix::~matrix()
{
	for(int r = 0; r < ROWS; ++r)	
	{
		delete [] m[r];
	}
	delete [] m;
}

void matrix::show()
{
	char tl = '[';
	char tr = ']';
	char bl = '[';
	char br = ']';

	for(int r = 0; r < ROWS; ++r)
	{
		for(int c = 0; c < COLS; ++c)
		{
			if(r == 0 && c == 0)
				cout << tl;
			else if(r == ROWS-1 && c == 0)
				cout << bl;

			cout << m[r][c] << " ";

			if(r == ROWS-1 && c == COLS-1)
				cout << br;
			else if(r == 0 && c == COLS-1)
				cout << tr;
		}
		cout << endl;
	}

}

void matrix::identity()
{
	if(is_square())
	{
		for(int r = 0; r < ROWS; ++r)
		{
			m[r][r] = 1;
		}
	}
	else
	{
		cout << " not a square matrix!" << endl;
	}
}

void matrix::zero()
{
	// populate the matrix with zeros
	for(int r = 0; r < ROWS; ++r)
	{
		for(int c = 0; c < COLS; ++c)
		{
			m[r][c] = 0;
		}
	}
}

/**  set_cell sets value to m[row][col], the following
 *   are set_cell's error codes:
 *   	0. No error
 *   	1. Out of bounds error
 *
 *   if reset is true, then wipe the cell value, 
 *   else add to the cell value
 */
int matrix::set_cell(int row, int col, float value, bool reset)
{
	int error;

	if((row >= 0 && row < ROWS) && (col >=0 && col < COLS))
	{
		if(reset)
			m[row][col] = value;
		else
			m[row][col] += value;
		error = 0;
	}
	else
	{
		error = 1;		// Out of bounds error
	}

	return error;
}

/** get_cell gets the value of m[row][col]
 */
float matrix::get_cell(int row, int col)
{
	float value;
	if((row >= 0 && row < ROWS) && (col >= 0 && col < COLS))
	{
		value = m[row][col];
	}
	else
	{
		cout << "error 1 : out of bounds of matrix" << endl;
		value = -1;
	}
	return value;
}

int matrix::get_rows()
{
	return ROWS;
}

int matrix::get_cols()
{
	return COLS;
}

/** det() computes and returns the determinant of this matrix
 *  the function returns 0 if matrix is not square, it also
 *  notifies the user through the common out
 */
float matrix::det()
{
	float retval = 0;

	if(ROWS == COLS)
	{
		if(ROWS == 2)	// DEV ONLY
		{
			retval = (m[0][0] * m[1][1]) - (m[0][1] * m[1][0]);
		}
		else
			cout << "not a 2x2 matrix" << endl;
	}
	else
	{
		cout << "not a square matrix" << endl;
	}
	return retval;
}

void matrix::transpose()
{
	for(int c = 0; c < COLS; ++c)
	{
		for(int r = 0; r < ROWS; ++r)
		{
			cout << m[r][c] << " ";
		}
		cout << endl;
	}
}

/** load(char[]) takes a filename as a parameter
 *  and loads the file into memory, after which it
 *  instantiates a matrix from the file input buffer
 */
int matrix::load(char filename[])
{
	int retval;
	int len = strlen(filename);
	char current;
	ifstream fin;

	fin.open(filename);

	// dev purposes only, output the contents of file
	do
	{
		current = fin.get();	
		cout << current;

	} while(!fin.eof());
	
	fin.close();

	return retval;
}

bool matrix::is_square()
{
	return ROWS == COLS;
}

matrix matrix::operator+(matrix& M)
{
	matrix C(ROWS, COLS);	// new matrix
	float sum;

	if(ROWS == M.get_rows() && COLS == M.get_cols())
	{
		for(int r = 0; r < ROWS; ++r)
		{
			for(int c = 0; c < COLS; ++c)
			{
				// set C[r][c] = m[r][c] + M[r][c]
				sum = m[r][c];
				sum += M.get_cell(r, c);
				C.set_cell(r, c, sum, true);
			}
		}
	}
	else
	{
		cout << "error 1 : matrices are not of equal size" << endl;
	}
	return C;
}

matrix matrix::operator*(matrix& M)
{
	matrix C(ROWS, M.get_cols());
	int product;

	if(COLS == M.get_rows())
	{
		for(int i = 0; i < COLS; ++i)
		{
			for(int r = 0; r < ROWS; ++r)
			{
				for(int c = 0; c < M.get_cols(); ++c)
				{
					product = m[r][i];
					product *= M.get_cell(i, c);
					C.set_cell(r, c, product, false);
				}
			}
		}
	}
	else
	{
		cout << "error 1 : left matrix columns do not match right matrix rows" << endl;
	}
	return C;
}

bool matrix::operator==(matrix& M)
{
	bool equal = true;
	if(ROWS != M.get_rows() || COLS != M.get_cols())
	{
		equal = false;
	}
	else
	{
		for(int r = 0; r < ROWS; ++r)
		{
			for(int c = 0; c < COLS; ++c)
			{
				if(m[r][c] != M.get_cell(r, c))
					equal = false;
			}
		}
	}

	return equal;
}
