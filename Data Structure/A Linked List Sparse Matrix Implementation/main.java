/*

Author: Zhongyi Sun, Sunx0725
        Tianxue Hu, huxxx811
 */

class main{
  public static void main(String[] args){
      try{
      SparseIntMatrix mat1 = new SparseIntMatrix(1000,1000,"matrix1_data.txt");
      MatrixViewer.show(mat1);

      SparseIntMatrix mat2 = new SparseIntMatrix(1000,1000,"matrix2_data.txt");
      MatrixViewer.show(mat2);

      SparseIntMatrix mat2_noise = new SparseIntMatrix(1000,1000,"matrix2_noise.txt");
      MatrixViewer.show(mat2_noise);

      System.out.println(mat2.minus(mat2_noise));
      MatrixViewer.show(mat2);

      System.out.println(mat2.plus(mat2_noise));
      System.out.println(mat2.minus(mat2_noise));
      MatrixViewer.show(mat2);

      }
      catch(Exception e){
        System.out.println("Error Happened in opening file");
      }
  }
}
