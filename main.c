// =========================================================
// Graphics Editor Project
// Developed by Anish
// Uses a 2D character array as canvas
// '_' = empty space
// '*' = drawing character
// =========================================================
 
#include <stdio.h>
#include <stdlib.h>
 
/* ------- canvas size and special characters ------- */
#define ROWS    25     
#define COLS    70    
#define BLANK   '_'     /* empty cell character*/
#define DOT     '*'     /* drawn cell character*/
#define MAX     64
 
/* ------- shape type numbers ------- */
#define CIRCLE    1
#define RECTANGLE 2
#define LINE      3
#define TRIANGLE  4
 
/* ------- one shape stored as a struct ------- */
/*
   x, y  = position 
   a, b  = size    
 
   CIRCLE    : x,y = centre,   a = radius
   RECTANGLE : x,y = top-left, a = width,  b = height
   LINE      : x,y = start,    a = end-x,  b = end-y
   TRIANGLE  : x,y = apex,     a = base-x, b = base-y
*/
struct Shape {
    int id;       /* unique number for this shape  */
    int type;     /* CIRCLE / RECTANGLE / LINE / TRIANGLE */
    int alive;    /* 1 = on canvas,  0 = deleted   */
    int x, y;     /* position parameter 1 and 2    */
    int a, b;     /* size    parameter 3 and 4    */
};
 
/* ------- global ------- */
char         canvas[ROWS][COLS];      /* the drawing grid      */
struct Shape shapes[MAX];             /* list of all shapes    */
int          total   = 0;             /* how many shapes added */
int          next_id = 1;            /* ID to give next shape */
 
// =========================================================
//                    CANVAS FUNCTIONS
// ========================================================= 
 
// Fill the whole canvas with blank characters 
void clear_canvas(void)
{
    int r, c;
    for (r = 0; r < ROWS; r++)
        for (c = 0; c < COLS; c++)
            canvas[r][c] = BLANK;
}
 
// Displays the current canvas along with the border
void show_canvas(void)
{
    int r, c;
 
    /* top border */
    printf("+");
    for (c = 0; c < COLS; c++) printf("-");
    printf("+\n");
 
    /* each row */
    for (r = 0; r < ROWS; r++) {
        printf("|");
        for (c = 0; c < COLS; c++)
            printf("%c", canvas[r][c]);
        printf("|\n");
    }
 
    /* bottom border */
    printf("+");
    for (c = 0; c < COLS; c++) printf("-");
    printf("+\n");
}
 
//puts dots i.e, '*' on the canvas (or) replaces '_' with '*'
void put_dot(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
        canvas[row][col] = DOT;
}
 
// removes the dots from the canvas (or) replaces '*' with '_'
void remove_dot(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
        canvas[row][col] = BLANK;
}





int main(void)
{
    clear_canvas();
    show_canvas();

    return 0;
}