#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/param.h> 
struct point
{
    int x;
    int y;
};
typedef struct point point_t;

struct  rect
{
    /* data */
    point_t nor_wes;
    point_t sou_eas;
};
typedef struct rect rect_t;

void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}
void print_point(point_t *p) {
    printf("point(%d, %d)", p->x, p->y);
}

point_t make_point(int x, int y) {
    struct point p = {.x = x, .y = y};
    return p;
}

void print_rect(rect_t *rect) {
    printf("rectangle(Upper left = ");
    print_point(&rect->nor_wes);
    printf(", lower right = ");
    print_point(&rect->sou_eas);
    printf(")\n");
}

rect_t make_rect(int a, int b, int c, int d) {
    struct rect result = {.nor_wes = make_point(a, b), .sou_eas = make_point(c, d)};
    return result;
}

int area_rect(rect_t *rect) {
    //point_t upper_left = rect->nor_wes;
    //point_t lower_right = rect->sou_eas;
    int height = rect->nor_wes.y - rect->sou_eas.y;
    int width = rect->sou_eas.x - rect->nor_wes.x;
    return width * height;
}

bool intersects_rect(rect_t *rect1, rect_t *rect2) {
    return (rect1->nor_wes.x <= rect2->sou_eas.x && rect1->nor_wes.y >= rect2->sou_eas.y);
}

rect_t intersection_rect(rect_t *rect1, rect_t *rect2) {
    if (!intersects_rect(rect1, rect2)) {
        return make_rect(0, 0, 0, 0);
    } else {
        //superflus, but more readable
        struct point upper_left = make_point(
            MAX(rect1->nor_wes.x, rect2->nor_wes.x)
            ,
            MIN(rect1->nor_wes.y, rect2->nor_wes.y)
        );   
        struct point lower_right = make_point(
            MIN(rect1->sou_eas.x, rect2->sou_eas.x) 
            ,
            MAX(rect1->sou_eas.y, rect2->sou_eas.y));
        struct rect result = make_rect(upper_left.x, upper_left.y, lower_right.x, lower_right.y);
        
        return result;
    }

}

int main(void) {
    struct point peak = {.x = 5, .y = 6};
    print_point(&peak);
    struct point peak2 = make_point(9,11);
    print_point(&peak2);
    putchar('\n');

    struct rect rectangle1 = {.nor_wes = peak, .sou_eas = make_point(7, 3)};
    print_rect(&rectangle1);
    
    putchar('\n');
    struct rect made_rectangle = make_rect(0, 5, 10, -5);
    print_rect(&made_rectangle);
    
    putchar('\n');
    printf("%d\n", area_rect(&made_rectangle));

    putchar('\n');
    struct rect made_rectangle_2 = make_rect(-7, -1, 3, -3);
    printf("%d\n", area_rect(&made_rectangle_2));

    struct rect made_rectangle_3 = make_rect(-4, 8, 2, 2);
    struct rect made_rectangle_4 = make_rect(-4, 2, 2, -4);


    printf("%d\n", intersects_rect(&made_rectangle, &made_rectangle_2));
    printf("%d\n", intersects_rect(&made_rectangle_2, &made_rectangle_3));
    printf("%d\n", intersects_rect(&made_rectangle, &made_rectangle_3));
    printf("%d\n", intersects_rect(&made_rectangle_3, &made_rectangle_4));

    struct rect intersection = intersection_rect(&made_rectangle_2, &made_rectangle_4);
    print_rect(&intersection);
    putchar('\n');
    return 0;
}