
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


char first[50];
char second[50];
char third[50];
char four[50];

char PlaySong[40]="Playing";

char calan[50];
char yildiz[6]="*****";
char gec[50];

FILE *dosya;
FILE *doss;

struct node {

    char data[50];
    struct node *next;
    struct node *prev;

};


struct node* start=NULL;


struct node* dugumOlustur(char* veri)
{
    struct node* yeniDugum = (struct node*)malloc(sizeof(struct node));
    strcpy(yeniDugum -> data, veri);
    yeniDugum -> next = NULL;
    yeniDugum -> prev = NULL;

    return yeniDugum;
}

 int sayac = 0;
    int sayac2=0;
    int sayac3=0;

int main()
{




    char kontrol[30];
    char baska[30];

    doss = fopen("input.txt","a");
    fclose(doss);

    doss = fopen("output.txt","w");
    fclose(doss);

     if((dosya = fopen("input.txt","r")) == NULL)
       {
       printf("dosya acilamdi");
       return 1;
       }

        while(!feof(dosya))
            {
                fscanf(dosya,"%s ",first);

                if(!strcmp(first,"InsertSong"))
                {
                    fscanf(dosya,"%s %s\n",second,third);

                    InsertSong(second,third);
                }
                else if(!strcmp(first,"MoveSong"))
                {
                    fscanf(dosya,"%s %s %s\n",second,third,four);

                    MoveSong(second,third,four);
                }
                 else if(!strcmp(first,"RemoveSong"))
                {
                    fscanf(dosya,"%s\n",third);

                    RemoveSong(third);
                }
                 else if(!strcmp(first,"PrintPlaylist"))
                {
                    fscanf(dosya,"%s\n",second);
                    PrintPlaylist(second);
                }
                else if(!strcmp(first,"PlaySong"))
                {
                    fscanf(dosya,"%s\n",second);

                    Playsong(second,sayac,sayac2,sayac3);

                }
                else if(!strcmp(first,"ReversePlaylist"))
                {

                    ReversePlaylist();

                }
            }
            fclose(dosya);
    return 0;
}


void InsertSong(char* second, char* third)//Sarki ekleme fonksiyonu
{
    doss = fopen("output.txt","a");


    if(!strcmp(second,"H"))//Basa ekleme
    {

       struct node* basaEklenecek = dugumOlustur(third);

        if(start == NULL)
        {

            start = basaEklenecek;
            return;
        }

        start -> prev = basaEklenecek;
        basaEklenecek -> next = start;
        start = basaEklenecek;


    }
    else if(!strcmp(second,"T"))//Sona ekleme
    {


        struct node* sonaEklenecek = dugumOlustur(third);
        if(start == NULL)
        {
            start = sonaEklenecek;

        }
        else
        {


        struct node* temp = start;
        if(start==NULL)
        {
            return;
        }
        while (temp-> next != NULL)
        {
            temp = temp->next;
        }

        sonaEklenecek ->prev = temp;
        temp -> next = sonaEklenecek;

        }


    }


    fclose(doss);


}

void MoveSong(char* second, char* third, char* four)//Sarki tasima fonksiyonu
{
    doss = fopen("output.txt","a");
    struct node* onceki1=NULL;
    struct node* onceki2=NULL;
    struct node* sonraki1=NULL;
    struct node* sonraki2=NULL;
    struct node* temp1 = start;
    struct node* temp2 = start;

    while(temp1 != NULL)
    {
        if(!strcmp(temp1-> data ,four))
        {
            onceki1 = temp1->prev;
            sonraki1=temp1->next;
            break;
        }
        temp1 = temp1-> next;
    }

    while(temp2 != NULL)
    {
        if(!strcmp(temp2-> data ,third))
        {
            onceki2 = temp2->prev;
            sonraki2=temp2->next;
            break;
        }
        temp2 = temp2-> next;
    }


    if(!strcmp(second,"B"))
    {
        if(start == NULL)
        {



        }
        else if (!strcmp(start -> data ,four))
        {
            temp2->prev=onceki1;
            temp2->next=temp1;
            start=temp2;

            if(sonraki2==NULL){

            }else{
                sonraki2->prev=onceki2;
            }
            if(onceki2==NULL){
                sonraki2->prev=NULL;
                start=sonraki2;
            }else{
                onceki2->next=sonraki2;
            }
        }
        else
        {
            onceki1->next=temp2;
            temp2->prev=onceki1;
            temp2->next=temp1;
            temp1->prev=temp2;

            if(sonraki2==NULL){

            }else{
                sonraki2->prev=onceki2;
            }
            if(onceki2==NULL){
                sonraki2->prev=NULL;
                start=sonraki2;
            }else{
                onceki2->next=sonraki2;
            }
        }
    }

    else if(!strcmp(second,"A"))
    {

        if(start == NULL)
        {


        }
        else if (temp1->next==NULL)
        {
            temp2->prev=temp1;
            temp2->next=NULL;
            temp1->next=temp2;

            if(sonraki2==NULL){

            }else{
                sonraki2->prev=onceki2;
            }
            if(onceki2==NULL){
                sonraki2->prev=NULL;
                start=sonraki2;
            }else{
                onceki2->next=sonraki2;
            }
        }
        else
        {
            temp2->prev=temp1;
            temp2->next=sonraki1;
            temp1->next=temp2;
            sonraki1->prev=temp2;

            if(sonraki2==NULL){

            }else{
                sonraki2->prev=onceki2;
            }
            if(onceki2==NULL){
                sonraki2->prev=NULL;
                start=sonraki2;
            }else{
                onceki2->next=sonraki2;
            }
        }

    }

    fclose(doss);
}

