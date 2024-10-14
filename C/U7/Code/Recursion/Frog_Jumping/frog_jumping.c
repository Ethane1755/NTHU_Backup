#include <stdio.h>
#include <limits.h>
#include <math.h>

int N;
int h[25+1];

int route[25]={1};//the current jumping path
int lenergy=INT_MAX;//least energy
int ljumps=INT_MAX;//least jumps

int cost(int jumps);//the energy consumed with respect to the current found path route[]

/*
cur: index of the current position
end: index of the end position
step: the step where we consider how to jump
*/
void jump(int cur, int end, int step);

int main(void)
{
    int i;

    scanf("%d",&N);
    for(i=1;i<=N;i++) scanf("%d",&h[i]);

    jump(1,N,1);

    printf("%d %d\n",lenergy,ljumps);

    return 0;
}

void jump(int cur, int end, int step)
{
    int i;

    //basis step
    if(cur>=end)
    {
        if(cur==end)//a path found in route[]: 0 <-> step-1
        {
            int cenergy=0;//current energy

            if((cenergy=cost(step-1))<lenergy)
            {
                lenergy=cenergy;
                ljumps=step-1;
            }
            else if(cenergy==lenergy && step-1<ljumps)
            {
                ljumps=step-1;
            }
        }

        return;
    }

    //recursive step: try possible jumps
    for(i=1;i<=2;i++)
    {
        route[step]=cur+i;//jump to (cur+i)th
        jump(cur+i,end,step+1);
    }
}

int cost(int jumps)
{
    int i=0;
    int totenergy=0;

    for(i=0;i<jumps;i++)
    {
        totenergy += abs(h[route[i]]-h[route[i+1]]);
    }

    return totenergy;
}
