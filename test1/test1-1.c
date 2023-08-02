#include <stdio.h>

#define PI 3.14

int cylinder(double r, double h, double* V, double* S)
{
    if (r > 0 && h > 0)
    {
        *V = PI*r*h*h;
        *S = 2*PI*r*h; 
        
        return 1; 
    }
    
    return -1; 
}

int main()
{
    double r, h;
    double V;
    double S;  

    do
    {
        printf("r and h: ");

        do
        {
            scanf("%lf %lf", &r, &h);

            if (r < 0 || h < 0)
            {
                printf(":(\nTry again: ");
            }

        } while (r < 0 || h < 0);
        
        int result = cylinder(r, h, &V, &S);

        if (result != -1)
        {
            printf("V = %lf, S = %lf\n", V, S);
        }

    } while (r != 0 && h != 0);
    
    printf("End...\n");

    return 0;
}