#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "header.h"



void printShortesRoute(int *cntr_ptr, cityTemp *citys)
{
    printf("\n\n\n#Kuerzeste Route: Zentrale");

    for(int i = 0; i < *cntr_ptr; i++)
    {
        printf("  => ");
        printf("%s", citys[i].city);
    }

    printf("  => Zentrale\n\n\n");
}

cityTemp* nearestNeighbor(int *cntr_ptr, cityTemp *citys)
{
    float distance = 10000;
    float shortestDistance = 10000;
    int nextInList = 0;
    float xCoordinate = 0;
    float yCoordinate = 0;
    float totalDistance = 0;

    cityTemp *citys_sorted = malloc(*cntr_ptr*sizeof(cityTemp));


    for(int i = 0; i < *cntr_ptr; i++)                     //nächste Stadt zur Zentrale (Wien)
    {
        xCoordinate = 111.3 * (citys[i].lat - 48.2);
        yCoordinate = 71.5 * (citys[i].lng - 16.3666);

        distance = sqrt(pow(xCoordinate, 2.0) + pow(yCoordinate, 2.0));

        if(distance > 0 && distance < shortestDistance)
                {
                    shortestDistance = distance;
                    nextInList = i;
                }
    }


    strcpy(citys_sorted[0].city, citys[nextInList].city);
    citys_sorted[0].lat = citys[nextInList].lat;
    citys_sorted[0].lng = citys[nextInList].lng;
    strcpy(citys_sorted[0].country, citys[nextInList].country);
    strcpy(citys_sorted[0].iso2, citys[nextInList].iso2);
    strcpy(citys_sorted[0].iso3, citys[nextInList].iso3);
    strcpy(citys_sorted[0].admin_name, citys[nextInList].admin_name);
    strcpy(citys_sorted[0].capital, citys[nextInList].capital);
    citys_sorted[0].population = citys[nextInList].population;
    citys_sorted[0].population = citys[nextInList].population;

    citys[nextInList].id = 0;

    shortestDistance = 100000;


    for(int i = 0; i < *cntr_ptr; i++)
    {
        for(int j = 0; j <  *cntr_ptr; j++)
        {


            if(citys[j].id > 0)
            {
                if(citys[j].id == 1040261752) citys[j].lat = 48.3;

                xCoordinate = 111.3 * (citys[j].lat - citys_sorted[i].lat);
                yCoordinate = 71.5 * (citys[j].lng - citys_sorted[i].lng);

                distance = sqrt(pow(xCoordinate, 2.0) + pow(yCoordinate, 2.0));

                //printf("Abstand %s - %s = %f\n", citys_sorted[i].city, citys[j].city, distance);

                if(distance > 0 && distance < shortestDistance)
                {
                    shortestDistance = distance;
                    nextInList = j;
                    totalDistance += shortestDistance;
                }
            }
        }

        strcpy(citys_sorted[i+1].city, citys[nextInList].city);
        citys_sorted[i+1].lat = citys[nextInList].lat;
        citys_sorted[i+1].lng = citys[nextInList].lng;
        strcpy(citys_sorted[i+1].country, citys[nextInList].country);
        strcpy(citys_sorted[i+1].iso2, citys[nextInList].iso2);
        strcpy(citys_sorted[i+1].iso3, citys[nextInList].iso3);
        strcpy(citys_sorted[i+1].admin_name, citys[nextInList].admin_name);
        strcpy(citys_sorted[i+1].capital, citys[nextInList].capital);
        citys_sorted[i+1].population = citys[nextInList].population;
        citys_sorted[i+1].population = citys[nextInList].population;

        citys[nextInList].id = 0;

        shortestDistance = 10000;
    }

    free(citys);

    return citys_sorted;
}

