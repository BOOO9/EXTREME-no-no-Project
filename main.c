#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    char city[50];
    char city_ascii[50];
    float lat;
    float lng;
    char country[50];
    char iso2 [3];
    char iso3 [4];
    char admin_name[50];
    char capital[50];
    long population;
    long id;

}cityTemp;

// unsere Funktionen:

void printShortesRoute();
void nearestNeighbor();
void readcsv();
void city_struct_to_csv();
int menu();
cityTemp* cityInput();



int main()
{

    cityTemp *citys = malloc(sizeof(cityTemp));
    cityTemp *citys_sorted = malloc(sizeof(citys));
//    printf("\n\n\n---%p\n\n\n", *citys);

    int running = 1;
    int cntr = 0;
    int cntr4new = 0;

    while (running == 1)                            //Men� Schleife
    {
        cntr = 0;

        int choice = menu();                        //menu() gibt Zahl von 0-3 zur�ck; 1 = St�dte nach Namen sortieren; 2 = Travelling SP; 3 = St�dte zur CSV hinzuf�gen

        switch(choice)
        {

            case 1:
            {

//                printf("\n\n\n111---%p\n\n\n", *citys);

                citys = cityInput(&cntr, citys);                // liest St�dte in das citys[] Array ein und f�llt das Array mit den Daten aus der CSV

//                printf("\n\n\n111---%p\n\n\n", *citys);
//                printf("\n\n---%d---\n\n",cntr);

                    for(int i = 0; i < cntr; i++)                             // test ob die Daten eingelesen werden
                    {
//                        printf("\n\n---%d---\n\n",cntr);
//                        printf("\n\n\n---%p\n\n\n", *citys);

                        printf("\n\ncity: %s\n",citys[i].city);

                        //printf("cityAscii: %s\n",citys[i].city_ascii);
                        printf("lat: %f\n",citys[i].lat);
                        /*printf("lng: %f\n",citys[i].lng);
                        printf("country: %s\n",citys[i].country);
                        printf("iso2: %s\n",citys[i].iso2);
                        printf("iso3: %s\n",citys[i].iso3);
                        printf("adminName: %s\n",citys[i].admin_name);
                        printf("capital: %s\n",citys[i].capital);
                        printf("population: %ld\n",citys[i].population);
                        printf("id: %ld\n\n",citys[i].id);
*/
                        printf("---------------------------------------------");

                    }



                //system("cls");

                break;

            }

            case 2:
            {


                cityInput(&cntr, citys);

                nearestNeighbor(citys, citys_sorted, cntr);

                printShortesRoute(citys_sorted, cntr);

                for(int i = 1; i < cntr+1; i++)                             // test ob die Daten eingelesen werden
                    {

                        printf("\n\ncity: %s\n",citys_sorted[i].city);

                        printf("---------------------------------------------");

                    }


                //Eingabe von St�dtenamen
                //TSM-Problem

                break;
            }
            case 3:

            {



                break;
            }

            case 0:

                running = 0;
                break;


            default:

                printf("Error");

                running = 0;
                break;

        }


    }

    return 0;

}



void printShortesRoute(cityTemp citys_sorted[101], int entries)
{
    printf("Kuerzeste Route:");

    for(int i = 0; i < entries+2; i++)
    {
        printf("  =>  ");
        printf("%s", citys_sorted[i].city);
    }
}



