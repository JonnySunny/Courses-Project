/*
    Author: Zhongyi Sun sunx0725
            Don Le      lexxx675
    Modified the Node.java Class by adding a method : setKey(K key)
        public void setKey(K key) {
        this.key = key ;
        }
    Modified thw test by adding several different cases to test our code.
 */

import java.util.*;

public class BinaryTree<K extends Comparable<K>, V> {
    private Node<K, V> root;
    private int size; //number of nodes
    private String string;

    public BinaryTree(Node<K,V> root) {
        if (root == null ) {
            size = 0;
        }
        else {
            //constructor method to properly add all of the nodes to the tree
            constructorHelper(root);
        }
        this.root = root;
    }

    //Helper method to add nodes to the tree and keep track of the size
    public void constructorHelper (Node <K, V> root) {
        add(root.getKey(),root.getValue());
        Stack<Node> s = new Stack<Node>();
        s.add(root);
        size = 1;

        //Pop nodes off the stack to add them to the tree. Push any of their children onto the stack.
        while (!s.isEmpty()) {
            Node x = s.pop();

            if (x.getRight() != null) {
                s.add(x.getRight());
                add((K)(x.getRight().getKey()), (V)(x.getRight().getValue()));
            }
            if (x.getLeft() != null) {
                s.add(x.getLeft());
                add((K)(x.getLeft().getKey()), (V)(x.getLeft().getValue()));
            }
        }
    }

    public Node<K, V> getRoot() {
        return this.root;
    }

    public void add(K key, V value) {
        if(key == null ){
            return;
        }
        else {
            size++; //keeps track of the size as we add more nodes
            //Handle case that we don't have a root
            if (root == null || root.getValue() == null) {
                root = new Node<K,V>(key, value);
            } else {
                //Add to left or right recursively if key is lesser or greater respectively
                if (key.compareTo(root.getKey()) < 0) {
                    root.setLeft(addHelper(root.getLeft(), new Node<K,V>(key, value)));
                }
                else {
                    root.setRight(addHelper(root.getRight(), new Node<K,V>(key, value)));
                }
            }
        }
    }

    //Recursive helper method to add nodes
    public Node<K,V> addHelper(Node<K,V> root, Node<K,V> node ) {
        if (root == null) {
            root = node;
        }
        else {
            //Check if we should add to the left, update the current value, or add to the right
            if (node.getKey().compareTo(root.getKey()) < 0) {
                root.setLeft(addHelper(root.getLeft(), node));
            } else if (node.getKey().compareTo(root.getKey()) == 0) {
                root.setValue(node.getValue());
            } else {
                root.setRight(addHelper(root.getRight(), node));
            }
        }
        return root;
    }

    //Helper method to the find value associated with a key
    public V find(K key) {
        if (key == null ) {
            //throw Exception("No key found");
            System.out.println("KEY IS NULL ");
            return null;
        } else {
            return findHelper(root, key);
        }
    }

    //Recursive helper method to continue searching until the value is found
    public V findHelper(Node<K,V> root, K key) {
        if (root == null ) {
            System.out.println("VALUE CANNOT FIND, IT IS NULL ");
            return null;
        }
        //Return the value if the right node was found, otherwise check the left or right subtrees
        if (key.compareTo(root.getKey()) == 0) {
            return root.getValue();
        } else if (key.compareTo(root.getKey()) <= 0) {
            return findHelper(root.getLeft(), key);
        } else {
            return findHelper(root.getRight(), key);
        }
    }

    @SuppressWarnings("unchecked")
    public V[] flatten() {
        if(size == 0) {
            return (V[]) new Object[size];
        }
        else {
            V[] ans = (V[]) new Object[size];
            Stack<Node> s = new Stack<Node>();
            s.add(root);
            HashMap<K,V> dic = new HashMap<>();
            ArrayList<K> keys = new ArrayList<>();
            dic.put(root.getKey(),root.getValue());
            int pos = 0;

            //Loop over all nodes to store their keys and values in a dictionary and list
            while (!s.isEmpty() && pos < size) {
                Node x = s.pop();
                dic.put((K)x.getKey(),(V)x.getValue());
                keys.add((K)x.getKey());
                if (x.getRight() != null) s.add(x.getRight());
                if (x.getLeft() != null) s.add(x.getLeft());
            }
            Collections.sort(keys); //the result is sorted by key values
            //Fill the array with values sorted by their keys
            for(K i: keys) {
                ans[pos++] = dic.get(i);
            }
            return ans;
        }
    }