void readcsv(cityTemp *searchCity, int *cntr_ptr, char cityName[])
{


    int position = *cntr_ptr;


    cityTemp dataTemp;

    char puffer[200];
    char delimiter[]="\"";
    char *puffer_ptr;

    int dataEntry=0;
    char *compare=",";
    int emptyField=0;
    int letterCount=0;
    char compareCity[50];

    FILE* myfile;
    char filename[20]="worldcities.csv";



    myfile=fopen(filename,"r");
    if (myfile == NULL)
    {
        printf("Datei nicht gefunden");
        return;
    }
    else
    {
        fgets(puffer,200,myfile);

        while(NULL!=fgets(puffer,200,myfile))
        {

            puffer_ptr = strtok(puffer, delimiter);
            dataEntry=0;

            while(puffer_ptr != NULL)
            {
                emptyField=0;
                while (strcmp (puffer_ptr,compare) == 0)
                {
                    if(emptyField>0)
                    {
                        dataEntry++;
                    }
                    emptyField++;
                    puffer_ptr = strtok(NULL, delimiter);
                }
                switch(dataEntry)
                {
                    case 0: strcpy(dataTemp.city,puffer_ptr);
                    break;
                    case 1: strcpy(dataTemp.city_ascii,puffer_ptr);
                    break;
                    case 2: dataTemp.lat = atof(puffer_ptr);
                    break;
                    case 3: dataTemp.lng = atof(puffer_ptr);
                    break;
                    case 4: strcpy(dataTemp.country,puffer_ptr);
                    break;
                    case 5: strcpy(dataTemp.iso2,puffer_ptr);
                    break;
                    case 6: strcpy(dataTemp.iso3,puffer_ptr);
                    break;
                    case 7: strcpy(dataTemp.admin_name,puffer_ptr);
                    break;
                    case 8: strcpy(dataTemp.capital,puffer_ptr);
                    break;
                    case 9: dataTemp.population = atol(puffer_ptr);
                    break;
                    case 10: dataTemp.id = atol(puffer_ptr);
                    break;
                }
                if(dataEntry<10)
                {
                    dataEntry++;
                    puffer_ptr = strtok(NULL, delimiter);
                }
                else
                {
                    puffer_ptr = NULL;
                }
            }
            letterCount=0;
            while(cityName[letterCount]!='\0' && letterCount<50)
            {
                if(cityName[letterCount] >= 'a' && cityName[letterCount] <= 'z')
                {
                    cityName[letterCount] -= 32;
                }
                letterCount++;
            }
            letterCount=0;
            strcpy(compareCity,dataTemp.city);
            while(compareCity[letterCount]!='\0' && letterCount<50)
            {
                if(compareCity[letterCount] >= 'a' && compareCity[letterCount] <= 'z')
                {
                    compareCity[letterCount] -= 32;
                }
                letterCount++;
            }


            if(strcmp(compareCity,cityName)==0)
            {

                searchCity[position] = dataTemp;

                position++;

                break;
            }

        }
        if(position == *cntr_ptr)
        {
            printf("\nKeine Stadt gefunden!\n");
        }
    }
    *cntr_ptr = position;
    fclose(myfile);
}

cityTemp* bubble(cityTemp *citys, int *cntr_ptr)
{
   int i;
   int citysReverse=*cntr_ptr-1;
   cityTemp temp;

   while(citysReverse>0)
   {
      for(i = 0; i < citysReverse; i++)
      {
          if(strcmp(citys[i].city_ascii,citys[i+1].city_ascii)>0)
          {
             temp=citys[i+1];
             citys[i+1]=citys[i];
             citys[i]=temp;
          }
      }
      citysReverse--;
   }
   printf("\nbubblesort, sorted by name:\n");
   for(i = 0; i < *cntr_ptr; i++)
   {
       printf("\ncity: %-20s population: %8ld",citys[i].city,citys[i].population);
   }

   citysReverse=*cntr_ptr-1;
   while(citysReverse>0)
   {
      for(i = 0; i < citysReverse; i++)
      {
          if(citys[i].population > citys[i+1].population)
          {
             temp=citys[i+1];
             citys[i+1]=citys[i];
             citys[i]=temp;
          }
      }
      citysReverse--;
   }
   printf("\n\nbubblesort, sorted by population:\n");
   for(i = 0; i < *cntr_ptr; i++)
   {
       printf("\ncity: %-20s population: %8ld",citys[i].city,citys[i].population);
   }
   return citys;
}

void quicksort_name(cityTemp *links, cityTemp *rechts)
{
   cityTemp *ptr1 = links;
   cityTemp *ptr2 = rechts;
   cityTemp w;
   cityTemp *x;
   cityTemp ptr1_element = *ptr1;
   cityTemp ptr2_element = *ptr2;

   x = (links+(rechts-links)/2);
   cityTemp x_element = *x;

   do
   {
      while(strcmp(ptr1_element.city_ascii,x_element.city_ascii) < 0)
      {
          ptr1++;
          ptr1_element = *ptr1;
      }
      while(strcmp(ptr2_element.city_ascii,x_element.city_ascii) > 0)
      {
          ptr2--;
          ptr2_element = *ptr2;
      }
      if(ptr1 > ptr2)
      {
          break;
      }
      w = *ptr1;
      *ptr1 = *ptr2;
      *ptr2 = w;

      ptr1++;
      ptr1_element = *ptr1;
      ptr2--;
      ptr2_element = *ptr2;

   } while(ptr1 <= ptr2);
   if(links < ptr2)  quicksort_name(links, ptr2);
   if(ptr1 < rechts) quicksort_name(ptr1, rechts);
}

