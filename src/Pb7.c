#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct data{
    char luna[50];
    int an;
};
struct AUTOMOBIL{
    char marca[50];
    char carburant;
    char model[50];
    struct data data_fabricatie;
};

void citire_automobile(struct AUTOMOBIL *evidenta, int *n)
{
for(int i=0;i<(*n);i++)
{   
    printf("\nautomobil %d", i);
    printf("\nmarca: ");
    gets(evidenta[i].marca);
    printf("carburant (B/M): ");
    scanf(" %c", &evidenta[i].carburant);
    getchar();
    printf("model: ");
    gets(evidenta[i].model);
    printf("data fabricatiei: ");
    scanf("%s %d", evidenta[i].data_fabricatie.luna, &evidenta[i].data_fabricatie.an);
    getchar();

}

}

void scriere(struct AUTOMOBIL *evidenta, int *n, FILE *f)
{
    for(int i=0;i<(*n);i++)
{
    fprintf(f, "\n%s", evidenta[i].marca);
    fprintf(f, "\n%c", evidenta[i].carburant);
    fprintf(f, "\n%s", evidenta[i].model);
    fprintf(f, "\n%s %d", evidenta[i].data_fabricatie.luna, evidenta[i].data_fabricatie.an);
    fprintf(f, "\n");
}
}

int luna_to_int(char luna[50])
{
    if (strcmp(luna, "ianuarie") == 0) 
    return 1;
    if (strcmp(luna, "februarie") == 0) 
    return 2;
    if (strcmp(luna, "martie") == 0) 
    return 3;
    if (strcmp(luna, "aprilie") == 0) 
    return 4;
    if (strcmp(luna, "mai") == 0) 
    return 5;
    if (strcmp(luna, "iunie") == 0) 
    return 6;
    if (strcmp(luna, "iulie") == 0) 
    return 7;
    if (strcmp(luna, "august") == 0) 
    return 8;
    if (strcmp(luna, "septembrie") == 0) 
    return 9;
    if (strcmp(luna, "octombrie") == 0) 
    return 10;
    if (strcmp(luna, "noiembrie") == 0) 
    return 11;
    if (strcmp(luna, "decembrie") == 0) 
    return 12;

    return 0; // lună invalidă
}

