#include "header.h"

int main(int argc, char const *argv[])
{
    FILE *fp;
    char buffer[0xa];
    fp = fopen("./tp2-binaires/niveau1", "r");

    // Moving pointer to end
    fseek(fp, 0xb00, SEEK_SET);

    // Printing position of pointer
    fread(buffer,0xa,1,fp);

    printf("%s\n",buffer );

    return 0;
}
