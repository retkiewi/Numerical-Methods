#include "aghmatrix.h"


// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(const std::vector<std::vector<T>>& mat) 
{
  matrix.resize(mat.size());
  for (unsigned i = 0; i < mat.size(); i++) 
  {
    matrix[i].resize(mat[i].size());
    for(unsigned j = 0; j < mat[i].size(); j++)
    {
      matrix[i][j] = mat[i][j];
    }
  }
  rows = matrix.size();
  cols = matrix[1].size();
}

// Parameter Constructor                                                                                                                                                      
template<typename T>
AGHMatrix<T>::AGHMatrix(unsigned _rows, unsigned _cols, const T& _initial) 
{
  matrix.resize(_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(_cols, _initial);
  }
  rows = _rows;
  cols = _cols;
}

// Copy Constructor                                                                                                                                                           
template<typename T>
AGHMatrix<T>::AGHMatrix(const AGHMatrix<T>& rhs) 
{
  matrix = rhs.matrix;
  rows = rhs.get_rows();
  cols = rhs.get_cols();
}

// Get the number of rows of the matrix                                                                                                                                       
template<typename T>
unsigned AGHMatrix<T>::get_rows() const 
{
  return this->rows;
}

// Get the number of columns of the matrix                                                                                                                                    
template<typename T>
unsigned AGHMatrix<T>::get_cols() const 
{
  return this->cols;
}

// Assignment Operator                                                                                                                                                        
template<typename T>
AGHMatrix<T>& AGHMatrix<T>::operator=(const AGHMatrix<T>& rhs) 
{
  if (&rhs == this)
    return *this;

  unsigned new_rows = rhs.get_rows();
  unsigned new_cols = rhs.get_cols();

  matrix.resize(new_rows);
  for (unsigned i=0; i<matrix.size(); i++) 
  {
    matrix[i].resize(new_cols);
  }

  for (unsigned i=0; i<new_rows; i++) 
  {
    for (unsigned j=0; j<new_cols; j++) 
    {
      matrix[i][j] = rhs(i, j);
    }
  }
  rows = new_rows;
  cols = new_cols;

  return *this;
}

// Access the individual elements                                                                                                                                             
template<typename T>
T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) 
{
  return this->matrix[row][col];
}

// Access the individual elements (const)                                                                                                                                     
template<typename T>
const T& AGHMatrix<T>::operator()(const unsigned& row, const unsigned& col) const 
{
  return this->matrix[row][col];
}

// Addition of two matrices                                                                                                                                                   
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator+(const AGHMatrix<T>& rhs) 
{
  // Task 1 - implement addition of two matrices
}

// Left multiplication of this matrix and another                                                                                                                              
template<typename T>
AGHMatrix<T> AGHMatrix<T>::operator*(const AGHMatrix<T>& rhs) 
{
  // Task 1 - implement multiplication of two matrices
}

// Printing matrix                                                                                                                        
template<typename T>
void operator<<(std::ostream& stream, const AGHMatrix<T>& matrix) 
{
  for (int i=0; i<matrix.get_rows(); i++) 
  { 
    for (int j=0; j<matrix.get_cols(); j++) 
    {
        stream << matrix(i,j) << ", ";
    }
    stream << std::endl;
  }
    stream << std::endl;
}

template<typename T>
bool AGHMatrix<T>::is_symmetric(){
    if(this->get_rows()!=this->get_cols()){
        return false;
    }
    
    int rows = this->get_rows();
    int cols = this->get_cols();
    
    for(int i = rows; i>=0; i--){
        for(int j=0; j<i; j++){
            if(!(this->matrix[rows-i][j]!=this->matrix[j][rows-i])){
                return false;
            }
        }
    }
    
    return true;
}

template<typename T>
AGHMatrix<T> AGHMatrix<T>::get_minor(int col, int row){
    int rows = this->get_rows()-1;
    int cols = this->get_cols()-1;
    
    AGHMatrix<T> matrix_minor (rows, cols, 0);
    
    int r=0;
    int c=0;
    for(int i = 0; i<rows; i++){
        if(i!=row){
            for(int j = 0; j<cols; j++){
                if(j!=col){
                    matrix_minor.matrix[r][c]=this->matrix[i][j];
                    c++;
                }
            }
            r++;
        }
    }
    
    return matrix_minor;
}


template<typename T>
T AGHMatrix<T>::get_determinant(){
    if((this->get_rows()!=this->get_cols()||this->get_rows()<1)){
        std::cout<<"Invalid matrix shape.";
        return 1;
    }
    if(this->get_rows()==1){
        return this->matrix[0][0];
    }   
    
    if(this->get_rows()==2){
        return this->matrix[0][0]*this->matrix[1][1]-this->matrix[0][1]*this->matrix[1][0];
    }
    
    T result = 0;
    int rows = this->get_rows();
    int cols = this->get_cols();
    
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            AGHMatrix<T> minor = get_minor(i, j);
            result += minor.get_determinant()*(pow(-1, i+j));
        }
    }
    
    return result;
}

template<typename T>
void AGHMatrix<T>::transpose(){
    int rows = this->get_rows();
    int cols = this->get_cols();
    
    AGHMatrix<T> transposed (cols, rows, 0);
    
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            transposed.matrix[j][i]=this->matrix[i][j];
        }
    }
    
    this = transposed;
}