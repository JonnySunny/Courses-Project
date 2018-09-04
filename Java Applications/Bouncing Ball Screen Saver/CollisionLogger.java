/*
    Author: Zhongyi Sun; Tianxue Hu

    X500: sunx0725; huxx811


 */

public class CollisionLogger {
    /* add data members here */
    int[][] looger;
    int width,height, b_width;
    int max;
    public CollisionLogger(int screenWidth, int screenHeight, int bucketWidth) {
    	/* constructor code here */
    	width = screenWidth;
    	height = screenHeight;
    	b_width = bucketWidth;
    	looger = new int[bucketWidth][bucketWidth];
      max = 0;
    }

     /**
     * This method records the collision event between two balls. Specifically, in increments the bucket corresponding to
     * their x and y positions to reflect that a collision occurred in that bucket.
     */
    public void collide(Ball one, Ball two) {
    	/* update data members to reflect the collision event between ball "one" and ball "two" */
    	int collison_X = (int) ((one.getXPos()+two.getXPos())/2);
    	int collison_Y = (int) ((one.getYPos()+two.getYPos())/2);
      if(collison_X == 0 && collison_Y == 0){
          looger[0][0]++;
      }
      else if(collison_X == 0 && collison_Y != 0){
          int ac_Y = height/collison_Y;
          if(ac_Y>=0 && ac_Y < b_width){
              looger[0][ac_Y]++;
          }
      }
      else if(collison_X != 0 && collison_Y == 0){
          int ac_X = width/collison_X;
          if(ac_X>=0 && ac_X < b_width){
              looger[ac_X][0]++;
          }
      }
      else{
    	int ac_X = width/collison_X;
    	int ac_Y = height/collison_Y;
        if(ac_X>=0 && ac_Y>=0 && ac_X < b_width && ac_Y < b_width){
                looger[ac_X][ac_Y] = looger[ac_X][ac_Y] + 1;
          }
        }
      }


    /**
     * Returns the heat map scaled such that the bucket with the largest number of collisions has value 255,
     * and buckets without any collisions have value 0.
     */
    public int[][] getNormalizedHeatMap() {

      int[][] normalizedHeatMap; //NOTE-- these dimensions need to be updated properly!!
    	/* implement your code to produce a normalized heat map of type int[][] here */


        for(int i = 0; i<looger.length;i++){
            for(int j = 0; j<looger[i].length;j++){
                if(looger[i][j]>max){
                    max = looger[i][j];
                }
            }
        }
        double scale = 255.0/max;
        for(int i = 0; i<looger.length;i++){
            for(int j = 0; j<looger[i].length;j++){
                if(looger[i][j]==max){
                    looger[i][j] = 255;
                }
                else{
                    looger[i][j] += looger[i][j] * scale;
                }
            }
        }

        normalizedHeatMap = looger;

        return normalizedHeatMap;
    }
}
