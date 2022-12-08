#include "bits.h"
#include "treenode.h"
#include "huffman.h"
#include "map.h"
#include "vector.h"
#include "priorityqueue.h"
#include "strlib.h"
#include "testing/SimpleTest.h"
using namespace std;

/**
 * Given a Queue<Bit> containing the compressed message bits and the encoding tree
 * used to encode those bits, decode the bits back to the original message text.
 *
 * You can assume that tree is a well-formed non-empty encoding tree and
 * messageBits queue contains a valid sequence of encoded bits.
 *
 * Your implementation may change the messageBits queue however you like. There
 * are no requirements about what it should look like after this function
 * returns. The encoding tree should be unchanged.
 *
 * iterate over the queue of the bit and return if reach the leaf of the tree.
 */
string decodeText(EncodingTreeNode* tree, Queue<Bit>& messageBits) {
    EncodingTreeNode* cur = tree;
    string res = "";
    while (!messageBits.isEmpty()) {
        Bit bit = messageBits.dequeue();
        if (bit == false) cur = cur->zero;
        else cur = cur->one;
        if (cur->isLeaf()) {
            res += cur->getChar();
            cur = tree;
        }
    }
    return res;
}

/**
 * Reconstruct encoding tree from flattened form Queue<Bit> and Queue<char>.
 *
 * You can assume that the queues are well-formed and represent
 * a valid encoding tree.
 *
 * Your implementation may change the queue parameters however you like. There
 * are no requirements about what they should look like after this function
 * returns.
 *
 * Solve this problem use a recursive way.
 */
EncodingTreeNode* unflattenTree(Queue<Bit>& treeShape, Queue<char>& treeLeaves) {
    Bit bit = treeShape.dequeue();
    if (bit == false) {
        EncodingTreeNode* res = new EncodingTreeNode(treeLeaves.dequeue());
        return res;
    }
    EncodingTreeNode* left = unflattenTree(treeShape, treeLeaves);
    EncodingTreeNode* right = unflattenTree(treeShape, treeLeaves);
    EncodingTreeNode* res = new EncodingTreeNode(left, right);
    return res;
}

/**
 * Decompress the given EncodedData and return the original text.
 *
 * You can assume the input data is well-formed and was created by a correct
 * implementation of compress.
 *
 * Your implementation may change the data parameter however you like. There
 * are no requirements about what it should look like after this function
 * returns.
 *
 * Compound the above two function to construct the decompose function.
 */
string decompress(EncodedData& data) {
    EncodingTreeNode* tree = unflattenTree(data.treeShape, data.treeLeaves);
    string res =  decodeText(tree, data.messageBits);
    deallocateTree(tree);
    return res;
}

/**
 * Constructs an optimal Huffman coding tree for the given text, using
 * the algorithm described in lecture.
 *
 * Reports an error if the input text does not contain at least
 * two distinct characters.
 *
 * When assembling larger trees out of smaller ones, make sure to set the first
 * tree dequeued from the queue to be the zero subtree of the new tree and the
 * second tree as the one subtree.
 *
 * TODO: Add any additional information to this comment that is necessary to describe
 * your implementation.
 */
EncodingTreeNode* buildHuffmanTree(string text) {
    Map<char, double> map;
    // We construct a map to map a char to the time of it's occurrence.
    for (char c : text) {
        if (map.containsKey(c)) {
            map[c] += 1;
        } else {
            double priority = 1;
            map.put(c, priority);
        }
    }
    PriorityQueue<EncodingTreeNode*> pq;
    // We construct the priorityqueue through the information given by the map.
    for (char c : map) {
        EncodingTreeNode* cur = new EncodingTreeNode(c);
        pq.enqueue(cur, map[c]);
    }
    while (pq.size() > 1) {
        double priority1 = pq.peekPriority();
        EncodingTreeNode* first = pq.dequeue();
        double priority2 = pq.peekPriority();
        EncodingTreeNode* second = pq.dequeue();
        EncodingTreeNode* cur = new EncodingTreeNode(first, second);
        pq.enqueue(cur, priority1 + priority2);
    }
    return pq.dequeue();
}

