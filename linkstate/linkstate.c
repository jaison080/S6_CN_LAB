#include <stdio.h>
#include <string.h>
int main()
{
    int count, src_router, i, j, k, w, v, min;
    int cost_matrix[100][100], dist[100], last[100];
    int flag[100];
    char src;
    printf("Enter the no of routers: ");
    scanf("%d", &count);
    printf("Enter the cost matrix values:\n\n");
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            printf("%c->%c:", 97 + i, 97 + j);
            scanf("%d", &cost_matrix[i][j]);
            if (cost_matrix[i][j] < 0)
                cost_matrix[i][j] = 1000;
        }
    }
    printf("\n Enter the source router:");
    scanf(" %c", &src);
    src_router = src - 97;
    for (v = 0; v < count; v++)
    {
        flag[v] = 0;
        last[v] = src_router;
        dist[v] = cost_matrix[src_router][v];
    }
    flag[src_router] = 1;
    for (i = 0; i < count; i++)
    {
        min = 1000;
        for (w = 0; w < count; w++)
        {
            if (!flag[w])
                if (dist[w] < min)
                {
                    v = w;
                    min = dist[w];
                }
        }
        flag[v] = 1;
        for (w = 0; w < count; w++)
        {
            if (!flag[w])
                if (min + cost_matrix[v][w] < dist[w])
                {
                    dist[w] = min + cost_matrix[v][w];
                    last[w] = v;
                }
        }
    }
    for (i = 0; i < count; i++)
    {
        printf("\n%c==>%c: \nPath taken:%c", 97 + src_router, 97 + i, 97 + i);
        w = i;
        while (w != src_router)
        {
            printf("<--%c", 97 + last[w]);
            w = last[w];
        }
        printf("\nShortest path cost:%d\n", dist[i]);
    }
}