#include<stdio.h>
int main()
{
    int bucket_size,n,outgoing,incoming,store=0;
    printf("Enter bucket size : ");
    scanf("%d",&bucket_size);
    printf("Enter Outgoing Rate : ");
    scanf("%d",&outgoing);
    printf("Enter No: of Inputs : ");
    scanf("%d",&n);
    while(n!=0)
    {
        printf("\nEnter Incoming Packet Size : ");
        scanf("%d",&incoming);
        printf("\nIncoming Packet Size : %d\n",incoming);
        if(incoming<=(bucket_size-store))
        {
            store+=incoming;
            printf("Bucket Buffer Size %d out of %d\n",store,bucket_size);
        }
        else
        {
            printf("Dropped %d no: of packets.\n",incoming-(bucket_size-store));
            printf("Bucket Buffer Size %d out of %d\n",store,bucket_size);
            store=bucket_size;
        }
        store=store-outgoing;
        printf("After Outgoing %d Packets Left out of %d in Buffer..\n\n",store,bucket_size);
    }
}