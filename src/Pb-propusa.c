#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char cod_produs[50];
    char denumire[50];
    int cantitate;
    float pret;
} marfa;

int main()
{
    FILE *f1,*f2;
    f1=fopen("marfuri1.dat", "wb");
    if(f1==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    
    f2=fopen("marfuri2.dat", "wb");
    if(f2==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    int n1,n2;
    marfa temp;
    //1
    printf("\nElemente stoc 1: ");
    scanf("%d", &n1);
    marfa *m1=malloc(n1*sizeof(marfa));
    for(int i=0;i<n1;i++)
    {   
        
        printf("\ncod produs: ");
        getchar();
        gets(m1[i].cod_produs);
        printf("denumire: ");
        
        fflush(stdin);

        gets(m1[i].denumire);
        printf("cantitate: ");
        scanf("%d", &m1[i].cantitate);
        printf("pret unitar: ");
        scanf("%f", &m1[i].pret);
    }
    for(int i=0;i<n1-1;i++)
    {
        for(int k=i+1;k<n1;k++)
        {
            if(strcmp(m1[i].cod_produs,m1[k].cod_produs)>0)
            {
                temp=m1[i];
                m1[i]=m1[k];
                m1[k]=temp;
            }
        }
    }
    fwrite(m1,sizeof(marfa),n1,f1);
    fclose(f1);
    free(m1);


    //2
    printf("\nElemente stoc 2: ");
    scanf("%d", &n2);
    marfa *m2=malloc(n2*sizeof(marfa));
    for(int i=0;i<n2;i++)
    {   
        printf("\ncod produs: ");
        getchar();
        gets(m2[i].cod_produs);
        printf("denumire: ");

        fflush(stdin);
        
        gets(m2[i].denumire);
        printf("cantitate: ");
        scanf("%d", &m2[i].cantitate);
        printf("pret unitar: ");
        scanf("%f", &m2[i].pret);
    }
    for(int i=0;i<n2-1;i++)
    {
        for(int k=i+1;k<n2;k++)
        {
            if(strcmp(m2[i].cod_produs,m2[k].cod_produs)>0)
            {
                temp=m2[i];
                m2[i]=m2[k];
                m2[k]=temp;
            }
        }
    }
    fwrite(m2,sizeof(marfa),n2,f2);
    fclose(f2);
    free(m2);

    f1=fopen("marfuri1.dat", "a+b");
    if(f1==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    f2=fopen("marfuri2.dat", "rb");
    if(f2==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    marfa *m;
    m=malloc(n2*sizeof(marfa));
    fread(m,sizeof(marfa),n2,f2);
    fwrite(m,sizeof(marfa),n2,f1);
    m=realloc(m,(n1+n2)*sizeof(marfa));
    fseek(f1,0,0);
    fread(m,sizeof(marfa),(n1+n2),f1);

    fclose(f1);
    fclose(f2);


    FILE *f;
    f=fopen("marfuri.dat", "wb");
    if(f==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }

    for(int i=0;i<n1+n2-1;i++)
    {
        for(int k=i+1;k<n1+n2;k++)
        {
            if(strcmp(m[i].cod_produs,m[k].cod_produs)>0)
            {
                temp=m[i];
                m[i]=m[k];
                m[k]=temp;
            }
        }
    }
    fwrite(m,sizeof(marfa), (n1+n2), f);

    fclose(f);
    free(m);


    //parcurgere

    marfa p;

    f=fopen("marfuri.dat", "rb");
    fseek(f, 0, SEEK_END);
    int n;
    n=ftell(f)/sizeof(marfa);
    fseek(f,0,SEEK_SET);
    for(int i=0;i<n;i++)
    {
        fread(&p,sizeof(marfa), 1,f);
        printf("\nDenumire produs: %s\nCantitate: %d",p.denumire,p.cantitate);
    }
    fclose(f);

    //modificare

    f=fopen("marfuri.dat", "r+b");
    if(f==NULL)
    {
        printf("fisierul nu poate fi deschis");
        exit(1);
    }
    char criteriu[100];
    printf("\nIntroduceti denumirea produsului pe care doriti sa l modificati: ");
    getchar();
    gets(criteriu);
    for(int i=0;i<n;i++)
    {
        fread(&p,sizeof(marfa),1,f);
        if(strcmp(p.denumire, criteriu)==0)
        {
            printf("\nNoul pret unitar: ");
            scanf("%f", &p.pret);
            fseek(f,(-1)*(sizeof(marfa)), SEEK_CUR);
            fwrite(&p,sizeof(marfa),1,f);
        }
    }
    fclose(f);


    //verificare 


    f=fopen("marfuri.dat", "rb");

    fseek(f,0,SEEK_SET);
    for(int i=0;i<n;i++)
    {
        fread(&p,sizeof(marfa), 1,f);
        printf("\nDenumire produs: %s\nPret: %.2f",p.denumire,p.pret);
    }
    fclose(f);

}