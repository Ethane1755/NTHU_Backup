#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
  int x;
  int y;  
} Point;


Point * ones_vec_1(int length)
{
    /// Please implement
    /// 1. Malloc memory for point array
    /// 2. Read values into point array
    /// 3. Return the address of the first element in the array
    Point* arr = (Point*)malloc(sizeof(Point) * length);
    for (int i = 0; i < length; i++) {
        scanf("%d %d", &arr[i].x, &arr[i].y);
    }
    return arr;
}

float compute_distance(Point* a, int first_id, int second_id)
{
    float ans;
    Point first_p, second_p;

    /// Please implement
    /// 1. Get two point from function argument
    /// 2. Compute 2D distance and return ans

    first_p = a[first_id]; second_p = a[second_id];
    

    ans = sqrt((first_p.x - second_p.x) * (first_p.x - second_p.x) + (first_p.y - second_p.y) * (first_p.y - second_p.y));

    return ans;
}