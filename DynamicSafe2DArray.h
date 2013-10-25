//class IndexOutOfBoundsException {};

template <class T>
class DynamicSafe2DArray
{
	private:
   	T** data;
      int row, col;

   public:
		DynamicSafe2DArray(): data(0), row(0), col(0) {}
      DynamicSafe2DArray(int row, int col)
      {
      	this->row = row;
         this->col = col;
         data = new T*[row];
         for (int i=0; i<row; i++)
         {
         	*(data+i) = new T[col];
            /*for (int j=0; j<col; j++)
            	*(*(data+i)+j) = 0;*/
         }
      }

      DynamicSafe2DArray(const DynamicSafe2DArray& rhs)
      {
         row = rhs.row;
         col = rhs.col;

         data = new T*[row];
         for (int i=0; i<row; i++)
         {
         	*(data+i) = new T[col];
            memcpy(*(data+i),*(rhs.data+i), sizeof(T)*col);
         }
      }

      DynamicSafe2DArray& operator=(const DynamicSafe2DArray& rhs)
      {
      	if (this == &rhs)
         	return *this;

         for (int i=row-1; i>0; i++)
         	delete *(data+i);
			delete data;

         row = rhs.row;
         col = rhs.col;

         data = new T*[row];
         for (int i=0; i<row; i++)
         {
         	*(data+i) = new T[col];
            memcpy(*(data+i),*(rhs.data+i), sizeof(T)*col);
         }

         return *this;
      }

   	T& operator()(int rowIndex, int colIndex)
      {
      	if (rowIndex < 0 || colIndex < 0 || rowIndex > row-1 || colIndex > col-1)
         	throw IndexOutOfBoundsException();

         return *(*(data+rowIndex)+colIndex);
      }

      int getRow() {return row;}
      int getCol() {return col;}

      void resize(int r, int c)
      {
      	T** temp = new T*[row];
         for (int i=0; i<row; i++)
         {
         	*(temp+i) = new T[col];
            memcpy(*(temp+i),*(data+i), sizeof(T)*col);
         }

         for (int i=row-1; i>=0; i--)
         	delete[] *(data+i);
			delete[] data;

         data = new T*[r];
         for (int i=0; i<r; i++)
         	*(data+i) = new T[c];

         int lI = row;
         int lJ = col;
         if (r < row) lI = r;
         if (c < col) lJ = c;

         for (int i = 0; i<lI; i++)
         	memcpy(*(data+i),*(temp+i), sizeof(T)*lJ);

         for (int i=row-1; i>=0; i--)
         	delete[] *(temp+i);
			delete[] temp;

         int tRow = row;
         int tCol = col;

         row = r;
         col = c;

         /*for (int i=0; i<r; i++)
         {
         	for (int j=0; j<c; j++)
            {
            	if (i >= tRow || j >= tCol) { (*this)(i,j) = 0; }
            }
         }*/
      }

      ~DynamicSafe2DArray()
      {
      	if (data != 0)
         {
         	for (int i=row-1; i>=0; i--)
            {
            	if (*(data+i) != 0)
               	delete *(data+i);
               *(data+i) = 0;
            }
            delete data;
         }
         data = 0;
      }
};