    public void remove(K key) {
        if (key == null || find(key) == null) {
            return;
        }

        else {
            Node<K,V> parent = findNode(root,key)[0]; //get the parent of the node you want to remove
            Node<K,V> ptr = findNode(root,key)[1]; //get the node that you want to remove

            if(ptr == null) {
                return;
            } else if (ptr.getLeft() == null ) { //Check if we have no left branch
                //If the node we want to remove is the root, set the new root to the previous root's right
                if (ptr == root) {
                    root = root.getRight();
                } else {
                    //Check whether the node to remove is the parent's left or right and set that the child's right (since we know it has no left)
                    if (ptr == parent.getLeft()) {
                        parent.setLeft(ptr.getRight());
                    } else {
                        parent.setRight(ptr.getRight());
                    }
                }
            }
                else { //Case where we have a left branch
                    Node<K,V> temp = findRightMostNode(ptr.getLeft())[1]; //find the node with the maximum value in the node to be removed's left subtree
                    //Reset the nodes values to that of the maximum
                    ptr.setKey(temp.getKey());
                    ptr.setValue(temp.getValue());
                    //If the max value node is the node to be removed's left (which therefore has no right subtree), connect its left the the rest of the tree
                    if(temp == ptr.getLeft()) {
                        ptr.setLeft(temp.getLeft());
                    }
                    //Otherwise we should remove the max value that we used as a replacement
                    else {
                        Node<K, V> parent2 = findRightMostNode(ptr.getLeft())[0];
                        parent2.setRight(null);
                    }
            }
            size--; //keep track of size as we remove nodes
        }

    }

    //Helper method to find the node with the max value and its parent to be used in the remove method
    public Node<K,V>[] findRightMostNode (Node<K,V> node) {
        Node<K,V>[] ans = new Node[2];
        Node<K,V> parent = node;
        Node<K,V> ptr = node;

        while (ptr.getRight() != null) {
            parent = ptr;
            ptr = ptr.getRight();
        }

        ans[0] = parent;
        ans[1] = ptr;
        return ans;
    }

    //Helper method to return the node associated with a key
    public Node<K,V>[] findNode (Node<K,V> node, K key) {
        Node<K,V>[] ans = new Node[2];
        Node<K,V> parent = null;
        Node<K,V> ptr = node;

        while (ptr != null && key.compareTo(ptr.getKey()) != 0 ) {
            parent = ptr;
            if(key.compareTo(ptr.getKey()) <= 0) {
                ptr = ptr.getLeft();
            } else {
                ptr = ptr.getRight();
            }
        }
        ans[0] = parent; //return the parent of the node
        ans[1] = ptr; //return the node itself
        return ans;
    }

    public boolean containsSubtree(BinaryTree<K, V> other) {
        if(other == null || other.getRoot() == null) {
            return true;
        }

        else if(find(other.getRoot().getKey()) != null) {
            Node<K, V> ptr = findNode(root,other.getRoot().getKey())[1];
            Node<K,V> otherRoot = other.getRoot();
            return containsSubtreeHelper(ptr, otherRoot);
        }
        else {
            return false;
        }
    }

    //Recursive helper function that checks if the current nodes are equal
    public boolean containsSubtreeHelper(Node<K,V> thisRoot, Node<K,V> otherRoot) {
        boolean left;
        boolean right;

        //If any of the nodes compared are not equal, false will be propagated upward
        if (thisRoot == null && otherRoot != null || otherRoot == null && thisRoot != null) {
            left = false;
            right = false;
        } else if (thisRoot == null) {
            left = true;
            right = true;
        } else if (thisRoot.equals(otherRoot)) {
            left =  containsSubtreeHelper(thisRoot.getLeft(), otherRoot.getLeft());
            right =  containsSubtreeHelper(thisRoot.getRight(), otherRoot.getRight());
        } else {
            left = false;
            right = false;
        }
        return left && right;
    }

    //Helper method to debug
    public String toString() {
        if(size == 0) {
            return "";
        }
        else {
            string = "{ ";
            toStringHelper(root);
            string = string + " }";
            return string;
        }
    }

    //Helper method for toString()
    public void toStringHelper(Node<K,V> thisRoot) {
        if (thisRoot == null) {
            return;
        }
        else {
            string += ""+thisRoot.getKey() +" , " +thisRoot.getValue() +" , ";
            toStringHelper(thisRoot.getLeft());
            toStringHelper(thisRoot.getRight());
        }
    }

}
