#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NO_OF_PACKETS 10

int rando(int a)
{
    int rn = (random()%10)%a;
    return rn==0 ? 1:rn;
}

int main()
{
    int packetsize[NO_OF_PACKETS],clk,bucket_size,output_rate,packetsize_rm=0,p_time,op;
    for(int i=0; i<NO_OF_PACKETS; i++)
        packetsize[i] = rando(6)*10;
    for(int i=0; i<NO_OF_PACKETS; i++)
        printf("\npacket[%d]: %d bytes\t",i,packetsize[i]);
    printf("\nEnter the output rate: ");
    scanf("%d",&output_rate);
    printf("\nEnter the bucket size: ");
    scanf("%d",&bucket_size);
    for(int i=0; i<NO_OF_PACKETS; i++)
    {
        if((packetsize[i]+packetsize_rm)> bucket_size)
        {
            if(packetsize[i]> bucket_size)
                printf("\n\nIncoming packet size(%d bytes) is greater than bucket capacity (%d bytes) - PACKET REJECTED", packetsize[i], bucket_size);
            else
                printf("\n\nBucket capacity exceeded - PACKET REJECTED");
        }
        else
        {
            packetsize_rm += packetsize[i];
            printf("\n\nIncoming pack size: %d",packetsize[i]);
            printf("\nBytes remaining to transmit: %d",packetsize_rm);
            p_time = rando(4)*10;
            printf("\nTime left for transmission: %d units",p_time);
            for(clk = 10; clk <= p_time; clk += 10)
            {
                sleep(1);
                if(packetsize_rm)
                {
                    if(packetsize_rm)
                    {
                        if(packetsize_rm <= output_rate)
                        {
                            op = packetsize_rm;
                            packetsize_rm=0;
                        }
                        else
                        {
                            op = output_rate;
                            packetsize_rm -= output_rate;
                        }
                        printf("\nPacket size of %d transmitted",op);
                        printf("\n---Bytes remaining to transmit: %d",packetsize_rm);
                    }
                    else
                    {
                        printf("\nTime left for transmission: %d units",p_time-clk);
                        printf("\nNo packets to transmit!!!");
                    }
                }
            }
        }
    }
}