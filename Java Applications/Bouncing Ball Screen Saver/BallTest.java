import junit.framework.TestCase;

import java.awt.*;

public class BallTest extends TestCase {

	static double alpha = 0.000001;
	Ball b = new Ball(50, 50, 10, Color.BLUE);

	public void testSetSpeedX() {
		b.setSpeedX(100);
		assertEquals(100.0, b.getSpeedX());
		b.setSpeedX(0 - Math.PI);
		assertEquals(-Math.PI, b.getSpeedX());
	}

	public void testSetSpeedY() {
		b.setSpeedY(100);
		assertEquals(100.0, b.getSpeedY(), alpha);
		b.setSpeedY(-100);
		assertEquals(-100.0, b.getSpeedY(), alpha);
	}

	public void testIntersect() {
		Ball b2 = new Ball(100, 50, 10, Color.BLUE);
		assertFalse(b.intersect(b2));
		b2.setRadius(41);
		assertTrue(b.intersect(b2));
		b2.setRadius(39);
		assertFalse(b.intersect(b2));
	}

	public void testCollide() {
		// simple 1-d collisions:
		// First in x dimension
		b = new Ball(50, 50, 10, Color.BLUE);
		b.setSpeedX(10);
		b.setSpeedY(0);
		Ball b2 = new Ball(100, 50, 41.0, Color.BLUE);
		b2.setSpeedX(-10);
		b2.setSpeedY(0);
		b.collide(b2);
		assertEquals(-10, b.getSpeedX(), alpha);
		assertEquals(0, b.getSpeedY(), alpha);

		// in y dimension
		b2.setPos(50, 100);
		b.setSpeedX(0);
		b.setSpeedY(10);
		b2.setSpeedX(0);
		b2.setSpeedY(-10);
		b.collide(b2);
		assertEquals(0, b.getSpeedX(), alpha);
		assertEquals(-10, b.getSpeedY(), alpha);

		// in y dimension with non-overlap
		b2.setRadius(39.0);
		b.setSpeedX(0);
		b.setSpeedY(10);
		b2.setSpeedX(0);
		b2.setSpeedY(-10);
		b.collide(b2);
		assertEquals(10.0, b.getSpeedY(), alpha);
		assertEquals(-10.0, b2.getSpeedY(), alpha);

		// in 2-dimensions
		b.setPos(397.0, 536.0);
		b.setSpeedX(99.9);
		b.setSpeedY(3.865);
		b.setRadius(10.0);
		b2.setPos(401.567, 524.256);
		b2.setRadius(10.0);
		b2.setSpeedX(96.564);
		b2.setSpeedY(25.9876);
		b.collide(b2);

		assertEquals(92.3, b.getSpeedX(), 1);
		assertEquals(24.4, b.getSpeedY(), 1);
		assertEquals(104.2, b2.getSpeedX(), 1);
		assertEquals(5.45, b2.getSpeedY(), 1);
	}

}
