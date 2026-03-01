#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    printf("Scrieti propozitiile, separate prin punct.\n");
    char TEXT[500];
    gets(TEXT);
    FILE *f;
    f=fopen("text.txt", "w+");
    if(f==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        return 0;
    }
    char *propozitie;

    propozitie=strtok(TEXT,".");
    while(propozitie!=NULL)
    {   
        fputs(propozitie,f);
        fprintf(f,".");
        propozitie=strtok(NULL,".");
        fprintf(f,"\n");
    }
    fflush(f);  //scriere la citire
    rewind(f);  //redir la inceput de fisier
    int c;
    while((c=getc(f))!=EOF)
    {
        printf("%c",c);
    }

     rewind(f);  //redir la inceput de fisier


    //cautare cuvant
    char cuvant[50];
    int k=1;
    printf("\nIntroduceti cuvantul: ");
    scanf("%s", cuvant);
    char linie[200];
    printf("\nCuvantul %s a fost gasit in liniile: ", cuvant);
    while( fgets(linie, sizeof(linie), f)!=NULL)
    {
       if(strstr(linie, cuvant)!=NULL)
        {
            printf("%d ", k);
        }
        k++;
    }

    rewind(f);
    int contor_cuvinte=0,  contor_caractere=0;
    while(fgets(linie,sizeof(linie),f)!=NULL)
    {
        for(int i=0;linie[i]!='\0';i++)
        {
            if(linie[i]==' ')
            {
                contor_cuvinte++;
            }
            if(linie[i]!=' ')
            {
                contor_caractere++;
            }
        }
        contor_cuvinte++;
    }
    printf("\nFisierul are \nCuvinte: %d \nCaractere: %d ", contor_cuvinte, contor_caractere);
   
    rewind(f);

    int lungimemax=0, l=0;
    while(fgets(linie, sizeof(linie),f)!=NULL)
    {
        for(int i=0;linie[i]!='\0';i++)
        {
            l=i;
        }
        if(l>lungimemax)
        lungimemax=l;
    }

    printf("\nLiniile de lungime max (%d) sunt: ", lungimemax);

    rewind(f);
    while(fgets(linie, sizeof(linie), f)!=NULL)
    {
         for(int i=0;linie[i]!='\0';i++)
        {
            l=i;
        }
        if(l==lungimemax)
        printf("%s", linie);
    }
    fclose(f);
    return 0;
}