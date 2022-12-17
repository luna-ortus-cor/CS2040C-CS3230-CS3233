//binary search tree is where every node to the left is smaller than parent, and every node to the right is larger than parent
//for equal values, need to tweak
//implements Table or Map Abstract Data Type (ADT)
//needs to support following 3 operations as efficiently as possible
//exists(v),insert(v),remove(v)
//if use unsorted array/vector, O(N), O(1), O(N) time complexity respectively
//if use sorted array/vector, O(logN), O(N), O(N) time complexity respectively
//other operations possible: min ele, max ele, next larger ele, previous smaller ele, list ele in sorted
//consists of root vertex, internal vertices, and leaf vertex (vertices)
//each vertex at least 4 attributes: parent (can be null), left, right, key/value/data
//all vertices on left subtree strictly smaller than parent, and all vertices on right subtree strictly greater than parent
//to handle duplicate, can include additional data to store frequency/occurence of value
//5. BST operations //TODO + REMOVE
