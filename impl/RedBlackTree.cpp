//an implementation of Red Black Tree

enum Color { RED, BLACK };

struct Vertex {
    int data;
    Color color;
    Vertex *left, *right, *parent;
};

class RBTree {
private:
    Vertex* root;
    Vertex* NIL;   // sentinel node

    void rotateLeft(Vertex* x) {
        Vertex* y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void rotateRight(Vertex* x) {
        Vertex* y = x->left;
        x->left = y->right;
        if (y->right != NIL)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    void insertV(Vertex* z) {
        while (z->parent->color == RED) {

            if (z->parent == z->parent->parent->left) {

                Vertex* y = z->parent->parent->right; // uncle

                if (y->color == RED) {
                    // Case 1
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        // Case 2
                        z = z->parent;
                        rotateLeft(z);
                    }
                    // Case 3
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }

            } else {

                Vertex* y = z->parent->parent->left; // uncle

                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotateRight(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Vertex* u, Vertex* v) {
        if (u->parent == NIL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }

    void deleteV(Vertex* x) {

        while (x != root && x->color == BLACK) {

            if (x == x->parent->left) {

                Vertex* w = x->parent->right;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color == BLACK &&
                    w->right->color == BLACK) {

                    w->color = RED;
                    x = x->parent;

                } else {

                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight(w);
                        w = x->parent->right;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft(x->parent);
                    x = root;
                }

            } else {

                Vertex* w = x->parent->left;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK &&
                    w->left->color == BLACK) {

                    w->color = RED;
                    x = x->parent;

                } else {

                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft(w);
                        w = x->parent->left;
                    }

                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }

        x->color = BLACK;
    }

    Vertex* minimum(Vertex* node) {
        while (node->left != NIL)
            node = node->left;
        return node;
    }

public:

    RBTree() {
        NIL = new Vertex();
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL->parent = NIL;

        root = NIL;
    }

    Vertex* search(int key) {
        Vertex* current = root;
        while (current != NIL && key != current->data) {
            if (key < current->data)
                current = current->left;
            else
                current = current->right;
        }
        return (current == NIL) ? nullptr : current;
    }

    void insert(int key) {

        Vertex* z = new Vertex();
        z->data = key;
        z->left = z->right = NIL;
        z->color = RED;

        Vertex* y = NIL;
        Vertex* x = root;

        while (x != NIL) {
            y = x;
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;

        if (y == NIL)
            root = z;
        else if (z->data < y->data)
            y->left = z;
        else
            y->right = z;

        insertV(z);
    }

    void remove(int key) {

        Vertex* z = search(key);
        if (!z) return;

        Vertex* y = z;
        Color yOriginalColor = y->color;
        Vertex* x;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        }
        else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        }
        else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z)
                x->parent = y;
            else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == BLACK)
            deleteV(x);
    }

    void inorder(Vertex* node) {
        if (node == NIL) return;
        inorder(node->left);
        cout << node->data << (node->color == RED ? "R " : "B ");
        inorder(node->right);
    }

    void printTree() {
        inorder(root);
        cout << endl;
    }
};
