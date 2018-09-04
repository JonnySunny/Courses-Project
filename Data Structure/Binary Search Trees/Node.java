public class Node<K extends Comparable<K>, V> {
    private K key;
    private V value;
    private Node<K, V> left, right;

    public Node(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public Node(K key, V value, Node<K, V> left, Node<K, V> right) {
        this.key = key;
        this.value = value;
        this.left = left;
        this.right = right;
    }

    public boolean equals(Node<K, V> other) {
        if (other == null) return false;
        boolean left, right;
        if (this.left == null) {
            left = other.left == null;
        }
        else {
            left = this.left.equals(other.left);
        }
        if (this.right == null) {
            right = other.right == null;
        }
        else {
            right = this.right.equals(other.right);
        }
        return left && right && this.key.equals(other.key) && this.value.equals(other.value);
    }
    public void setKey(K key) {
        this.key = key ;
    }
    public K getKey() {
        return key;
    }

    public V getValue() {
        return value;
    }

    public void setValue(V value) {
        this.value = value;
    }

    public Node<K, V> getLeft() {
        return left;
    }

    public void setLeft(Node<K, V> left) {
        this.left = left;
    }

    public Node<K, V> getRight() {
        return right;
    }

    public void setRight(Node<K, V> right) {
        this.right = right;
    }
}
