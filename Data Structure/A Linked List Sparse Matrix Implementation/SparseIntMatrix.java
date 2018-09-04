/*

Author: Zhongyi Sun, Sunx0725
        Tianxue Hu, huxxx811

(a)For a square matrix of N x N elements with m non-zero elements, how much memory is required for the SparseIntMatrix
implementation? How much for a standard 2D array implementation?

The memory is required for the SparseIntMatrix is m*5
The memory is required for a standard 2D array is N*N*1

(b)For a square matrix, assume N=100,000 and m=1,000,000. Is the SparseIntMatrix implementation more space-efficient,
and if so, by how much? (i.e. was it worth all of the effort you just went through implementing it?)
For what value of m does the 2D array implementation become more space-efficient than the SparseIntMatrix implementation?

space for 2D array one is N*N = (10^5)*(10^5) = 10^10
space for sparse one is  m*5 = (10^6)*5

So SparseIntMatrix is more space-efficient, it can save (10^10-(10^6)*5) total.
(10^10)/5 = (10^9)*2
When the number of elements is (10^9)*2 for this square matrix 100,000*100,000, both of implementation are same on the space efficiency.
More than this number, the 2D array is more space-efficient; otherwise, the sparse one is better in space-efficient perspective.

 */

import java.io.File;
import java.util.Scanner;

public class SparseIntMatrix {

    private MatrixEntry[] rowArray, columnArray;

    /*
    * A constructor returns an instance of this class
    * @param numRows, numCols two integers representing the number of rows and columns in this matrix
    *
    * @returns an instance of this class
    */
    public SparseIntMatrix(int numRows, int numCols){
        rowArray = new MatrixEntry[numRows];
        columnArray = new MatrixEntry[numCols];

    }
    /*
    * A constructor returns an instance of this class
    * @param numRows, numCols, inputFile. First two integers representing the number of rows and columns in this matrix,
    *  and the as a string which is the filename you want to use
    *
    * @returns an instance of this class
    */
    public SparseIntMatrix(int numRows, int numCols, String inputFile){
        rowArray = new MatrixEntry[numRows];
        columnArray = new MatrixEntry[numCols];
        try{
            Scanner s;
            File f = new File(inputFile);
            s = new Scanner(f);
            while(s.hasNext()) {
                //according to the pattern in the file, split them by ',', then we get information for each entry
                String sentence = s.nextLine();
                String[] slist = sentence.split(",");
                Integer row = Integer.valueOf(slist[0]);
                Integer col = Integer.valueOf(slist[1]);
                Integer data = Integer.valueOf(slist[2]);
                setElement(row, col, data);
            }
      }
      catch(Exception e){
            System.out.println("Error Happened in opeing file");
      }

    }

    /*
    * Method that returns the element which you want get from the matrix
    * @param row, col Two integers representing the location information
    *
    * @returns an int element
    */
    public int getElement(int row, int col){
        //corresponding element (integer) if one exists or zero otherwise.
        if(row < 0 || row >= rowArray.length){
            return 0;
        }
        if(col < 0 || col >= columnArray.length){
            return 0;
        }
        else{
            MatrixEntry preRowTemp = findPreRowEntry(row,col);
            //set condition to avoid null pointer exception
            if(preRowTemp!=null && preRowTemp.getColumn()==col){
                return preRowTemp.getData();
            }
            else {
                return 0;
            }
        }
    }
    /*
    * Method that sets the new element into matrix
    * @param row, col, data. Three integers representing the information of one entry you want to set
    *
    * @returns a boolean to denote if set successfully or not
    */
    public boolean setElement(int row, int col, int data){
        //corresponding element (integer) if one exists or zero otherwise.
        //check if the row and col are valid for this matrix
        if(row < 0 || row >= rowArray.length) {
            return false;
        }
        else if (col < 0 || col >= columnArray.length) {
            return false;
        }
        else {
            //operate with rowArray, to traverse the column of this header, and add the new entry in to this link
            MatrixEntry preRowTemp = findPreRowEntry(row, col);
            //operate with columnArray, to traverse the row of this header, and add the new entry in to this link
            MatrixEntry preColTemp = findPreColEntry(row, col);
            MatrixEntry entry = new MatrixEntry(row,col,data);
            //connect the rest part if the entry is already there
            if(preRowTemp.getNextColumn()!=null){
              entry.setNextColumn(preRowTemp.getNextColumn());
            }
            if(preColTemp.getNextRow()!=null){
              entry.setNextRow(preColTemp.getNextRow());
            }
            preColTemp.setNextRow(entry);
            preRowTemp.setNextColumn(entry);
            return true;
        }
    }
    /*
    * Method that returns the previous entry in the row of this entry
    * @param row, col two integers to find the position
    *
    * @returns An reference to the MatrixEntry corresponding to the previous row
    */
    public MatrixEntry findPreRowEntry(int row, int col){
        if(rowArray[row] == null){
            rowArray[row] = new MatrixEntry(row,0,0);
        }
        MatrixEntry tempRow = rowArray[row];
        MatrixEntry preRowTemp = null;

        while(tempRow!=null && tempRow.getColumn()<=col) {
            preRowTemp = tempRow;
            tempRow = tempRow.getNextColumn();
        }
        return preRowTemp;
    }
    /*
    * Method that returns the previous entry in the row of this entry
    * @param row, col two integers to find the position
    *
    * @returns An reference to the MatrixEntry corresponding to the previous row
    */
    public MatrixEntry findPreColEntry(int row, int col){
        if(columnArray[col] == null){
            columnArray[col] = new MatrixEntry(0,col,0);
         }
        MatrixEntry tempCol = columnArray[col];
        MatrixEntry preColTemp = null;

        while(tempCol!=null && tempCol.getRow()<=row) {
            preColTemp = tempCol;
            tempCol = tempCol.getNextRow();
        }
        return preColTemp;
    }

    /*
    * Method that returns the number of columns in this matrix
    * @param null
    *
    * @returns An integer of this matrix's columns
    */
    public int getNumCols(){
        return columnArray.length;
    }
    /*
    * Method that returns the number of rows in this matrix
    * @param null
    *
    * @returns An integer of this matrix's rows
    */
    public int getNumRows(){
        return rowArray.length;
    }

    /*
    * Another sparse matrix to be added to the current one. This method should update the state of the current object
    * @param otherMat another SparseIntMatrix
    *
    * @returns a boolean to indicate if the addition is successful or not
    */
    public boolean plus(SparseIntMatrix otherMat){
        if(getNumRows() == otherMat.getNumRows() && getNumCols() == otherMat.getNumCols()){
            for(int i = 0; i < getNumRows(); i++){
                for(int j = 0; j<getNumCols();j++){
                  setElement(i,j,this.getElement(i,j)+otherMat.getElement(i,j));
                }
            }
            return true;
        }
        else{
            return false;
        }
    }

    /*
    * Another sparse matrix to be subtracted from the current one. This method should update the state of the current object
    * @param otherMat another SparseIntMatrix
    *
    * @returns a boolean to indicate if the subtraction is successful or not
    */
    public boolean minus(SparseIntMatrix otherMat){
        if(getNumRows() == otherMat.getNumRows() && getNumCols() == otherMat.getNumCols()){
            for(int i = 0; i < getNumRows(); i++){
                for(int j = 0; j<getNumCols();j++){
                    setElement(i,j,this.getElement(i,j)-otherMat.getElement(i,j));
                }
            }
            return true;
        }
        else{
            return false;
        }
      }
}
