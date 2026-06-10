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
#define ROWS    30    
#define COLS    100  
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
    printf("Shape with ID %d deleted successfully!\n", id);
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
    printf("\nCanvas Size: 100 columns x 30 rows\n");
    printf("Valid Columns: 0 - 99\n");
    printf("Valid Rows: 0 - 29\n");
    printf("\n");
    printf("\n===== Graphics Editor =====\n");
    printf("1. Add Rectangle\n");
    printf("2. Add Line\n");
    printf("3. Add Circle\n");
    printf("4. Add Triangle\n");
    printf("5. Delete Shape\n");
    printf("6. Modify Shape\n");
    printf("7. List Shapes\n");
    printf("8. Show Canvas\n");
    printf("9. Exit\n");
}
void modify_shape(void)
{
    int id;
    int i;

    printf("Enter shape ID to modify: ");
    scanf("%d", &id);

    for(i = 0; i < total; i++)
    {
        if(shapes[i].id == id && shapes[i].alive == 1)
        {
            if(shapes[i].type == RECTANGLE)
            {
                printf("Enter new x: ");
                scanf("%d", &shapes[i].x);

                printf("Enter new y: ");
                scanf("%d", &shapes[i].y);

                printf("Enter new width: ");
                scanf("%d", &shapes[i].a);

                printf("Enter new height: ");
                scanf("%d", &shapes[i].b);
            }

            else if(shapes[i].type == LINE)
            {
                printf("Enter new x1: ");
                scanf("%d", &shapes[i].x);

                printf("Enter new y1: ");
                scanf("%d", &shapes[i].y);

                printf("Enter new x2: ");
                scanf("%d", &shapes[i].a);

                printf("Enter new y2: ");
                scanf("%d", &shapes[i].b);
            }

            else if(shapes[i].type == CIRCLE)
            {
                printf("Enter new center x: ");
                scanf("%d", &shapes[i].x);

                printf("Enter new center y: ");
                scanf("%d", &shapes[i].y);

                printf("Enter new radius: ");
                scanf("%d", &shapes[i].a);
            }

            else if(shapes[i].type == TRIANGLE)
            {
                printf("Enter new apex x: ");
                scanf("%d", &shapes[i].x);

                printf("Enter new apex y: ");
                scanf("%d", &shapes[i].y);

                printf("Enter new height: ");
                scanf("%d", &shapes[i].a);
            }

            printf("Shape modified successfully!\n");

            clear_canvas();
            redraw_shapes();

            return;
        }
    }

    printf("Shape not found!\n");
}

void add_rectangle(void)
{
    int x, y, width, height;

    printf("Enter left column (x) [0-99]: ");
    scanf("%d", &x);

    printf("Enter top row (y) [0-29]: ");
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
    printf("Rectangle added successfully!\n");
}

void add_line(void)
{
    int x1, y1, x2, y2;

    printf("Enter start column x1 [0-99]: ");
    scanf("%d", &x1);

    printf("Enter start row y1 [0-29]: ");
    scanf("%d", &y1);

    printf("Enter end column x2 [0-99]: ");
    scanf("%d", &x2);

    printf("Enter end row y2 [0-29]: ");
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
    printf("Line added successfully!\n");

}

void add_circle(void)
{
    int x, y, radius;

    printf("Enter center column (x) [0-99]: ");
    scanf("%d", &x);

    printf("Enter center row (y) [0-29]: ");
    scanf("%d", &y);

    printf("Enter radius: ");
    scanf("%d", &radius);

    shapes[total].id = next_id++;
    shapes[total].type = CIRCLE;
    shapes[total].alive = 1;
    shapes[total].x = x;
    shapes[total].y = y;
    shapes[total].a = radius;

    total++;

    clear_canvas();
    redraw_shapes();

    printf("Circle added successfully!\n");
}

void add_triangle(void)
{
    int x, y, height;

    printf("Enter apex column (x) [0-99]: ");
    scanf("%d", &x);

    printf("Enter apex row (y) [0-29]: ");
    scanf("%d", &y);

    printf("Enter height: ");
    scanf("%d", &height);

    shapes[total].id = next_id++;
    shapes[total].type = TRIANGLE;
    shapes[total].alive = 1;
    shapes[total].x = x;
    shapes[total].y = y;
    shapes[total].a = height;

    total++;

    clear_canvas();
    redraw_shapes();

    printf("Triangle added successfully!\n");
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
            case 3:
                add_circle();
                break;
            case 4:
                add_triangle();
                break;
            case 5:
                delete_shape_menu();
                break;
           case 6:
                modify_shape();
                break;

            case 7:
                list_shapes();
                break;

            case 8:
                show_canvas();
                 break;

            case 9:
                printf("Exiting...\n");
                return 0;
        }
    }
    return 0;
}
// | Shape     | x          | y          | a      | b      |
// | --------- | ---------- | ---------- | ------ | ------ |
// | Rectangle | top-left x | top-left y | width  | height |
// | Line      | start x    | start y    | end x  | end y  |
// | Circle    | center x   | center y   | radius |   -    |
// | Triangle  | apex x     | apex y     | height |   -    |