void quicksort_pop(cityTemp *links, cityTemp *rechts)
{
   cityTemp *ptr1 = links;
   cityTemp *ptr2 = rechts;
   cityTemp w;
   cityTemp *x;
   cityTemp ptr1_element = *ptr1;
   cityTemp ptr2_element = *ptr2;

   x = (links+(rechts-links)/2);
   cityTemp x_element = *x;

   do
   {
      while(ptr1_element.population < x_element.population)
      {
          ptr1++;
          ptr1_element = *ptr1;
      }
      while(ptr2_element.population > x_element.population)
      {
          ptr2--;
          ptr2_element = *ptr2;
      }
      if(ptr1 > ptr2)
      {
          break;
      }
      w = *ptr1;
      *ptr1 = *ptr2;
      *ptr2 = w;

      ptr1++;
      ptr1_element = *ptr1;
      ptr2--;
      ptr2_element = *ptr2;

   } while(ptr1 <= ptr2);
   if(links < ptr2)  quicksort_pop(links, ptr2);
   if(ptr1 < rechts) quicksort_pop(ptr1, rechts);
}

// gibt ein pointer in den heap zurück in dem ein dynamisch allokierter Datensatz von Städten steht
// es muss ein pointer zu einem counter übergeben werden der die Anzahl der Städte mitzählt
cityTemp* user_input_to_city_Struct(int *cntr4new)
{


    int cntr = 0;

    int running = 1;
    char choice;

    cityTemp *temp_city = calloc(1, sizeof(cityTemp));

    while(running)
    {


        printf("Geben Sie eine Stadt ein: ");
        fgets(temp_city[cntr].city, 50, stdin);

        temp_city[cntr].city[strlen(temp_city[cntr].city) - 1] = '\0';      // nimmt das '\n' am ende vom String weg und macht ein \0 draus

        printf("In welchem Land liegt %s: ", temp_city[cntr].city);
        fgets(temp_city[cntr].country, 50, stdin);

        temp_city[cntr].country[strlen(temp_city[cntr].country) - 1] = '\0';

        printf("An welchen Breitengrad liegt %s: ", temp_city[cntr].city);
        scanf("%f", &temp_city[cntr].lat);

        printf("An welchem Laengengrad liegt %s: ", temp_city[cntr].city);
        scanf("%f", &temp_city[cntr].lng);

        printf("Wie viele Menschen leben in %s: ", temp_city[cntr].city);
        scanf("%ld", &temp_city[cntr].population);

        getchar();                                                          // da sonst die nächste Einlesefnkt nur '\n' liest

        printf("Was ist der ascii Code von %s: ", temp_city[cntr].city);
        fgets(temp_city[cntr].city_ascii, 50, stdin);

        temp_city[cntr].city_ascii[strlen(temp_city[cntr].city_ascii) - 1] = '\0';

        printf("Was ist der ISO2 Code von %s: ", temp_city[cntr].city);
        fgets(temp_city[cntr].iso2, 4, stdin);

        temp_city[cntr].iso2[strlen(temp_city[cntr].iso2) - 1] = '\0';

        printf("Was ist der ISO3 Code von %s: ", temp_city[cntr].city);
        fgets(temp_city[cntr].iso3, 5, stdin);

        temp_city[cntr].iso3[strlen(temp_city[cntr].iso3) - 1] = '\0';

        printf("Was ist der Admin Name von %s: ", temp_city[cntr].city);
        fgets(temp_city[cntr].admin_name, 50, stdin);

        temp_city[cntr].admin_name[strlen(temp_city[cntr].admin_name) - 1] = '\0';

        printf("Capital von %s: ", temp_city[cntr].city);
        fgets(temp_city[cntr].capital, 50, stdin);

        temp_city[cntr].capital[strlen(temp_city[cntr].capital) - 1] = '\0';

        printf("Was ist die ID von %s: ", temp_city[cntr].city);
        scanf("%ld", &temp_city[cntr].id);

        printf("%s wurde zur Datenbank hinzugefuegt\n",temp_city[cntr].city);


        printf("\n\nWollen sie noch eine Stadt zur Datenbank hinzufuegen? (Y/N) ");
        scanf(" %c", &choice);
        getchar();
        if (choice == 'n' || choice == 'N') break;

        cntr++;

        temp_city = realloc(temp_city, sizeof(cityTemp)*(cntr+1));

        printf("\n\n");

    }

    *cntr4new = (cntr+1);

    return temp_city;
}

