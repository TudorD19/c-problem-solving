#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct persoana{
    char nume[50];
    char prenume[50];
    float varsta;
};
int main()
{
    struct persoana v[5];
    for(int i=0;i<5;i++)
    {
        printf("\nPersoana %d", i+1);
        printf("\nnume: ");
        scanf("%s", v[i].nume);
        printf("prenume: ");
        scanf("%s", v[i].prenume);
        printf("varsta: ");
        scanf("%f", &v[i].varsta);
    }

    FILE *f1;
    FILE *f2;
    f1=fopen("Problema6.txt", "w+");
    if(f1==NULL)
    {
        printf("f1 nu a putut fi deschis");
        return 0;
    }
     for(int i=0;i<5;i++)
    {
        fprintf(f1, "%s\n", v[i].nume);
        fprintf(f1, "%s\n", v[i].prenume);
        fprintf(f1,"%.2f\n",v[i].varsta);
        fprintf(f1,"\n");
    }  
    
    f2=fopen("Problema6.bin", "wb+");
    if(f2==NULL)
    {
        printf("f2 nu a putut fi deschis");
        return 0; 
    }
    for(int i=0;i<5;i++)
    {
        fwrite(&v[i], sizeof(struct persoana), 1, f2);
    }
    
    //b)

    printf("\nTEXT:\n");
    fflush(f1);
    rewind(f1);
    struct persoana p;
    for(int i=0;i<5;i++)
    {   
        fscanf(f1, "%s", p.nume);
        fscanf(f1,"%s", p.prenume);
        fscanf(f1, "%f", &p.varsta);

        printf("%s %s %.2f", p.nume, p.prenume, p.varsta);
        printf("\n");
    }
    
    printf("\nBINAR:\n");
    fflush(f2);
    rewind(f2);
    struct persoana b;
    for(int i=0;i<5;i++)
    {
        fread(&b, sizeof(struct persoana), 1, f2);
        printf("%s %s %.2f", b.nume, b.prenume, b.varsta);
        printf("\n");
    }

    //c)
    struct persoana nou;
    printf("\nNume: ");
    scanf("%s", nou.nume);
    printf("Prenume: ");
    scanf("%s", nou.prenume);
    printf("Varsta: ");
    scanf("%f", &nou.varsta);
    
    rewind(f1);
    rewind(f2);
    
    int verif_text=0, verif_bin=0;
    for(int i=0;i<5;i++)
    {
        fscanf(f1, "%s", p.nume);
        fscanf(f1,"%s", p.prenume);
        fscanf(f1, "%f", &p.varsta);
        if(strcmp(nou.nume,p.nume)==0&&strcmp(nou.prenume,p.prenume)==0&&nou.varsta==p.varsta)
        {
            printf("\nDA, structura se regaseste in fisierul text");
            verif_text=1;
        }
    }
    
    if(verif_text==0)
    {
    fflush(f1);
    fprintf(f1, "%s\n", nou.nume);
    fprintf(f1, "%s\n", nou.prenume);
    fprintf(f1,"%f\n",nou.varsta);
    printf("\nNU, structura nu se regaseste in fisierul text");

    }
    for(int i=0;i<5;i++)
    {
         fread(&b, sizeof(struct persoana), 1, f2);
         if(strcmp(nou.nume,b.nume)==0&&strcmp(nou.prenume,b.prenume)==0&&nou.varsta==b.varsta)
        {
            printf("\nDA, structura se regaseste in fisierul binar");
            verif_bin=1;
        }
    }
    if(verif_bin==0)
    {
    fflush(f2);
    fwrite(&nou, sizeof(struct persoana), 1, f2);
    printf("\nNU, structura nu se regaseste in fisierul binar");
    }
    //d)
    rewind(f1);
    rewind(f2);
    fflush(f1);
    fflush(f2);
    float medie_text=0, medie_bin=0;
    int count;
    if(verif_text==1)
    {   
        count=5;
        for(int i=0;i<5;i++)
        {
             fscanf(f1, "%s", p.nume);
            fscanf(f1,"%s", p.prenume);
            fscanf(f1, "%f", &p.varsta);
            medie_text+=p.varsta;
        }
        medie_text=medie_text/5;
    }
    else
    {   
        count=6;
        for(int i=0;i<6;i++)
        {
            fscanf(f1, "%s", p.nume);
            fscanf(f1,"%s", p.prenume);
            fscanf(f1, "%f", &p.varsta);
            medie_text+=p.varsta;
        }
        medie_text=medie_text/6;
    }
    printf("\nMedia de varsta a pers din fisierul text este %.2f", medie_text);

    if(verif_bin==1)
    {
        for(int i=0;i<5;i++)
        {
            fread(&b, sizeof(struct persoana), 1, f2);
            medie_bin+=b.varsta;
        }
        medie_bin=medie_bin/5;
    }
    else
    {
         for(int i=0;i<6;i++)
        {
            fread(&b, sizeof(struct persoana), 1, f2);
            medie_bin+=b.varsta;
        }
        medie_bin=medie_bin/6;
    }
    printf("\nMedia de varsta a pers din fisierul bin este %.2f", medie_bin);

    //e)--sortare

    rewind(f1);
    rewind(f2);

    struct persoana aux[count], temp;

    for(int i=0;i<count-1;i++)
    {
        fscanf(f1,"%s",p.nume);
        fscanf(f1,"%s", p.prenume);
        fscanf(f1,"%f", &p.varsta);
        aux[i]=p;
    }
    for(int i=0;i<count-1;i++)
    {
        for(int k=i;k<count;k++)
        {
            if(aux[i].varsta>aux[k].varsta)
            {
                temp=aux[i];
                aux[i]=aux[k];
                aux[k]=temp;
            }
        }
    }
    f1=fopen("Problema6.txt", "w+");
     if(f1==NULL)
    {
        printf("f1 nu a putut fi deschis");
        return 0;
    }
    for(int i=0;i<count;i++)
    {
        fprintf(f1, "%s\n", aux[i].nume);
        fprintf(f1, "%s\n", aux[i].prenume);
        fprintf(f1,"%.2f\n",aux[i].varsta);
        fprintf(f1,"\n");
    } 

    printf("\nfisierul TEXT ordonat:\n");
    fflush(f1);//citire
    rewind(f1);
    for(int i=0;i<count;i++)
    {   
        fscanf(f1, "%s", p.nume);
        fscanf(f1,"%s", p.prenume);
        fscanf(f1, "%f", &p.varsta);

        printf("%s %s %.2f", p.nume, p.prenume, p.varsta);
        printf("\n");
    }

//sortare binar
  for(int i=0;i<count-1;i++)
    {
        fread(&p, sizeof(struct persoana), 1, f2);
        aux[i]=p;
    }
    for(int i=0;i<count-1;i++)
    {
        for(int k=i;k<count;k++)
        {
            if(aux[i].varsta>aux[k].varsta)
            {
                temp=aux[i];
                aux[i]=aux[k];
                aux[k]=temp;
            }
        }
    }
    f2=fopen("Problema6.bin", "wb+");
     if(f2==NULL)
    {
        printf("f2 nu a putut fi deschis");
        return 0;
    }
    for(int i=0;i<count;i++)
    {
       fwrite(&aux[i],sizeof(struct persoana), 1, f2);
    } 
    rewind(f2);
    fflush(f2);
    printf("\nfisierul BINAR ordonat\n");
    for(int i=0;i<count;i++)
    {
        fread(&p,sizeof(struct persoana), 1, f2);
        printf("%s %s %.2f", p.nume, p.prenume, p.varsta);
        printf("\n");
    }

    fclose(f1);
    fclose(f2);
    return 0;




    




}