// This is the helper function to traverse the tree and build the map.
void mapChar(EncodingTreeNode* tree, Map<char, Vector<Bit>>& map, Vector<Bit> code) {
    if (tree->isLeaf()) {
        char c = tree->getChar();
        map.put(c, code);
        return;
    }
    if (tree->zero != nullptr) {
        code.add(Bit(0));
        mapChar(tree->zero, map, code);
        code.remove(code.size() - 1);
    }
    if (tree->one != nullptr) {
        code.add(Bit(1));
        mapChar(tree->one, map, code);
    }
}
/**
 * Given a string and an encoding tree, encode the text using the tree
 * and return a Queue<Bit> of the encoded bit sequence.
 *
 * You can assume tree is a valid non-empty encoding tree and contains an
 * encoding for every character in the text.
 *
 * Solve this problem with a recursive helper function.
 */
Queue<Bit> encodeText(EncodingTreeNode* tree, string text) {
    Map<char, Vector<Bit>> map;
    Vector<Bit> code;
    Queue<Bit> res;
    mapChar(tree, map, code);
    for (char c : text) {
        code = map.get(c);
        for (Bit bit : code) {
            res.enqueue(bit);
        }
    }
    return res;
}

/**
 * Flatten the given tree into a Queue<Bit> and Queue<char> in the manner
 * specified in the assignment writeup.
 *
 * You can assume the input queues are empty on entry to this function.
 *
 * You can assume tree is a valid well-formed encoding tree.
 *
 * Also use a recursive way to solve the problem.
 */
void flattenTree(EncodingTreeNode* tree, Queue<Bit>& treeShape, Queue<char>& treeLeaves) {
    if (tree == nullptr) return;
    if (tree->isLeaf()) {
        char c = tree->getChar();
        treeLeaves.enqueue(c);
        treeShape.enqueue(Bit(0));
        return;
    } else {
        treeShape.enqueue(Bit(1));
        flattenTree(tree->zero, treeShape, treeLeaves);
        flattenTree(tree->one, treeShape, treeLeaves);
    }
}

/**
 * Compress the input text using Huffman coding, producing as output
 * an EncodedData containing the encoded message and flattened
 * encoding tree used.
 *
 * Reports an error if the message text does not contain at least
 * two distinct characters.
 *
 * Compound the above function and finally finish the compress function.
 */
EncodedData compress(string messageText) {
    EncodingTreeNode* tree = buildHuffmanTree(messageText);
    Queue<Bit> treeShape;
    Queue<char> treeLeaves;
    flattenTree(tree, treeShape, treeLeaves);
    Queue<Bit> messageBits = encodeText(tree, messageText);
    EncodedData res = {treeShape, treeLeaves, messageBits};
    deallocateTree(tree);
    return res; 
}

/* * * * * * Testing Helper Functions Below This Point * * * * * */

EncodingTreeNode* createExampleTree() {
    /* Example encoding tree used in multiple test cases:
     *                *
     *              /   \
     *             T     *
     *                  / \
     *                 *   E
     *                / \
     *               R   S
     */
    EncodingTreeNode* E = new EncodingTreeNode('E');
    EncodingTreeNode* R = new EncodingTreeNode('R');
    EncodingTreeNode* T = new EncodingTreeNode('T');
    EncodingTreeNode* S = new EncodingTreeNode('S');
    EncodingTreeNode* node1 = new EncodingTreeNode(R, S);
    EncodingTreeNode* node2 = new EncodingTreeNode(node1, E);
    EncodingTreeNode* node3 = new EncodingTreeNode(T, node2);
    return node3;
}

void deallocateTree(EncodingTreeNode* t) {
    if (t == nullptr) return;
    deallocateTree(t->zero);
    deallocateTree(t->one);
    delete t;
}

bool areEqual(EncodingTreeNode* a, EncodingTreeNode* b) {
    if (a == nullptr || b == nullptr) {
        if (a == b) return true;
        else return false;
    }
    if (a->isLeaf() && b->isLeaf()) {
        if (a->getChar() == b->getChar()) {
            return true;
        } else {
            return false;
        }
    } else if (a->isLeaf() || b->isLeaf()) {
        return false;
    } else {
        return areEqual(a->one, b->one) && areEqual(a->zero, b->zero);
    }
}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Write your own student tests. */
STUDENT_TEST("The test of the deallocate function!") {
    EncodingTreeNode* cur = createExampleTree();
    deallocateTree(cur);
    Queue<Bit>  treeShape  = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeLeaves = { 'T', 'R', 'S', 'E' };
    EncodingTreeNode* tree = unflattenTree(treeShape, treeLeaves);
    deallocateTree(tree);
}

