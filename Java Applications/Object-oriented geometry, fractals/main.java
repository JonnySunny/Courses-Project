/*
Zhongyi Sun
5320262
*/
import java.util.Scanner;

public class main {
    public static void main(String[] args) {



        System.out.println("Choose one shape to show its Fractal and then print out the total area: 't' for Triangle、'c' for Circle、'r' for Rectangle ");

        //initialize three different default shape
        Triangle newtri = new Triangle(400,400,50,50);
        Rectangle newrec = new Rectangle(400,400,100,50);
        Circle newcir = new Circle(400,400,50);

        //receive the input from users
        Scanner shape = new Scanner(System.in);
        String input = shape.next();

        //operate depends on the input
        if(input.toLowerCase().equals("c")){
            Fractal facc = new Fractal();
            System.out.println("Circle area total is : "+facc.CircleFractal(newcir,0));
        }
        if (input.toLowerCase().equals("t")){
            Fractal fact = new Fractal();
            System.out.println("Triangle area total is : "+fact.TriangleFractal(newtri,0));
        }
        if (input.toLowerCase().equals("r")){
            Fractal facr = new Fractal();
            System.out.println("Rectangle area total is : "+facr.RectangleFractal(newrec,0));
        }
        //if no pattern matches, print this and exit
        else{
            System.out.println("Input format is not correct, Please re-run. ");
        }

    }
}
