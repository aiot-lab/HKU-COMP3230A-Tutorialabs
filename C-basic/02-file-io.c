#include <stdio.h>

int main(int argc, char *argv[]) {
    // create a file
    FILE *fp = fopen("test.txt", "w");
    // write to the file
    fprintf(fp, "hello world");
    // close the file
    fclose(fp);
    // open the file
    fp = fopen("test.txt", "r");
    // read from the file
    char buf[100];
    fgets(buf, 100, fp);
    printf("%s", buf);
    // close the file
    fclose(fp);
    return 0;
}