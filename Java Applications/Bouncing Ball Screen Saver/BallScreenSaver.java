/*
    Author: Zhongyi Sun
    ID: 5320262
    X500: sunx0725
 */
import java.awt.*;
import java.awt.event.KeyEvent;
import java.io.IOException;

public class BallScreenSaver extends AnimationFrame {
    /*

     Many codes are from BouncingBall class.

     */
    Ball[] balllist;
    private int ballSize=18;
    public final int BORDER=30;
    private final int START_SPEED=300;

    private CollisionLogger collisionLogger;
    private static final int COLLISION_BUCKET_WIDTH = 20;
    private int saveCounter=0;

    @Override
    public void action() {
        //update

        for(int i = 0; i< balllist.length; i++){
            balllist[i].updatePosition(getFPS());

        }
        //handle for balls bounce off walls
        for(int i = 0; i<balllist.length;i++) {
          /*
            changed
          */
            if (balllist[i].getXPos() < BORDER || balllist[i].getXPos() + balllist[i].getRadius() > getHeight() - BORDER) {
                double newXvel = -balllist[i].getSpeedX();
                balllist[i].setSpeedX(newXvel);
            }

            if(balllist[i].getYPos() < BORDER ||  balllist[i].getYPos() + balllist[i].getRadius() > getWidth() - BORDER ){
                double newYvel = -balllist[i].getSpeedY();
                balllist[i].setSpeedY(newYvel);
            }


        }
        //handle for balls collide
        for(int i = 0; i<balllist.length;i++){
            for(int j = i+1; j<balllist.length;j++){
                if(balllist[j].intersect(balllist[i])){
                    balllist[j].collide(balllist[i]);
                    balllist[j].setColor(Color.RED);
                    balllist[i].setColor(Color.RED);
                    collisionLogger.collide(balllist[j],balllist[i]);
                }
            }
        }



    }

    public double randdouble(double min, double max){
        //a utility method to get a random double between min and max.
        return (Math.random()*(max-min)+min);
    }

    @Override
    public void draw(Graphics g) {

        g.setColor(Color.black);
        g.fillRect(0,0, getWidth(), getHeight());
        g.setColor( Color.WHITE);
        g.drawRect(BORDER,BORDER,getWidth()-BORDER*2,getHeight()-BORDER*2);

        for(int i = 0; i< balllist.length;i++) {
            g.setColor(balllist[i].getColor());
            g.fillOval((int) balllist[i].getXPos(), (int) balllist[i].getYPos(), (int)balllist[i].getRadius(),(int)balllist[i].getRadius());
        }
    }

    @Override
    protected void processKeyEvent(KeyEvent e) {

        int keyCode = e.getKeyCode();
        /* This captures the user pressing the "p" key and prints out the current collisionLog to an image.
        	You can use this directly in your implementation. Add other cases to the if/else statement to
        	handle other key events.
        */
        if (e.getID() == KeyEvent.KEY_PRESSED && keyCode == KeyEvent.VK_P) {

            EasyBufferedImage image = EasyBufferedImage.createImage(collisionLogger.getNormalizedHeatMap());
            try {
                image.save("heatmap"+saveCounter+".png", EasyBufferedImage.PNG);
                saveCounter++;
            } catch (IOException exc) {
                exc.printStackTrace();
                System.exit(1);
            }
        }
         /* This captures the user pressing the "<-" key and decrease velocity 10%.
        	You can use this directly in your implementation. Add other cases to the if/else statement to
        	handle other key events.
        */
        if (e.getID() == KeyEvent.KEY_PRESSED && keyCode == KeyEvent.VK_LEFT) {

                for(int i = 0; i< balllist.length;i++){
                    double newxvel = balllist[i].getSpeedX() * 0.9;
                    double newyvel = balllist[i].getSpeedY() * 0.9;
                    balllist[i].setSpeedX(newxvel);
                    balllist[i].setSpeedY(newyvel);
                }

        }
         /* This captures the user pressing the "->" key and increase velocity 10 %.
        	You can use this directly in your implementation. Add other cases to the if/else statement to
        	handle other key events.
        */
        if (e.getID() == KeyEvent.KEY_PRESSED && keyCode == KeyEvent.VK_RIGHT) {

                for(int i = 0; i< balllist.length;i++){
                    double newxvel = balllist[i].getSpeedX() * 1.1;
                    double newyvel = balllist[i].getSpeedY() * 1.1;
                    balllist[i].setSpeedX(newxvel);
                    balllist[i].setSpeedY(newyvel);
                }
            }

    }


    public BallScreenSaver(int inwidth, int inheight, String inname, int innumOfballs){

        super(inwidth,inheight,inname);
        double dir=randdouble(0,Math.PI*2);


        balllist  = new Ball[innumOfballs];
        for(int i = 0; i< balllist.length; i++){

            double xpos =  randdouble(BORDER,getWidth()-BORDER);
            double ypos =  randdouble(BORDER,getHeight()-BORDER);

            balllist[i] = new Ball(xpos,ypos,ballSize,Color.GREEN);

            double xvel =  Math.cos(dir) * START_SPEED;
            double yvel =  Math.sin(dir) * START_SPEED;
            balllist[i].setSpeedX(xvel);
            balllist[i].setSpeedY(yvel);

        }
        setFPS(20);
        collisionLogger = new CollisionLogger(this.getWidth(),this.getHeight(), COLLISION_BUCKET_WIDTH);

    }

}