// bekommt einen Pointer zue einenm Datensatz von Städten den er dann in ein File schreibt
// der counter bestimmt wieviele Städte im Datensatz sind
void city_struct_to_csv(cityTemp* citys, int cntr)
{

    char filename[100] = "newfile.csv"; //"worldcities.csv";



    printf("\nGeben Sie den Dateinamen inkl. Dateiendung ein. \n(Sollte die Datei nicht existieren wird eine neue angelegt)\nDateiname: ");
    fgets(filename, 100, stdin);
    filename[strlen(filename) - 1] = '\0';          // nimmt das '\n' am ende vom String weg und macht ein \0 draus

    FILE *fileptr;

    fileptr = fopen(filename,"a");

    if (fileptr == NULL)
    {
        printf("Datei nicht gefunden");
        return;
    }


    //printed die Werte aus der Structarry in eine CSV Datei
    for(int i = 0; i < cntr; i++)
    {

        //"city","city_ascii","lat","lng","country","iso2","iso3","admin_name","capital","population","id"

        fprintf(fileptr, "%s,", citys[i].city);
        fprintf(fileptr, "\"%s\",", citys[i].city_ascii);
        fprintf(fileptr, "\"%f\",", citys[i].lat);
        fprintf(fileptr, "\"%f\",", citys[i].lng);
        fprintf(fileptr, "\"%s\",", citys[i].country);
        fprintf(fileptr, "\"%s\",", citys[i].iso2);
        fprintf(fileptr, "\"%s\",", citys[i].iso3);
        fprintf(fileptr, "\"%s\",", citys[i].admin_name);
        fprintf(fileptr, "\"%s\",", citys[i].capital);
        fprintf(fileptr, "\"%ld\",", citys[i].population);
        fprintf(fileptr, "\"%ld\"", citys[i].id);


        fprintf(fileptr, "\n");

    }

    fclose(fileptr);

}

//printf the main menu
int menu()
{
    int choice = 0;

    printf("\n* * * * * * * * * * * * * * * * * * *\n");
    printf("*                                   *\n");
    printf("*  Willkommen zu Travelling C-AG!   *\n");
    printf("*                                   *\n");
    printf("* * * * * * * * * * * * * * * * * * *\n\n");


    printf("Wenn Sie Staedte nach ihrem Namen sortieren wollen..............1\n");
    printf("Wenn Sie die kuerzeste Route zwischen Staedte wissen wollen.....2\n");
    printf("Wenn Sie eine neuen Stadt zur Datenbank hinzufuegen wollen......3\n");
    printf("Wenn Sie das Programm beeden wollen.............................0\n\n");
    scanf("%1d", &choice);
    printf("\n\n");


    return choice;
}

cityTemp* cityInput(int *cntr_ptr, cityTemp *citys)
{
    char temp[50];

    citys = realloc(citys, 2*sizeof(cityTemp));


    printf("Geben sie eine Stadt ein: ");
    fgets(temp, 50, stdin);                                     // fgets damit auch Abstände eingelesen werden
    temp[strlen(temp) - 1] = '\0';                              // löscht den Zeilenumbruch am Ende des Strings (falls vorhanden)

    readcsv(citys, cntr_ptr, temp);                             // holt sich die Daten aus der CSV Datei

    printf("Geben sie noch eine Stadt ein: ");
    fgets(temp, 50, stdin);
    temp[strlen(temp) - 1] = '\0';

    readcsv(citys, cntr_ptr, temp);

    // fragt solange Städte ab bis 0 eingegeben wird oder der counter 100 ereicht
    while(temp[0] != '0')
    {

        printf("Geben sie noch eine Stadt ein (oder '0' wenn Sie fertig sind): ");
        fgets(temp, 50, stdin);
        temp[strlen(temp) - 1] = '\0';

        if(temp[0] != '0')
        {

            citys = realloc(citys, (*cntr_ptr+1)*sizeof(cityTemp));
            readcsv(citys, cntr_ptr, temp);

            continue;
        }

        else if(temp[0] == '0') break;

    }

   return citys;
}

