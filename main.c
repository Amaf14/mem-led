#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/io.h>
#include <string.h>

int main() {
        unsigned char val;
        int x, i=0, z;
        int a=0, b=0;
        int v[]={0, 0, 0, 0, 0, 0, 0, 0};
        char free[30], total[30];
        if( ioperm(888,1,1) ) {
                printf("Couldn't get port 888\n");
                return 1;
        }
        FILE *ff, *ft;
        ff=popen("egrep 'MemFree' /proc/meminfo", "r");
        ft=popen("egrep 'MemTotal' /proc/meminfo", "r");
        fgets(free, 30, ff);
        fgets(total, 30, ft);
        for(i=0;i<=strlen(free);i++) {
                if(free[i]>=48 && free[i]<=57)
                        a=a*10+(int)(free[i]-'0');
        }
        for(i=0;i<=strlen(total);i++) {
                if(total[i]>=48 && total[i]<=57)
                        b=b*10+(int)(total[i]-'0');
        }
        for(int z=0;z<=7;z++)
                if(z<(int)(b-a)/(b/8))
                        v[z]=1;
                else
                        v[z]=0;
        val = inb(888);
        for( x=0; x<8; x++ )
                if( v[x]!=1 )
                        val &= ~(1<<x);
                else
                        val |= 1<<x;
        outb(val, 888);
        sleep(1);
        outb(0,888);
        printf("%d\n", (int)(b-a)/(b/8));
        return 0;
}
