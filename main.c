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
 
// removes the dots from the canvas (or) replaces '*' back to '_'
void remove_dot(int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
        canvas[row][col] = BLANK;
}

// Draws a rectangle using '*'
void draw_rectangle(int x, int y, int width, int height)
{
    int i;

    // top side
    for(i = x; i < x + width; i++)
        put_dot(y, i);

    // bottom side
    for(i = x; i < x + width; i++)
        put_dot(y + height - 1, i);

    // left side
    for(i = y; i < y + height; i++)
        put_dot(i, x);

    // right side
    for(i = y; i < y + height; i++)
        put_dot(i, x + width - 1);
}

//draw a line (vertical and horizontal)
void draw_line(int x1, int y1, int x2, int y2)
{
    int i;

    if(y1 == y2) // horizontal line
    {
        for(i = x1; i <= x2; i++)
            put_dot(y1, i);
    }

    else if(x1 == x2) // vertical line
    {
        for(i = y1; i <= y2; i++)
            put_dot(i, x1);
    }
}

// Draw a hollow triangle
void draw_triangle(int x, int y, int height)
{
    int i;

    // left side
    for(i = 0; i < height; i++)
        put_dot(y + i, x - i);

    // right side
    for(i = 0; i < height; i++)
        put_dot(y + i, x + i);

    // base
    for(i = x - height + 1; i <= x + height - 1; i++)
        put_dot(y + height - 1, i);
}

// Draws a  circle
void draw_circle(int x, int y, int radius)
{
    int row, col;
    int distance;

    for(row = y - radius; row <= y + radius; row++)
    {
        for(col = x - radius; col <= x + radius; col++)
        {
            distance = (row - y) * (row - y) +
                       (col - x) * (col - x);

            if(distance >= radius * radius - 2 &&
               distance <= radius * radius + 2)
            {
                put_dot(row, col);
            }
        }
    }
}



int main(void)
{
    clear_canvas();

    draw_rectangle(10, 5, 20, 8);

    draw_line(5, 15, 25, 15);

    draw_line(40,5,40,18);

    draw_triangle(55, 8, 6);

    draw_circle(25, 18, 5);

    show_canvas();

    return 0;
}