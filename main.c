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

void redraw_shapes(void)
{
    int i;

    for(i = 0; i < total; i++)
    {
        if(shapes[i].alive == 1)
        {
            if(shapes[i].type == RECTANGLE)
            {
                draw_rectangle(
                    shapes[i].x,
                    shapes[i].y,
                    shapes[i].a,
                    shapes[i].b
                );
            }

            else if(shapes[i].type == LINE)
            {
                draw_line(
                    shapes[i].x,
                    shapes[i].y,
                    shapes[i].a,
                    shapes[i].b
                );
            }

            else if(shapes[i].type == CIRCLE)
            {
                draw_circle(
                    shapes[i].x,
                    shapes[i].y,
                    shapes[i].a
                );
            }

            else if(shapes[i].type == TRIANGLE)
            {
                draw_triangle(
                    shapes[i].x,
                    shapes[i].y,
                    shapes[i].a
                );
            }
        }
    }
}

void delete_shape(int id)
{
    int i;

    for(i = 0; i < total; i++)
    {
        if(shapes[i].id == id)
        {
            shapes[i].alive = 0;
            break;
        }
    }
}
void delete_shape_menu(void)
{
    int id;

    printf("Enter shape ID to delete: ");
    scanf("%d", &id);

    delete_shape(id);

    clear_canvas();
    redraw_shapes();
}

void list_shapes(void)
{
    int i;

    printf("\nID\tType\t\tAlive\n");

    for(i = 0; i < total; i++)
    {
        printf("%d\t", shapes[i].id);

        if(shapes[i].type == RECTANGLE)
            printf("Rectangle\t");
        else if(shapes[i].type == LINE)
            printf("Line\t\t");
        else if(shapes[i].type == CIRCLE)
            printf("Circle\t\t");
        else if(shapes[i].type == TRIANGLE)
            printf("Triangle\t");

        if(shapes[i].alive)
            printf("Yes\n");
        else
            printf("No\n");
    }
}


void show_menu(void)
{
    printf("\n===== Graphics Editor =====\n");
    printf("1. Add Rectangle\n");
    printf("2. Add Line\n");
    printf("3. Add Circle\n");
    printf("4. Add Triangle\n");
    printf("5. Delete Shape\n");
    printf("6. List Shapes\n");
    printf("7. Show Canvas\n");
    printf("8. Exit\n");
}

void add_rectangle(void)
{
    int x, y, width, height;

    printf("Enter x: ");
    scanf("%d", &x);

    printf("Enter y: ");
    scanf("%d", &y);

    printf("Enter width: ");
    scanf("%d", &width);

    printf("Enter height: ");
    scanf("%d", &height);

    shapes[total].id = next_id++;
    shapes[total].type = RECTANGLE;
    shapes[total].alive = 1;
    shapes[total].x = x;
    shapes[total].y = y;
    shapes[total].a = width;
    shapes[total].b = height;

    total++;

    clear_canvas();
    redraw_shapes();
}

void add_line(void)
{
    int x1, y1, x2, y2;

    printf("Enter x1: ");
    scanf("%d", &x1);

    printf("Enter y1: ");
    scanf("%d", &y1);

    printf("Enter x2: ");
    scanf("%d", &x2);

    printf("Enter y2: ");
    scanf("%d", &y2);

    shapes[total].id = next_id++;
    shapes[total].type = LINE;
    shapes[total].alive = 1;
    shapes[total].x = x1;
    shapes[total].y = y1;
    shapes[total].a = x2;
    shapes[total].b = y2;

    total++;

    clear_canvas();
    redraw_shapes();
}

int main(void)
{
    clear_canvas();

    int choice;

    while(1)
    {
        show_menu();

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                add_rectangle();
                break;
            case 2:
                add_line();
                break;
            case 5:
                delete_shape_menu();
                break;
            case 6:
                list_shapes();
                break;

            case 7:
                show_canvas();
                break;

            case 8:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Option not implemented yet.\n");
        }
    }

// // Rectangle
// shapes[0].id=1;
// shapes[0].type = RECTANGLE;
// shapes[0].alive = 0;
// shapes[0].x = 10;
// shapes[0].y = 5;
// shapes[0].a = 20;
// shapes[0].b = 8;

// // Horizontal line
// shapes[1].id=2;
// shapes[1].type = LINE;
// shapes[1].alive = 1;
// shapes[1].x = 5;
// shapes[1].y = 15;
// shapes[1].a = 25;
// shapes[1].b = 15;

// // Vertical line
// shapes[2].id=3;
// shapes[2].type = LINE;
// shapes[2].alive = 1;
// shapes[2].x = 40;
// shapes[2].y = 5;
// shapes[2].a = 40;
// shapes[2].b = 18;

// // Triangle
// shapes[3].id=4;
// shapes[3].type = TRIANGLE;
// shapes[3].alive = 1;
// shapes[3].x = 55;
// shapes[3].y = 8;
// shapes[3].a = 6;

// // Circle
// shapes[4].id=5;
// shapes[4].type = CIRCLE;
// shapes[4].alive = 1;
// shapes[4].x = 25;
// shapes[4].y = 18;
// shapes[4].a = 5;

// total = 5;

    // draw_line(5, 15, 25, 15);

    // draw_line(40,5,40,18);

    // draw_triangle(55, 8, 6);

    // draw_circle(25, 18, 5);

    //delete_shape(5);

    // redraw_shapes();

    // list_shapes();

    // show_canvas();

    return 0;
}
// | Shape     | x          | y          | a      | b      |
// | --------- | ---------- | ---------- | ------ | ------ |
// | Rectangle | top-left x | top-left y | width  | height |
// | Line      | start x    | start y    | end x  | end y  |
// | Circle    | center x   | center y   | radius |   -    |
// | Triangle  | apex x     | apex y     | height |   -    |