STUDENT_TEST("The test of the areEqual function!") {
    EncodingTreeNode* tree1 = createExampleTree();
    EncodingTreeNode* tree2 = createExampleTree();
    EXPECT(areEqual(tree1, tree2));
    deallocateTree(tree2->one);
    tree2->one = nullptr;
    EXPECT(!areEqual(tree1, tree2));
    deallocateTree(tree1);
    deallocateTree(tree2);
}

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("decodeText, small example encoding tree") {
    EncodingTreeNode* tree = createExampleTree(); // see diagram above
    EXPECT(tree != nullptr);

    Queue<Bit> messageBits = { 1, 1 }; // E
    EXPECT_EQUAL(decodeText(tree, messageBits), "E");

    messageBits = { 1, 0, 1, 1, 1, 0 }; // SET
    EXPECT_EQUAL(decodeText(tree, messageBits), "SET");

    messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1}; // STREETS
    EXPECT_EQUAL(decodeText(tree, messageBits), "STREETS");

    deallocateTree(tree);
}

PROVIDED_TEST("unflattenTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    Queue<Bit>  treeShape  = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeLeaves = { 'T', 'R', 'S', 'E' };
    EncodingTreeNode* tree = unflattenTree(treeShape, treeLeaves);

    EXPECT(areEqual(tree, reference));

    deallocateTree(tree);
    deallocateTree(reference);
}

PROVIDED_TEST("decompress, small example input") {
    EncodedData data = {
        { 1, 0, 1, 1, 0, 0, 0 }, // treeShape
        { 'T', 'R', 'S', 'E' },  // treeLeaves
        { 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1 } // messageBits
    };

    EXPECT_EQUAL(decompress(data), "TRESS");
}

PROVIDED_TEST("buildHuffmanTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    EncodingTreeNode* tree = buildHuffmanTree("STREETTEST");
    EXPECT(areEqual(tree, reference));

    deallocateTree(reference);
    deallocateTree(tree);
}

PROVIDED_TEST("encodeText, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above

    Queue<Bit> messageBits = { 1, 1 }; // E
    EXPECT_EQUAL(encodeText(reference, "E"), messageBits);

    messageBits = { 1, 0, 1, 1, 1, 0 }; // SET
    EXPECT_EQUAL(encodeText(reference, "SET"), messageBits);

    messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1 }; // STREETS
    EXPECT_EQUAL(encodeText(reference, "STREETS"), messageBits);

    deallocateTree(reference);
}

PROVIDED_TEST("flattenTree, small example encoding tree") {
    EncodingTreeNode* reference = createExampleTree(); // see diagram above
    Queue<Bit>  expectedShape  = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> expectedLeaves = { 'T', 'R', 'S', 'E' };

    Queue<Bit>  treeShape;
    Queue<char> treeLeaves;
    flattenTree(reference, treeShape, treeLeaves);

    EXPECT_EQUAL(treeShape,  expectedShape);
    EXPECT_EQUAL(treeLeaves, expectedLeaves);

    deallocateTree(reference);
}

PROVIDED_TEST("compress, small example input") {
    EncodedData data = compress("STREETTEST");
    Queue<Bit>  treeShape   = { 1, 0, 1, 1, 0, 0, 0 };
    Queue<char> treeChars   = { 'T', 'R', 'S', 'E' };
    Queue<Bit>  messageBits = { 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0 };

    EXPECT_EQUAL(data.treeShape, treeShape);
    EXPECT_EQUAL(data.treeLeaves, treeChars);
    EXPECT_EQUAL(data.messageBits, messageBits);
}

PROVIDED_TEST("Test end-to-end compress -> decompress") {
    Vector<string> inputs = {
        "HAPPY HIP HOP",
        "Nana Nana Nana Nana Nana Nana Nana Nana Batman"
        "Research is formalized curiosity. It is poking and prying with a purpose. – Zora Neale Hurston",
    };

    for (string input: inputs) {
        EncodedData data = compress(input);
        string output = decompress(data);

        EXPECT_EQUAL(input, output);
    }
}
