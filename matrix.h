/** Matrix ADT by tlehman, 2008
 *	
 *	This is a data type meant to be used in 
 *	Linear Algebra calculations.
 *		The Matrix ADT can assume any size ( ROWSxCOLS )
 *		Matrices can be 
 *			1. Added
 *			2. Multiplied
 *			3. Transposed 
 *			4. Inverted		// NOT YET DEFINED
 *
 *	Matrices can be used to solve linear systems or to 
 *	perform linear transformations such as rotations and
 *	projections.
 * */

class matrix
{
	public:
		matrix(int rows, int cols);
		matrix(char filename[]);
		~matrix();

		void show();		// display the matrix
		void identity();    // sets a square matrix to the identity
		void zero();		// set to zero matrix
		int set_cell(int row, int col, float value, bool reset);
		float get_cell(int row, int col);
		int get_rows();
		int get_cols();
		float det();		// compute and return the determinant
							// ONLY DEFINED FOR 2x2 Matrices, generalize to NxN
		void transpose();

		int load(char filename[]);
		bool is_square();

		matrix operator+(matrix& M);
		matrix operator*(matrix& M);
		bool operator==(matrix& M);
	private:
		float **m;			// grid where matrix values reside
		int ROWS;
		int COLS;
};

