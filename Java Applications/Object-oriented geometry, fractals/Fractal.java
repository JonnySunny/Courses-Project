/*
Zhongyi Sun
5320262
*/
import java.awt.*;
public class Fractal {
    Canvas drawing = new Canvas(800,800);

    int times = 7; //using 'times' to control how many layers you want, and the original shape is the first layer

    //Implement TriangleFractal
    public double TriangleFractal(Triangle newtriangle,int counter){

        //get basic information for this triangle
        double h = newtriangle.getHeight();
        double x = newtriangle.getXPos();
        double y = newtriangle.getYPos();
        double w = newtriangle.getWidth();
        double area = newtriangle.calculateArea();

        //change color and draw
        Color co = Color.BLUE;
        if((counter) % 3 ==0){
            co = Color.BLUE;
        }
        else if((counter-1) % 3 ==0){
            co = Color.GREEN;
        }
        else if((counter-2) % 3 == 0){
            co = Color.RED;
        }
        newtriangle.setColor(co);
        drawing.drawShape(newtriangle);

        //Given recursive call to calculate the total area
        if (counter+1 < times ) {

            Triangle trione = new Triangle(x - w / 2, y, w / 2, h / 2);
            area+=TriangleFractal(trione,counter + 1);

            Triangle tritwo = new Triangle(x +w, y, w / 2, h / 2);
            area+=TriangleFractal(tritwo,counter + 1);

            Triangle trithree = new Triangle(x + w / 2 - w / 4, y- h, w / 2, h / 2);
            area+=TriangleFractal(trithree,counter + 1);
        }
        return area;
    }

    //Implement CircleFractal
    public double CircleFractal(Circle newcircle, int counter){

        //get basic information of Circle
        double x = newcircle.getXPos();
        double y = newcircle.getYPos();
        double r = newcircle.getRadius();
        double area = newcircle.calculateArea();
        Color co = Color.BLUE;

        //change color and draw
        if((counter) % 3 ==0){
            co = Color.BLUE;
        }
        else if((counter-1) % 3 ==0){
            co = Color.GREEN;
        }
        else if((counter-2) % 3 == 0){
            co = Color.RED;
        }
        newcircle.setColor(co);
        drawing.drawShape(newcircle);

        //Given recursive call to calculate the total area
        if (counter+1 < times ) {
            Circle cirone = new Circle(x - r / 2 - r, y , r/2);
            area +=CircleFractal(cirone,counter + 1);

            Circle cirtwo = new Circle(x , y +r+r/2, r/2);
            area +=CircleFractal(cirtwo,counter + 1);

            Circle cirthree = new Circle(x + r / 2 + r, y , r/2);
            area +=CircleFractal(cirthree,counter + 1);

            Circle cirfour = new Circle(x, y -r-r/2, r/2);
            area +=CircleFractal(cirfour,counter + 1);
        }
        return area;
    }

    //Implement RectangleFractal
    public double RectangleFractal(Rectangle newrec, int counter){

        //get information for rectangle
        double h = newrec.getHeight();
        double x = newrec.getXPos();
        double y = newrec.getYPos();
        double w = newrec.getWidth();
        double area = newrec.calculateArea();

        //set color and draw the rectangle
        Color co = Color.BLUE;
        if((counter) % 3 ==0){
            co = Color.BLUE;
        }
        else if((counter-1) % 3 ==0){
            co = Color.GREEN;
        }
        else if((counter-2) % 3 == 0){
            co = Color.RED;
        }
        newrec.setColor(co);
        drawing.drawShape(newrec);

        //Given recursive call to calculate the total area
        if(counter+1 < times ) {
            Rectangle recone = new Rectangle(x - w / 2, y + h, w / 2, h / 2);
            area += RectangleFractal(recone, counter + 1);

            Rectangle rectwo = new Rectangle(x + w, y + h , w / 2, h / 2);
            area += RectangleFractal(rectwo, counter + 1);

            Rectangle recthree = new Rectangle(x - w / 2, y - h/2, w / 2, h / 2);
            area += RectangleFractal(recthree, counter + 1);

            Rectangle recfour = new Rectangle(x + w, y -h/2, w / 2, h / 2);
            area += RectangleFractal(recfour, counter + 1);
        }
        return area;
    }
}
