/*
Author: Zhongyi Sun, Sunx0725
        Tianxue Hu, huxxx811
 */

public class MatrixEntry {

    private int r,c,data;
    private MatrixEntry nextcol, nextrow;

    /*
    * A constructor which will return a instance of this class
    * @param the row, column, and data associated with this matrix element
    *
    * @returns  an instance of the MatrixEntry class
    */
    public MatrixEntry(int row, int col, int data){
        r=row;
        c=col;
        this.data=data;
    }

    /*
    * Method that returns the column
    * @param none
    *
    * @returns an integer corresponding to the column of this entry
    */
    public int getColumn(){ return c; }

    /*
    * Method that sets column of this entry
    * @param col an integer corresponding to the column of this entry
    *
    * @returns none
    */
    public void setColumn(int col){
        c =  col;
    }
    /*
    /*
    * Method that returns the row
    * @param none
    *
    * @returns an integer corresponding to the row of this entry
    */
    public int getRow(){ return r; }

    /*
    * Method that sets row of this entry
    * @param row an integer corresponding to the row of this entry
    *
    * @returns none
    */
    public void setRow(int row){ r = row;}

    /*
    * Method that returns the data of this entry
    * @param none
    *
    * @returns a data corresponding to this entry
    */
    public int getData(){
        return data;
    }

    /*
    * Method that sets data in this entry
    * @param data an integer corresponding to the data of this entry
    *
    * @returns none
    */
    public void setData(int data){
        this.data = data;
    }

    /*
    * Method that returns  a reference to the next matrix element in the current element’s column
    * @param none
    *
    * @returns a reference to next column of this entry
    */
    public MatrixEntry getNextColumn(){
        return nextcol;
    }

    /*
    * Method that sets a reference to the next element in this element's column
    * @param el MatrixEntry which references to next column entry of this element
    *
    * @returns none
    */
    public void setNextColumn(MatrixEntry el){
        nextcol = el;
    }
    /*
    * Method that returns  a reference to the next matrix element in the current element’s row
    * @param none
    *
    * @returns a reference to next row of this entry
    */
    public MatrixEntry getNextRow() { return nextrow; }

    /*
    * Method that sets a reference to the next element in this row's column
    * @param el MatrixEntry which references to next row entry of this element
    *
    * @returns none
    */
    public void setNextRow(MatrixEntry el){
        nextrow = el;
    }


}
