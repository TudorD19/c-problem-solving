#include<stdio.h>
#include<stdlib.h>
int main()
{   
    int n;
    printf("Dimensiune= ");
    scanf("%d", &n);
    int *v=malloc(n*sizeof(int));
    if(v==NULL)
   {
     printf("Alocare dinamica esuata");
     return 0;
   }
    for(int i=0;i<n;i++)
    {
        printf("\nv[%d]=", i);
        scanf("%d", &v[i]);
    }

    FILE *f1;
    FILE *f2;
    f1=fopen("problema3.txt", "w+");
    if(f1==NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        return 0;
    }
    f2=fopen("problema3.bin", "wb+");
    if(f2==NULL)
    {
        printf("Fisierul nu a putut fi deschis");
        return 0;
    }
//scriere in fisier
    for(int i=0;i<n;i++)
    {
        fprintf(f1,"%d ",v[i]);
    }
    fwrite(v, sizeof(int), n, f2);

//citire din fisier
    fflush(f1);
    rewind(f1);

    int *v_text=malloc(n*sizeof(int));
    if(v_text==NULL)
   {
     printf("Alocare dinamica esuata");
     return 0;
   }
    for(int i=0;i<n;i++)
    {
        fscanf(f1, "%d", &v_text[i]);
    }
    printf("\nTEXT: ");
    for(int i=0;i<n;i++)
    {
        printf("%d ", v_text[i]);
    }
    free(v_text);

    fflush(f2);
    rewind(f2);

    int *v_binar=malloc(n*sizeof(int));
    if(v_binar==NULL)
   {
     printf("Alocare dinamica esuata");
     return 0;
   }
    fread(v_binar, sizeof(int), n, f2);
    printf("\nBINAR:");
    for(int i=0;i<n;i++)
    {
        printf("%d ", v_binar[i]);
    }
    free(v_binar);

    free(v);

    fclose(f1);
    fclose(f2);
    return 0;

    
}