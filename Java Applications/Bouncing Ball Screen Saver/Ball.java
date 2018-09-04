/*
    Author: Zhongyi Sun; Tianxue Hu

    X500: sunx0725; huxx811


 */

import java.awt.*;
public class Ball extends Circle {

    private double xvel,yvel;

    public Ball(double initx, double inity, double initr, Color initcolor){
        super(initx,inity,initr);
        super.setColor(initcolor);


    }
    public void setSpeedX(double initx){
        xvel = initx;
    }
    public void setSpeedY(double inity){
        yvel = inity;
    }
    public double getSpeedX(){
        return xvel;
    }
    public double getSpeedY(){
        return yvel;
    }


    public void updatePosition(double fpstime){
        double recentposX  = super.getXPos() + getSpeedX()/fpstime;
        double recentposY  = super.getYPos() + getSpeedY()/fpstime;
        super.setPos(recentposX, recentposY);

    }

    public boolean intersect(Ball ball){
        //using the distance to check if they are intersecting
        double distance = Math.sqrt((Math.pow(super.getXPos()-ball.getXPos(),2.0))+Math.pow(super.getYPos()-ball.getYPos(),2.0));
        if(distance <= (super.getRadius()+ball.getRadius())){
            return true;
        }
        else{
            return false;
        }
    }
    //this is i, the ball passed in is j
    public void collide(Ball ball){
        //following the guideline in the document.
        double distance = Math.sqrt((Math.pow(super.getXPos()-ball.getXPos(),2.0))+Math.pow(super.getYPos()-ball.getYPos(),2.0));

        double deltaX=  (super.getXPos() - ball.getXPos()) / distance ;

        double deltaY = (super.getYPos() - ball.getYPos()) / distance ;

        if(intersect(ball)){

            double tempxvel = (getSpeedX()*deltaX+getSpeedY()*deltaY) * deltaX - (-ball.getSpeedX()*deltaY+ball.getSpeedY()*deltaX) * deltaY;
            double tempyvel = (getSpeedX()*deltaX+getSpeedY()*deltaY) * deltaY + (-ball.getSpeedX()*deltaY+ball.getSpeedY()*deltaX) * deltaX;


            double speedx =  (ball.getSpeedX()*deltaX + ball.getSpeedY()*deltaY) * deltaX -  (-getSpeedX()*deltaY+getSpeedY()*deltaX) * deltaY ;
            double speedy =  (ball.getSpeedX()*deltaX + ball.getSpeedY()*deltaY) * deltaY +  (-getSpeedX()*deltaY+getSpeedY()*deltaX) * deltaX ;


            setSpeedX(speedx);
            setSpeedY(speedy);

            ball.setSpeedX(tempxvel);
            ball.setSpeedY(tempyvel);

        }
    }



}
