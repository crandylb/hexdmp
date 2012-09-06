/* hexdmp.c -- Dump in Hex and ASCII with Optional args, CRB, Mar 18, 1995 */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int hexdump(FILE *fp, char *filename, long start, long runlength);

int main(int argc, char *argv[])
{
    int retval;
    long addr = 0, start = 0, runlength = 0;
    FILE* fp;

    if ( argc < 2 )            /* this makes the filename optional */
        fp = stdin;
    else if ( argc > 4 || argv[1][0] == '-' ) {
        printf("useage: hexdump filename start runlength\n"
               "    where args are otional, start and lenlength\n"
               "    can be in decimal or hex, eg 0x25\n");
        exit ( 0 );
    }    
    else if ( (fp = fopen(argv[1], "rb")) == NULL ) {
        fprintf(stderr, "error: can't open '%s'\n", argv[1]);
        exit ( 2 );
    }
 
    if ( argc >= 3 ) {         /* optional starting position */
        start = strtol(argv[2], NULL, 0);
        addr = (start/16)*16;
    }

    if ( argc == 4 )           /* optional run length */
        runlength = strtol(argv[3], NULL, 0);

    if ( fp != stdin && fseek(fp, addr, SEEK_SET) == -1 ) {
        fprintf(stderr, "error: can't position '%s' to %l\n", argv[1], start);
        exit ( 3 );
    }

    retval = hexdump(fp, argv[1], start, runlength);

    if ( fp != stdin )
       fclose(fp);

    return retval;
}

int hexdump(FILE *fp, char *filename, long start, long runlength)
{
    int i, n;
    long addr = 0, limit = 1;
    unsigned char buff[16];
    int allzeros, morezeros = 0;

    addr = (start/16)*16;
    while ( n = fread(buff, 1, 16, fp) ) {     /* read n bytes */
        if ( runlength && addr + n > start + runlength )
            limit = start - addr + runlength;
        else
            limit = n;

        if ( limit == 0 )
            break;
 
        allzeros = 1;
        for ( i = 0; i < limit; i++ )
            if ( buff[i] ) {
                allzeros = 0;
                break;
            }

        if ( allzeros ) {
            if ( !morezeros ) {
                printf("...\n");
                morezeros = 1;
            }
            addr += n;
            continue;
        }
        morezeros = 0;

        printf("%08lX ", addr);         /* print byte address */
        for ( i = 0; i < limit; i++ ) { /* print up to limit bytes */
            if ( addr + i < start )
                printf("   ");
            else
                printf(" %02X", buff[i]);   /* each in 2-character hex */
            if ( i == 7 )               /* extra space after 8 bytes */
                printf(" ");
        }
        if ( limit < 16 )               /* extra space for ASCII part */
        for ( i = 0; i < 16 - limit; i++ )
            printf("   ");
        if ( limit < 8 )
            printf(" ");
        printf("  ");
        for ( i = 0; i < limit; i++ ) { /* print up to limit bytes */
            if ( addr + i < start )
                printf(" ");
            else if ( isprint(buff[i]) )/* each as a single ASCII */
                printf("%c", buff[i]);  /* character if printable */
            else                        /* otherwise just print */
                printf(".");            /* a single dot */
        }
        printf("\n");
        addr += limit;                  /* increment the address */
    }
    printf("\n");
    return 0;
}
