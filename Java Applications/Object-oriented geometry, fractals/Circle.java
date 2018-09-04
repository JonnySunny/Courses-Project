/*
Zhongyi Sun
5320262
*/
import java.awt.*;

public class Circle {

    private double x, y, r;
    private Color color;
    /*
        Constructor
        x position (double), y position (double), radius (double)

     */
    public Circle(double initx, double inity, double initradius) {
        x = initx;
        y = inity;
        r = initradius;
    }

    //Attributes
    public double calculatePerimeter() {

        return 2 * Math.PI * r;
    }

    public double calculateArea() {

        return Math.PI * r * r;
    }

    //setter
    public void setColor(Color initcolor) {
        color = initcolor;
    }

    public void setPos(double initx, double inity) {
        x = initx;
        y = inity;
    }

    public void setRadius(double initradius) {
        r = initradius;
    }

    //getter
    public Color getColor() {
        return color;
    }

    public double getXPos() {
        return x;
    }

    public double getYPos() {
        return y;
    }

    public double getRadius() {
        return r;
    }



}