void RemoveSong(char* third)//Sarki silmee fonksiyonu
{
    char uyarii[40]="Cannot Remove The Playing Song";
    struct node* temp = start;
    if(!strcmp(calan,third))
    {
        doss = fopen("output.txt","a");
        fprintf(doss,"%s\n",uyarii);
        fprintf(doss,"%s\n",yildiz);
        fclose(doss);
    }


    else if(start->next==NULL && start->prev==NULL)
    {


        start=NULL;
    }
    else
    {

        if(start==NULL)
        {
            return ;
        }
        while(temp->next!=NULL)
        {
            if(!strcmp(temp->data , third)){break;}
            temp = temp->next;
        }
        struct node* sonraki = temp -> next;
        struct node* onceki = temp-> prev;
        if(sonraki==NULL){
            onceki -> next = NULL;
        }
        else if(onceki==NULL){
            sonraki -> prev = NULL;
            start=sonraki;
        }
        else{
            onceki -> next = sonraki;
            sonraki -> prev = onceki;
        }
        free(temp);

    }
}

void PrintPlaylist(char* second)//Liste yazdirma fonksiyonu
{

doss = fopen("output.txt","a");



    char uyarprint[40]="No Songs To Print";

    if(start==NULL)
    {

        fprintf(doss,"%s\n",uyarprint);
        fprintf(doss,"%s\n",yildiz);
    }


    else if(!strcmp(second,"F"))
    {

        struct node* temp = start;
        if(start==NULL)
        {
            return;
        }
        while (temp != NULL)
        {
            strcpy(gec,temp->data);
            fprintf(doss,"%s\n",gec);

            temp = temp->next;
        }
        fprintf(doss,"%s\n",yildiz);
    }
    else if(!strcmp(second,"R"))
    {
        struct node* temp=start;
        if(start==NULL)
        {
            return;
        }


        while (temp->next != NULL)
        {

            temp = temp->next;

        }


        if(start==NULL)
        {
            return;
        }


        while(temp!=NULL)
        {

            strcpy(gec,temp->data);
            fprintf(doss,"%s\n",gec);
            temp=temp->prev;
        }

        fprintf(doss,"%s\n",yildiz);


    }

fclose(doss);
}


void Playsong(char* second)//Sarki calma fonksiyonu
{


    doss = fopen("output.txt","a");

    char uyar[50]="No Songs To Play";
    struct node* temp = start;
    if(temp==NULL)
    {
        fprintf(doss,"%s\n",uyar);
        fprintf(doss,"%s\n",yildiz);

    }

    else if(sayac == 0)
    {


        if(!strcmp(second,"N"))
        {


             struct node* temp = start;



                strcpy(gec,temp->data);
                fprintf(doss,"%s\t%s\n",PlaySong,gec);
                fprintf(doss,"%s\n",yildiz);
                strcpy(calan,temp->data);
                temp = temp->next;
                sayac2++;

        }
        else
        {



            struct node* temp = start;
            if(start==NULL)
            {
                return;
            }

            while (temp != NULL)
            {


                if(temp->next == NULL)
                {

                    strcpy(gec,temp->data);
                    fprintf(doss,"%s\t%s\n",PlaySong,gec);
                    fprintf(doss,"%s\n",yildiz);
                    strcpy(calan,temp->data);

                }
                temp = temp->next;
            }
            sayac3++;



        }
        sayac++;
    }
    else
    {
        if(!strcmp(second,"N"))
        {

            struct node* temp = start;

            if(start==NULL)
            {
                return;
            }
            while(temp != NULL )
            {
                if(!strcmp(temp,calan))
                {
                    if(temp->next==NULL)
                    {
                        strcpy(calan,start);

                    }
                    else
                    {
                        strcpy(calan,temp->next);

                    }
                    break;
                }
                temp=temp->next;
            }
            fprintf(doss,"%s\t%s\n",PlaySong,calan);
            fprintf(doss,"%s\n",yildiz);




        }
        else
        {

            struct node* temp = start;

             if(start==NULL)
             {
                return;
             }
             while(temp != NULL)
             {
                 if(!strcmp(temp,calan))
                 {

                     if(temp->next==NULL && temp->prev == NULL)
                     {
                         strcpy(temp,calan);
                         fprintf(doss,"%s\t%s\n",PlaySong,calan);
                        fprintf(doss,"%s\n",yildiz);

                     }


                     else if(temp->prev==NULL)
                     {

                          if(start==NULL)
                          {
                            return;
                          }
                          while(temp->next!=NULL)
                          {

                              temp=temp->next;
                          }

                            strcpy(calan,temp);
                            fprintf(doss,"%s\t%s\n",PlaySong,calan);
                            fprintf(doss,"%s\n",yildiz);

                     }
                     else if(temp->prev != NULL)
                     {
                        strcpy(calan,temp->prev);
                        fprintf(doss,"%s\t%s\n",PlaySong,calan);
                        fprintf(doss,"%s\n",yildiz);
                     }

                 }

                 temp=temp->next;
             }


        }

        sayac++;
    }



    fclose(doss);
}


void ReversePlaylist()//Listeyi ters donderme fonksiyonu
{
doss = fopen("output.txt","a");

    struct node *tmp = NULL;
    if(start==NULL)
    {
        return 0;
    }
   while(start->next != NULL)
   {
       tmp =start->next;
       start-> next = start-> prev;
       start->prev = tmp;
       start=tmp;
   }

   tmp= start->next;
   start->next = start->prev;
   start->prev = tmp;


fclose(doss);
}