void nearestNeighbor(cityTemp citys[100], cityTemp citys_sorted[100], int entries)
{

    printf("test\n\ntest\n\ntest\n\n");


    float distance = 1000;
    float shortestDistance = 1000;
    int nextInList = 0;
    float xCoordinate = 0;
    float yCoordinate = 0;
    float totalDistance = 0;


    strcpy(citys_sorted[0].city, "ZentraleWien");
    strcpy(citys_sorted[0].city_ascii, "Vienna");
    citys_sorted[0].lat = 48.2;
    citys_sorted[0].lng = 16.3666;
    strcpy(citys_sorted[0].country, "Austria");
    strcpy(citys_sorted[0].iso2, "AT");
    strcpy(citys_sorted[0].iso3, "AUT");
    strcpy(citys_sorted[0].admin_name, "Wien");
    strcpy(citys_sorted[0].capital, "primary");
    citys_sorted[0].population = 2400000;
    citys_sorted[0].id = 1040261752;




    for(int i = 0; i < entries; i++)
    {
        for(int j = 1; j < entries+1; j++)
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

    strcpy(citys_sorted[nextInList+1].city, citys_sorted[0].city);
    citys_sorted[nextInList+1].lat = citys_sorted[0].lat;
    citys_sorted[nextInList+1].lng = citys_sorted[0].lng;
    strcpy(citys_sorted[nextInList+1].country, citys_sorted[0].country);
    strcpy(citys_sorted[nextInList+1].iso2, citys[0].iso2);
    strcpy(citys_sorted[nextInList+1].iso3, citys[0].iso3);
    strcpy(citys_sorted[nextInList+1].admin_name, citys[0].admin_name);
    strcpy(citys_sorted[nextInList+1].capital, citys[0].capital);
    citys_sorted[nextInList+1].population = citys[0].population;
    citys_sorted[nextInList+1].population = citys[0].population;


    //printf("\nTotal distance = %f\n\n", totalDistance);


}



void readcsv(cityTemp *searchCity, int *cntr_ptr, char cityName[])
{
//    printf("\n\n\n---%p\n\n\n", *searchCity);

    int position = *cntr_ptr;

//    printf("\n\nDer wahre Zaeler ist:%d\n\n",position);

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


//    printf("Geben sie den Dateinamen inkl Endung an: ");
//    gets(filename);
//    printf("Geben sie den Namen der Stadt ein: ");
//    gets(cityName);

    myfile=fopen(filename,"r");
    if (myfile == NULL)
    {
        printf("Datei nicht gefunden");
        return;
    }
    else
    {
        fgets(puffer,200,myfile);
//        for(int i=0;i<6;i++)
        while(NULL!=fgets(puffer,200,myfile))
        {
//            fgets(puffer,200,myfile);
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
//            printf("\n\n%s\n\n",cityName);
//            printf("\n\n%s\n\n",compareCity);

            if(strcmp(compareCity,cityName)==0)
            {
//                printf("\n\n\nNamen sind gleich\n\n\n");

                searchCity[position] = dataTemp;
/*
                printf("city: %s\n",searchCity[position].city);
                printf("cityAscii: %s\n",searchCity[position].city_ascii);
                printf("lat: %f\n",searchCity[position].lat);
                printf("lng: %f\n",searchCity[position].lng);
                printf("country: %s\n",searchCity[position].country);
                printf("iso2: %s\n",searchCity[position].iso2);
                printf("iso3: %s\n",searchCity[position].iso3);
                printf("adminName: %s\n",searchCity[position].admin_name);
                printf("capital: %s\n",searchCity[position].capital);
                printf("population: %ld\n",searchCity[position].population);
                printf("id: %ld\n",searchCity[position].id);
*/

//                printf("\n\n\nin readcsv---%p\n\n\n", *searchCity);
                position++;


//                citys=searchCity;

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




// gibt ein pointer in den heap zur�ck in dem ein dynamisch allokierter Datensatz von St�dten steht
// es muss ein pointer zu einem counter �bergeben werden der die Anzahl der St�dte mitz�hlt
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

        temp_city[cntr].city[strlen(temp_city[cntr].city) - 1] = '\0';    // nimmt das '\n' am ende vom String weg und macht ein \0 draus

        printf("In welchem Land liegt %s: ", temp_city[cntr].city);
        fgets(temp_city[cntr].country, 50, stdin);

        temp_city[cntr].country[strlen(temp_city[cntr].country) - 1] = '\0';

        printf("An welchen Breitengrad liegt %s: ", temp_city[cntr].city);
        scanf("%f", &temp_city[cntr].lat);

        printf("An welchem Laengengrad liegt %s: ", temp_city[cntr].city);
        scanf("%f", &temp_city[cntr].lng);

        printf("Wie viele Menschen leben in %s: ", temp_city[cntr].city);
        scanf("%ld", &temp_city[cntr].population);

        getchar(); // da sonst die n�chste Einlesefnkt nur '\n' liest

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


        printf("\n--------------------------\n\n");
        printf("city: %s\n",temp_city[cntr].city);
        printf("cityAscii: %s\n",temp_city[cntr].city_ascii);
        printf("lat: %f\n",temp_city[cntr].lat);
        printf("lng: %f\n",temp_city[cntr].lng);
        printf("country: %s\n",temp_city[cntr].country);
        printf("iso2: %s\n",temp_city[cntr].iso2);
        printf("iso3: %s\n",temp_city[cntr].iso3);
        printf("adminName: %s\n",temp_city[cntr].admin_name);
        printf("capital: %s\n",temp_city[cntr].capital);
        printf("population: %ld\n",temp_city[cntr].population);
        printf("id: %ld\n",temp_city[cntr].id);



        printf("\n\nWollen sie noch eine Stadt eingeben? (Y/N) ");
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



// bekommt einen Pointer zue einenm Datensatz von St�dten den er dann in ein File schreibt
// der counter bestimmt wieviele St�dte im Datensatz sind

void city_struct_to_csv(cityTemp *citys, int cntr)
{

    char filename[100] = "newfile.csv"; //"worldcities.csv";

    printf("\nWie hei�t die .csv Datei in der Sie die Daten abspeichern wollen? (Sollte die Datei nicht existieren wird eine neue angelegt)\nDateiname: ");
    fgets(filename, 100, stdin);
    filename[strlen(filename) - 1] = '\0';          // nimmt das '\n' am ende vom String weg und macht ein \0 draus

    FILE *fileptr;

    fileptr = fopen(filename,"a");

    if (fileptr == NULL)
    {
        printf("Datei nicht gefunden");
        return;
    }

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



int menu()
{
    int choice = 0;

    printf("* * * * * * * * * * * * * * * * * * *\n");
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
//    int cntr = *cntr_ptr;

//    printf("\n\n\n%d\n\n\n", cntr);

//    printf("\n\n\n---%p\n\n\n", *citys);
    citys = realloc(citys, 5*sizeof(cityTemp));
//    printf("\n\n\n---%p\n\n\n", *citys);

    getchar();                                                  //damit fgets() nicht das vorangegangenen Leerzeichen einliest

    printf("Geben sie eine Stadt ein: ");
    fgets(temp, 50, stdin);                                     // fegts damit auch Abst�nde eingelesen werden
    temp[strlen(temp) - 1] = '\0';                              // l�scht den Zeilenumbruch am Ende des Strings (falls vorhanden)
//    cntr++;

//    printf("\n\n\n%d\n\n\n", cntr);

//    readcsv(citys, cntr, temp);                                 // holt sich die Daten aus der CSV Datei
    readcsv(citys, cntr_ptr, temp);

    printf("Geben sie noch eine Stadt ein: ");
    fgets(temp, 50, stdin);
    temp[strlen(temp) - 1] = '\0';
//    cntr++;

//    printf("\n\n\n%d\n\n\n", cntr);

//    readcsv(citys, cntr, temp);
    readcsv(citys, cntr_ptr, temp);

    // fragt solange St�dte ab bis 0 eingegeben wird oder der counter 100 ereicht
    while(temp[0] != '0')
    {

        printf("Geben sie noch eine Stadt ein (oder '0' wenn Sie fertig sind): ");
        fgets(temp, 50, stdin);
        temp[strlen(temp) - 1] = '\0';

        if(temp[0] != '0')
        {
//            cntr++;

//            citys = realloc(citys, (cntr+1)*sizeof(cityTemp));
//            readcsv(citys, cntr, temp);
            citys = realloc(citys, (*cntr_ptr+1)*sizeof(cityTemp));
            readcsv(citys, cntr_ptr, temp);

            continue;
        }

        else if(temp[0] == '0') break;

    }


//    *cntr_ptr = cntr;

//    printf("\n\n\n%d\n\n\n", *cntr_ptr);

//   printf("\n\n\n---%p\n\n\n", *citys);

   return citys;



}
