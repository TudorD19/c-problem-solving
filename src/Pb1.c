#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{   
    char sir[100];
    printf("Tastati o propozitie:\n");
    gets(sir);
    FILE*fisier;
    if((fisier=fopen("fisier.txt", "wt"))==NULL)
    {
        printf("fisierul nu s-a deschis");
        return 0;;
    }
    //scriere o singura comanda -- TEXT
    // fputs(sir, fisier);

    /*scriere printr-o singura comanda--BINAR
    fwrite(sir, sizeof(sir[0]), strlen(sir), fisier);*/
    
    /*scriere car cu car
    for(int k=0;k<strlen(sir);k++)
    {
            fputc(sir[k],fisier);
    }*/
  
    //scriere car cu car PE FIECARE LINIE   
    for(int k=0;k<strlen(sir);k++)
    {
            fputc(sir[k],fisier);
            fprintf(fisier, "\n");
    }
    fclose(fisier);
    return 0;
}