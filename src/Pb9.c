#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char prenume[40];
    char sex;
    float nota;
}   studenti;

float nota_max(studenti s, FILE *f, int *n2, char persoane[50][50], int *k)
{   
    float nota_maxima=0;

    for(int i=0;i<(*n2);i++)
     {
            fread(&s,sizeof(studenti),1,f);
            if(s.nota>nota_maxima)
            {
                nota_maxima=s.nota;
            }
     }

     (*k)=0; 
     fseek(f,0,SEEK_SET);
     for(int i=0;i<(*n2);i++)
     {
        fread(&s, sizeof(studenti), 1, f);
        if(s.nota==nota_maxima)
        {
            strcpy(persoane[*k], s.prenume);
            (*k)++;
        }
     }
     return nota_maxima;
}

int main()
{
    FILE *f;
    f=fopen("Problema9.dat", "wb");
    if(f==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    printf("Cati studenti sunt?");
    int n;
    scanf("%d", &n);
    studenti s;

    //citire informatii--scriere in fisier

    for(int i=0;i<n;i++)
    {
        printf("\nprenume: ");
        getchar();
        gets(s.prenume);
        printf("sex: ");
        scanf("%c", &s.sex);
        printf("nota: ");
        scanf("%f", &s.nota);

        fwrite(&s, sizeof(studenti), 1, f);
    }
    fclose(f);
    
    //citire informatii din fisier

    f=fopen("Problema9.dat", "rb");
    if(f==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    for(int i=0;i<n;i++)
    {
        fread(&s,sizeof(studenti), 1, f);
        printf("\n%s\n%c\n%.2f", s.prenume, s.sex, s.nota);
    }
    fclose(f);

    //adaugare info in fisier
    int n1;
    printf("\nCati studenti doriti sa adaugati? ");
    scanf("%d", &n1);
    f=fopen("Problema9.dat", "ab");
    if(f==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    for(int i=0;i<n1;i++)
    {
         printf("\nprenume: ");
        getchar();
        gets(s.prenume);
        printf("sex: ");
        scanf("%c", &s.sex);
        printf("nota: ");
        scanf("%f", &s.nota);

        fwrite(&s, sizeof(studenti), 1, f); 
    }
    fclose(f);

    //calcul medie varsta

    int n2=n+n1;
    float medie=0;

    f=fopen("Problema9.dat", "rb");
    if(f==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }

    for(int i=0;i<n2;i++)
    {
        fread(&s,sizeof(studenti), 1, f);
        medie+=s.nota;
    }
    medie=medie/n2;
    printf("\nMedia de note a grupului de studenti este %.2f", medie);
    
    fclose(f);

    //verificare existenta
    printf("\nALegeti criteriu selectare: prenume/nota\n");
    char criteriu[10];
    scanf("%s", criteriu);
    f=fopen("Problema9.dat", "rb");
        if(f==NULL)
        {
            printf("fisierul nu a putut fi deschis");
            exit(1);
        }
    if(strcmp(criteriu,"prenume")==0)
    {
        
        char prenume[40];
        printf("\nIntroduceti numele pe care vreti sa-l cautati: ");
        getchar();
        gets(prenume);
        
        //parcurgere
        int ok=0;
        for(int i=0;i<n2;i++)
        {
            fread(&s,sizeof(studenti),1,f);
            if(strcmp(s.prenume,prenume)==0)
            {
                ok=1;
                printf("\nPersoana %s a fost gasita.", prenume);
                break;
            }
        }
        if(ok==0)
        {
            printf("\n%s nu a fost gasit.", prenume);
        }
    }
    else if(strcmp(criteriu,"nota")==0)
    {
        float nota;
        printf("\nIntroduceti nota pe care vreti sa o cautati: ");
        getchar();
        scanf("%f", &nota);

        //parcurgere
        int ok=0;
        for(int i=0;i<n2;i++)
        {
            fread(&s,sizeof(studenti),1,f);
            if(s.nota==nota)
            {
                ok=1;
                printf("\nNota %.2f a fost gasita.", nota);
                break;
            }
        }
        if(ok==0)
        {
            printf("\nNota %.2f nu a fost gasita.", nota);
        }
    }

    //nota max

    fseek(f,0,SEEK_SET);
    char persoane[50][50];
    int k;
    float max=nota_max(s,f,&n2,persoane,&k);
    printf("\nNota maxima este %.2f. ", max);
    printf("Persoanele care au obtinut nota maxima sunt:\n");
    for(int i=0; i<k;i++)
    {
        printf(" \n%s", persoane[i]);
    }
    fclose(f);


    //construire


    f=fopen("Problema9.dat", "rb");
    if(f==NULL)
    {
        printf("fisierul nu a putut fi deschis");
        exit(1);
    }
    FILE *fete, *baieti;
    fete=fopen("fete.dat", "wb");
    if(fete==NULL)
    {
        printf("fete.dat nu a putut fi deschis");
        exit(1);
    }
    baieti=fopen("baieti.dat", "wb");
    if(baieti==NULL)
    {
        printf("baieti.dat nu a putut fi deschis");
        exit(1);
    }
    int kf=0, kb=0;
    for(int i=0;i<n2;i++)
    {
    fread(&s,sizeof(studenti),1,f);
    if(s.sex=='f'||s.sex=='F')
    {
        fwrite(&s,sizeof(studenti),1,fete);
        kf++;
    }
    else if(s.sex=='m'||s.sex=='M')
    {
        fwrite(&s,sizeof(studenti),1,baieti);
        kb++;
    }
    }
    fclose(f);
    fclose(fete);
    fclose(baieti);

    //ordonare 

    fete=fopen("fete.dat", "rb");
    if(fete==NULL)
    {
        printf("fete.dat nu a putut fi deschis");
        exit(1);
    }
    baieti=fopen("baieti.dat", "rb");
    if(baieti==NULL)
    {
        printf("baieti.dat nu a putut fi deschis");
        exit(1);
    }
    //ordonare fete
    studenti *sf=malloc(kf*sizeof(studenti));
    studenti temp;
    fread(sf,sizeof(studenti),kf,fete);
    for(int i=0;i<kf-1;i++)
    {
        for(int j=i;j<kf;j++)
        {
            if(sf[i].nota>sf[j].nota)
            {
                temp=sf[i];
                sf[i]=sf[j];
                sf[j]=temp;
            }
        }
    }
    fclose(fete);
    fete=fopen("fete.dat", "wb");
    if(fete==NULL)
    {
        printf("fete.dat nu a putut fi deschis");
        exit(1);
    }
    fwrite(sf,sizeof(studenti),kf,fete);
    fclose(fete);
    free(sf);

    //ordonare baieti
    studenti *sb=malloc(kb*sizeof(studenti));
    fread(sb, sizeof(studenti), kb, baieti);
    for(int i=0;i<kb-1;i++)
    {
        for(int j=i;j<kb;j++)
        {
            if(strcmp(sb[i].prenume,sb[j].prenume)<0)
            {
                temp=sb[i];
                sb[i]=sb[j];
                sb[j]=temp;
            }
        }
    }
    fclose(baieti);
    baieti=fopen("baieti.dat", "wb");
    if(baieti==NULL)
    {
        printf("baieti.dat nu a putut fi deschis");
        exit(1);
    }
    fwrite(sb,sizeof(studenti), kb,baieti);
    fclose(baieti);
    free(sb);

    //suplimentar
    ///citire fisiere ordonate

    fete=fopen("fete.dat", "rb");
    if(fete==NULL)
    {
        printf("fete.dat nu a putut fi deschis");
        exit(1);
    }
    printf("\nfete.dat ordonat: \n");
    for(int i=0;i<kf;i++)
    {
        fread(&s,sizeof(studenti),1,fete);
        printf("\n%s\n%c\n%.2f", s.prenume, s.sex, s.nota);
    }
    fclose(fete);

    baieti=fopen("baieti.dat", "rb");
    if(baieti==NULL)
    {
        printf("baieti.dat nu a putut fi deschis");
        exit(1);
    }
    printf("\nbaieti.dat ordonat:\n");
    for(int i=0;i<kb;i++)
    {
        fread(&s,sizeof(studenti), 1,baieti);
        printf("\n%s\n%c\n%.2f", s.prenume, s.sex, s.nota);

    }
    fclose(baieti);

    return 0;

}