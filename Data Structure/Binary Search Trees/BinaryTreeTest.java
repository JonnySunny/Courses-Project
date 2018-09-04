import org.junit.Test;
import java.util.Arrays;
import static org.junit.Assert.*;
import static org.junit.Assert.assertTrue;

public class BinaryTreeTest {
    /*
          40
      20      60
    10  30  50  70
     */
    BinaryTree<Integer, String> p1Tree = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(10, "ten"), new Node<Integer, String>(30, "thirty")),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy"))));

    BinaryTree<Integer, String> p1Tree1 = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(10, "ten", new Node<Integer, String>(5, "five"), null), new Node<Integer, String>(30, "thirty")),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy"))));

    BinaryTree<Integer, String> p1Tree2 = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(10, "ten"), new Node<Integer, String>(30, "thirty")),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy", null, new Node<Integer, String>(75, "seventy-five")))));

    BinaryTree<Integer, String> p1Tree3 = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(10, "ten"), new Node<Integer, String>(30, "thirty", new Node<Integer, String>(25, "twenty-five"), null)),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy"))));

    BinaryTree<Integer, String> p1Tree4 = new BinaryTree<Integer, String>(new Node<Integer, String>(55, "fifty-five"));

    BinaryTree<Integer, String> p1Tree5 = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(10, "ten"), new Node<Integer, String>(30, "thirty")),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "updated"), new Node<Integer, String>(70, "seventy"))));

    @Test
    public void test_add_1() throws Exception {
        //checks for the case where 5 is added
        p1Tree.add(5, "five");
        System.out.println(p1Tree.toString());
        assertTrue(p1Tree.getRoot().equals(p1Tree1.getRoot()));
    }

    @Test
    public void test_add_2() throws Exception {
        //checks for the case where 75 is added
        p1Tree.add(75, "seventy-five");
        System.out.println(p1Tree.toString());
        assertTrue(p1Tree.getRoot().equals(p1Tree2.getRoot()));
    }

    @Test
    public void test_add_3() throws Exception {
        //checks for case where 25 is added
        p1Tree.add(25, "twenty-five");
        System.out.println(p1Tree.toString());
        assertTrue(p1Tree.getRoot().equals(p1Tree3.getRoot()));
    }

    @Test
    public void test_add_4() throws Exception {
        //checks for case where root is empty
        BinaryTree<Integer, String> tree = new BinaryTree<Integer, String>(null);
        tree.add(55, "fifty-five");
        System.out.println(tree.toString());
        System.out.println(p1Tree4.toString());
        assertTrue(tree.getRoot().equals(p1Tree4.getRoot()));
    }

    @Test
    public void test_add_5() throws Exception {
        //checks for case where 50 is updated
        p1Tree.add(50, "updated");
        System.out.println(p1Tree.toString());
        assertTrue(p1Tree.getRoot().equals(p1Tree5.getRoot()));
    }

    @Test
    public void test_find_1() throws Exception {
        assertTrue(p1Tree.find(10).equals("ten"));
    }

    @Test
    public void test_find_2() throws Exception {
        assertTrue(p1Tree.find(5) == null);
    }

    @Test
    public void test_find_3() throws Exception {
        assertTrue(p1Tree.find(70).equals("seventy"));
    }

    @Test
    public void test_find_4() throws Exception {
        assertTrue(p1Tree.find(35) == null);
    }

    @Test
    public void test_find_5() throws Exception {
        assertTrue(p1Tree.find(40).equals("forty"));
    }

    BinaryTree<Integer, Boolean> prob3_1 = new BinaryTree<Integer, Boolean>(null);
    BinaryTree<Integer, Boolean> prob3_2 = new BinaryTree<Integer, Boolean>(new Node<Integer, Boolean>(15, true));
    BinaryTree<Integer, Boolean> prob3_3 = new BinaryTree<Integer, Boolean>(new Node<Integer, Boolean>(1, true, null, new Node<Integer, Boolean>(2, true, null, new Node<Integer, Boolean>(3, true, null, new Node<Integer, Boolean>(4, true, null, new Node<Integer, Boolean>(5, false, null, null))))));

    @Test
    public void test_flatten_1() throws Exception {
        assertTrue(Arrays.equals(prob3_1.flatten(), new Boolean[0]));
    }

    @Test
    public void test_flatten_2() throws Exception {
        assertTrue(Arrays.equals(prob3_2.flatten(), new Boolean[] {true}));
    }

    @Test
    public void test_flatten_3() throws Exception {
        assertTrue(Arrays.equals(prob3_3.flatten(), new Boolean[] {true, true, true, true, false}));
    }

    @Test
    public void test_flatten_4() throws Exception {
        assertTrue(Arrays.equals(p1Tree5.flatten(), new String[] {"ten", "twenty", "thirty", "forty", "updated", "sixty", "seventy"}));
    }

    @Test
    public void test_flatten_5() throws Exception {
        assertTrue(Arrays.equals(p1Tree.flatten(), new String[] {"ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy"}));
    }

    /*
           5
        2     8
      1   3 7   9
    0
     */

    BinaryTree<Integer, Character> p4Tree = new BinaryTree<Integer, Character>(new Node<Integer, Character>(5, 'a',
            new Node<Integer, Character>(2, 'd',
                    new Node<Integer, Character>(1, 'e', new Node<>(0, 'g'), null),
                    new Node<Integer, Character>(3, 'f', null, null)),
            new Node<Integer, Character>(8, 'b',
                    new Node<Integer, Character>(7, 'h', null, null),new Node<Integer, Character>(9, 'c', null, null))));

    @Test
    public void test_remove_1() throws Exception {
        p4Tree.remove(-1);
        System.out.println(p4Tree.toString());
        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[] {'g', 'e', 'd', 'f', 'a', 'h', 'b', 'c'}));
    }

    @Test
    public void test_remove_2() throws Exception {
        p4Tree.remove(0);
        System.out.println(p4Tree.toString());

        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[] {'e', 'd', 'f', 'a', 'h', 'b', 'c'}));
    }

    @Test
    public void test_remove_3() throws Exception {
        p4Tree.remove(8);
        System.out.println(p4Tree.toString());

        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[] {'g', 'e', 'd', 'f', 'a', 'h', 'c'}));
    }

    @Test
    public void test_remove_4() throws Exception {
        p4Tree.remove(1);
        System.out.println(p4Tree.toString());

        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[] {'g', 'd', 'f', 'a', 'h', 'b', 'c'}));
    }

    @Test
    public void test_remove_5() throws Exception {
        p4Tree.remove(5);
        System.out.println(p4Tree.toString());

        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[] {'g', 'e', 'd', 'f', 'h', 'b', 'c'}));
    }
    @Test
    public void test_remove_6() throws Exception {
        p4Tree.remove(2);
        System.out.println(p4Tree.toString());

        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[] {'g', 'e', 'f', 'a', 'h','b', 'c'}));
    }
    @Test
    public void test_remove_7() throws Exception {
        p4Tree.remove(3);
        System.out.println(p4Tree.toString());

        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[] {'g', 'e', 'd', 'a', 'h','b', 'c'}));
    }
    @Test
    public void test_remove_8() throws Exception {
        p4Tree.remove(9);
        System.out.println(p4Tree.toString());

        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[]  {'g', 'e', 'd', 'f', 'a', 'h','b'}));
    }
    @Test
    public void test_remove_9() throws Exception {
        p4Tree.remove(10);
        System.out.println(p4Tree.toString());
        assertTrue(Arrays.equals(p4Tree.flatten(), new Character[] {'g', 'e', 'd', 'f', 'a', 'h','b', 'c'}));
    }
        /*
              40
          20      60
        10  30  50  70
         */
    BinaryTree<Integer, String> p5Tree = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(10, "ten"), new Node<Integer, String>(30, "thirty")),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy"))));

    BinaryTree<Integer, String> p5Tree1 = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(10, "ten"), new Node<Integer, String>(30, "thirty")),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy"))));

    BinaryTree<Integer, String> p5Tree2 = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(60, "ten"), new Node<Integer, String>(30, "thirty")),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy"))));

    BinaryTree<Integer, String> p5Tree3 = new BinaryTree<Integer, String>(new Node<Integer, String>(60, "sixty",
            new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy")));

    BinaryTree<Integer, String> p5Tree4 = new BinaryTree<Integer, String>(new Node<Integer, String>(40, "forty",
            new Node<Integer, String>(20, "twenty",
                    new Node<Integer, String>(10, "fifty"), new Node<Integer, String>(30, "thirty")),
            new Node<Integer, String>(60, "sixty",
                    new Node<Integer, String>(50, "fifty"), new Node<Integer, String>(70, "seventy"))));

    BinaryTree<Integer, String> p5Tree5 = new BinaryTree<Integer, String>(null);


    @Test
    public void test_containsSubtree_1() throws Exception {
        assertTrue(p5Tree.containsSubtree(p5Tree1));
    }

    @Test
    public void test_containsSubtree_2() throws Exception {
        System.out.println(p5Tree);
        System.out.println(p5Tree2);
        assertTrue(!(p5Tree.containsSubtree(p5Tree2)));
    }

    @Test
    public void test_containsSubtree_3() throws Exception {
        assertTrue(p5Tree.containsSubtree(p5Tree3));
    }

    @Test
    public void test_containsSubtree_4() throws Exception {
        assertTrue(!(p5Tree.containsSubtree(p5Tree4)));
    }

    @Test
    public void test_containsSubtree_5() throws Exception {
        assertTrue(p5Tree.containsSubtree(p5Tree5));
    }
}
