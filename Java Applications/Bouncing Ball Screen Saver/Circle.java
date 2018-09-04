 
import java.awt.*;
public class Circle {
	double x,y,r;
	Color color;

	public Circle(double x, double y, double r){
		this.x=x;
		this.y=y;
		this.r=r;
	}
	public double calculatePerimeter(){
		return 2*Math.PI*r;
	}
	public double calculateArea(){
		return Math.PI*r*r;		
	}
	public void setColor(Color c){
		color=c;
	}
	public void setPos(double x,double y){
		this.x=x;
		this.y=y;
	}
	public void setRadius(double r){
		this.r=r;
	}
	public Color getColor(){
		return color;
	}
	public double getXPos(){
		return x;
	}
	public double getYPos(){
		return y;
	}
	public double getRadius(){
		return r;
	}
}


