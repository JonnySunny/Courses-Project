/*
Zhongyi Sun
5320262
*/
import java.awt.*;
public class Triangle {
    private double x,y,width,height;
    private Color color;
    /*
       Constructor
       x position of bottom left corner (double),
       y position of bottom left corner (double),
       width (double),
       height (double);
   */
    public Triangle(double initx, double inity, double initwidth, double initheight){
        x = initx;
        y = inity;
        width = initwidth;
        height = initheight;
    }
    //Attributes
     public double calculatePerimeter(){

        return 2*Math.sqrt((height*height) + ((width/2.0)*(width/2.0))) + width;
    }

    public double calculateArea(){

         return width*height*0.5;

    }

    //setter
    public void setColor(Color initcolor ){
        color = initcolor;
    }

    public void setPos(double initx, double inity){
        x = initx;
        y = inity;
    }

    public void setHeight(double initheight){
        height = initheight;
    }

    public void setWidth(double initwidth){
        width = initwidth;
    }


    //getter
    public Color getColor(){
        return color;
    }
    public double getXPos(){
        return x;
    }

    public double getYPos(){
        return y;
    }

    public double getHeight(){
        return height;
    }

    public double getWidth(){
        return width;
    }



}