int cautare(char marca[50], char *carburant, FILE *f, int *count)
{   
    struct AUTOMOBIL temp[*count];
    f=fopen("Problema7.txt", "r");
    fseek(f, 0, SEEK_SET);
    int ok=0;
    for(int i=0;i<(*count);i++)
    {
        fscanf(f, " %s", temp[i].marca);
        fscanf(f, " %c", &temp[i].carburant);
        fscanf(f, " %s", temp[i].model);
        fscanf(f, " %s", temp[i].data_fabricatie.luna);
        fscanf(f, " %d", &temp[i].data_fabricatie.an);
        
        if(strcmp(marca,temp[i].marca)==0&&(*carburant)==temp[i].carburant)
        {
            ok=1;
        }
    }
    if(ok==1)
    return 1;
    else 
    return 0;
}
void afisare_ordonata(FILE *f, int *count, struct AUTOMOBIL temp[*count])
{   
    int i=0;
    struct AUTOMOBIL p;
    f=fopen("Problema7.txt", "rt");
    if(f==NULL)
    {
        printf("f nu a putut fi deschis");
        exit(1);
    }
    fseek(f, 0, SEEK_SET);
    while (fscanf(f, "%49s %c %49s %49s %d", p.marca, &p.carburant, p.model, p.data_fabricatie.luna, &p.data_fabricatie.an) == 5)
    {
        if(p.data_fabricatie.an<2021||(p.data_fabricatie.an==2021&&strcmp(p.data_fabricatie.luna,"ianuarie")==0))
        {
            temp[i]=p;
            i++;
        }
    }
    fclose(f);
    *count=i;


}
void ordonare_crescatoare(FILE *f3, FILE *f, int *count, struct AUTOMOBIL ordonat[*count])
{
    
    struct AUTOMOBIL temp;
    for(int i=0;i<(*count);i++)
    {
        fscanf(f, "%s", ordonat[i].marca);
        fscanf(f, " %c", &ordonat[i].carburant);
        fscanf(f, "%s", ordonat[i].model);
        fscanf(f, "%s %d", ordonat[i].data_fabricatie.luna, &ordonat[i].data_fabricatie.an);
    }

    for(int i=0;i<(*count)-1;i++)
    {
        for(int k=i+1;k<(*count);k++)
        {
            if(ordonat[i].data_fabricatie.an>ordonat[k].data_fabricatie.an)
            {
                temp=ordonat[i];
                ordonat[i]=ordonat[k];
                ordonat[k]=temp;
            }
            else if(ordonat[i].data_fabricatie.an==ordonat[k].data_fabricatie.an&&luna_to_int(ordonat[i].data_fabricatie.luna)>luna_to_int(ordonat[k].data_fabricatie.luna))
            {
                 temp=ordonat[i];
                ordonat[i]=ordonat[k];
                ordonat[k]=temp;
            }
        }
    }
    scriere(ordonat, count, f3);
;
}
int main()
{
FILE *f;
f=fopen("Problema7.txt", "w+");
if(f==NULL)
{
    printf("f nu a putut fi deschis");
    return 0;
}

int n;
struct AUTOMOBIL *evidenta;
printf("EVIDENTA AUTO");
printf("\nNumar masini: ");
scanf("%d", &n);
getchar();
evidenta=malloc(n*sizeof(struct AUTOMOBIL));
citire_automobile(evidenta, &n);
scriere(evidenta,&n, f);

fflush(f);
fclose(f);

free(evidenta);

//b)

int noi;
printf("\nCate automobile noi au venit in stoc?");
scanf("%d", &noi);
getchar();
f=fopen("Problema7.txt", "a");
if(f==NULL)
{
    printf("f nu a putut fi deschis");
    return 0;
}
evidenta=malloc(noi*sizeof(struct AUTOMOBIL));
citire_automobile(evidenta,&noi);
scriere(evidenta,&noi, f);
fflush(f);
fclose(f);
int count=n+noi;

//c)

char marca[50];
char carburant;
printf("\nCautare automobil");
printf("\nmarca: ");
scanf("%s", marca);
printf("carburant (B/M): ");
getchar();
scanf("%c", &carburant);
if(cautare(marca,&carburant,f,&count)==1)
{
    printf("\nAutomobilul este regasit in evidenta");
}
else 
{
    printf("Automobilul nu este regasit in evidenta");
}
fclose(f);

//d)
struct AUTOMOBIL temp[count];
afisare_ordonata(f, &count, temp);
printf("\nAutomobile cu vechime mai mare de 5 ani:\n");
for(int k=0;k<count;k++)
{
    printf("\n%s", temp[k].marca);
    printf("\n%c", temp[k].carburant);
    printf("\n%s", temp[k].model);
    printf("\n%s %d", temp[k].data_fabricatie.luna, temp[k].data_fabricatie.an);
    printf("\n");
}

//e)

FILE *f3;

count=n+noi;
struct AUTOMOBIL ordonat[count];
f3=fopen("Problema7-2.txt", "w");
    if(f3==NULL)
    {
        printf("f3 nu a putut fi deschis");
        exit(1);
    }
    f=fopen("Problema7.txt", "r");
    if(f==NULL)
    {
        printf("f nu a putut fi deschis");
        exit(1);
    }
    fseek(f, 0, SEEK_SET);
ordonare_crescatoare(f3,f,&count,ordonat);
/*f3=fopen("Problema7-2.txt", "r");
if(f3==NULL)
{
    printf("f3 nu a putut fi deschis");
    exit(1);
}
 for(int i=0;i<count;i++)
    {
        fgetc(f3);
        fscanf(f3, "%s", ordonat[i].marca);
        fscanf(f3, "%c", &ordonat[i].carburant);
        fscanf(f3, "%s", ordonat[i].model);
        fscanf(f3, "%s %d", ordonat[i].data_fabricatie.luna, &ordonat[i].data_fabricatie.an);
    }
*/
fclose(f);
fclose(f3);
return 0;

}