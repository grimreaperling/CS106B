/*
 * This file contains the functions to draw the sierpinski triangle with the given order.
 */
#include <iostream>    // for cout, endl
#include "recursion.h"
#include "testing/SimpleTest.h"
using namespace std;

/*
 * This function draws a filled, black triangle on the provided GWindow
 * that is defined by the corner GPoints one, two, and three. This
 * function has been provided for you and does not need to be modified.
 */
void fillBlackTriangle(GWindow& window, GPoint one, GPoint two, GPoint three) {
    window.setColor("black");
    window.fillPolygon( {one, two, three} );
}

/*
 * The function to draw the sierpinski triangle with the given position and the order.
 */
int drawSierpinskiTriangle(GWindow& window, GPoint one, GPoint two, GPoint three, int order) {
    int res = 0;
    if (order == 0) {
        fillBlackTriangle(window, one, two, three);
        return 1;
    }
    GPoint mid1((one.x + two.x) / 2, (one.y + two.y) / 2);
    GPoint mid2((one.x + three.x) / 2, (one.y + three.y) / 2);
    GPoint mid3((two.x + three.x) / 2, (two.y + three.y) / 2);
    res += drawSierpinskiTriangle(window, one, mid1, mid2, order - 1);
    res += drawSierpinskiTriangle(window, two, mid1, mid3, order - 1);
    res += drawSierpinskiTriangle(window, three, mid2, mid3, order - 1);
    return res;
}


/* * * * * * Test Cases * * * * * */

/*
 * Do not modify the code beyond this line! There are no
 * unit tests for this problem. You should do all testing
 * via the interactive demo.
 */

PROVIDED_TEST("Test fractal drawing interactively using graphical demo") {
    runInteractiveDemo();
}

