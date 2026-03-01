#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    int nr_angajati;
    char sediu[50];
    char nume[50];
}firma;

typedef struct{
    char nume[50];
    int varsta;
    firma f;
}   ANGAJAT;

void citire( int *n, ANGAJAT *a, FILE *f)
{
    for(int i=0;i<(*n);i++)
    {   
        //citire info 
        printf("\nNume: ");
        getchar();
        scanf("%[^\n]s", a[i].nume);
        printf("Varsta: ");
        getchar();
        scanf("%d", &a[i].varsta);
        printf("Nume firma: ");
        getchar();
        scanf("%[^\n]s", a[i].f.nume);
        printf("Nr angajati firma: ");
        getchar();
        scanf("%d", &a[i].f.nr_angajati);
        printf("Localitate sediu firma: ");
        getchar();
        scanf("%[^\n]s", a[i].f.sediu);
    }
     //scriere in fisier
    for(int i=0;i<(*n);i++)
        {
            fprintf(f, "%s\n%d\n%s\n%d\n%s\n", a[i].nume, a[i].varsta, a[i].f.nume, a[i].f.nr_angajati, a[i].f.sediu);
            fprintf(f, "\n");
        }
}
void adaugare(int *n, int *n2, ANGAJAT *a, FILE *f)
{
    for(int i=(*n);i<(*n2);i++)
    {   
        //citire info 
        printf("\nNume: ");
        getchar();
        scanf("%[^\n]s", a[i].nume);
        printf("Varsta: ");
        getchar();
        scanf("%d", &a[i].varsta);
        printf("Nume firma: ");
        getchar();
        scanf("%[^\n]s", a[i].f.nume);
        printf("Nr angajati firma: ");
        getchar();
        scanf("%d", &a[i].f.nr_angajati);
        printf("Localitate sediu firma: ");
        getchar();
        scanf("%[^\n]s", a[i].f.sediu);
    }
     //scriere in fisier
    for(int i=(*n);i<(*n2);i++)
        {
            fprintf(f, "%s\n%d\n%s\n%d\n%s\n", a[i].nume, a[i].varsta,a[i].f.nume, a[i].f.nr_angajati, a[i].f.sediu);
            fprintf(f, "\n");
        }
}
void selectare(ANGAJAT *a, int *n2, FILE *f)
{   
   //copie vector de structuri
    ANGAJAT *copie=malloc((*n2)*sizeof(ANGAJAT));
    if(copie==NULL)
    {
        printf("Eroare alocare");
        exit(1);
    }
    for(int i=0;i<(*n2);i++)
    {
        copie[i]=a[i];
    }


    //verificare 

    for(int i=0;i<(*n2);i++)
    {
        for(int k=i;k<(*n2);k++)
        {
            if(strcmp(copie[i].f.sediu,copie[k].f.sediu)==0)
            {   
                char nume_fisier[100];
                strcpy(nume_fisier,copie[i].f.sediu);
                strcat(nume_fisier, ".txt");
                
                f=fopen(nume_fisier, "a");
                if(f==NULL)
                {
                    printf("%s nu a putut fi deschis", nume_fisier);
                    exit(1);
                }
                fprintf(f, "%s\n%s\n", copie[k].nume, copie[k].f.nume);
                strcpy(copie[k].f.sediu, "a");
                fclose(f);
            }
        }
    }
    free(copie);
}
void ordonare(ANGAJAT *a, int *n2, FILE *f)
{
   //copie vector de structuri
    ANGAJAT *copie=malloc((*n2)*sizeof(ANGAJAT));
    if(copie==NULL)
    {
        printf("Eroare alocare");
        exit(1);
    }
    for(int i=0;i<(*n2);i++)
    {
        copie[i]=a[i];
    }
    
    f=fopen("pb8-ordonare.txt", "wt");
    if(f==NULL)
    {
        printf("f nu a putut fi deschis");
        exit(1);
    }
    ANGAJAT temp;
    int i;
    for(i=0;i<(*n2)-1;i++);
    {
        for(int k=i+1;k<(*n2);k++)
        {
            if(a[i].f.nr_angajati>a[k].f.nr_angajati)
            {
                temp=a[i];
                a[i]=a[k];
                a[k]=temp;
            }
        }
    }
    for(i=0;i<(*n2);i++)
    {
        fprintf(f, "%s\n%d\n%s\n%d\n%s\n", a[i].nume, a[i].varsta, a[i].f.nume, a[i].f.nr_angajati, a[i].f.sediu);
        fprintf(f, "\n");
    }
    fclose(f);
}
float medie(int *n2, ANGAJAT *a)
{   
    float medie;
    int varste=0;
    for(int i=0;i<(*n2);i++)
    {
   varste+=a[i].varsta;
    }
    medie=varste/(*n2);
    return medie;
}
int identificare(int *n2, ANGAJAT *a, int v[], int k, FILE *f)
{   
    f=fopen("Problema8.txt", "rt");
    if(f==NULL)
    {
        printf("f nu a putut fi deschis");
        exit(1);
    }
    float m;
    k=0;
    m=medie(&n2, a);
    for(int i=0;i<(*n2);i++)
    {
        if(a[i].varsta<m)
        {
            v[k]=ftell(f);
            k++;
        }
    }
    return k;

}

int main()
{
    FILE *f;
    f=fopen("Problema8.txt", "w");
    if(f==NULL)
    {
        printf("f nu a putut fi deschis");
        exit(1);
    }

    printf("introduceti numarul de angajati: ");
    int n,n1,n2;
    scanf("%d", &n);
    ANGAJAT *a;
    a=malloc(n*sizeof(ANGAJAT));
    citire(&n,a,f);
    printf("\nCati angajati doriti sa adaugati in fisier: ");
    scanf("%d", &n1);
    n2=n+n1;
    a=realloc(a, n2*sizeof(ANGAJAT));
    fclose(f);
    f=fopen("Problema8.txt", "a");
    if(f==NULL)
    {
        printf("f nu a putut fi deschis");
        exit(1);
    }
    adaugare(&n,&n2,a,f);
    fclose(f);
    selectare(a,&n2,f);

    free(a);
    fclose(f);
    return 0;
}