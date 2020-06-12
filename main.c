#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "header.h"




int main()
{

    cityTemp *citys = malloc(sizeof(cityTemp));
    cityTemp *array_end;

    float timeSec;
    clock_t timeBegin, timeEnd;

    int running = 1;
    int cntr = 0;
    int cntr4new = 0;

    while (running == 1)                            //Menü Schleife
    {
        cntr = 0;

        int choice = menu();                        //menu() gibt Zahl von 0-3 zurück; 1 = Städte nach Namen sortieren; 2 = Travelling SP; 3 = Städte zur CSV hinzufügen

        getchar();                                  // da sonst die nächste Einlesefnkt nur '\n' liest

        switch(choice)
        {
            case 1:                                 // Städte sortiert ausgeben
            {


                citys = cityInput(&cntr, citys);    // liest Städte in das citys Array ein und füllt das Array mit den Daten aus der CSV

                timeBegin = clock();
                citys = bubble(citys, &cntr);
                timeEnd = clock();

                timeSec=timeEnd - timeBegin;
                timeSec/=CLOCKS_PER_SEC;
                printf("\n\nBenoetigte Zeit um bubblesort zwei mal auszufuehren: %f Sekunden\n\n\n\n", timeSec);

                timeBegin = clock();
                array_end = citys;
                for(int i = 0;i<cntr-1;i++)
                {
                    array_end++;
                }
                quicksort_name(citys, array_end);
                printf("\nquicksort, sorted by name:\n");
                for(int i = 0; i <= cntr-1; i++)
                {
                    printf("\ncity: %-20s population: %8ld",citys[i].city_ascii,citys[i].population);
                }

                array_end = citys;
                for(int i = 0;i<cntr-1;i++)
                {
                    array_end++;
                }
                quicksort_pop(citys, array_end);
                printf("\n\nquicksort, sorted by population:\n");
                for(int i = 0; i <= cntr-1; i++)
                {
                    printf("\ncity: %-20s population: %8ld",citys[i].city_ascii,citys[i].population);
                }

                timeEnd = clock();

                timeSec=timeEnd - timeBegin;
                timeSec/=CLOCKS_PER_SEC;
                printf("\n\nBenoetigte Zeit um quicksort zwei mal auszufuehren: %f Sekunden\n\n\n\n", timeSec);

                printf("\n\nWollen Sie diese Staedteliste in einer .csv Datei abpseichern? (Y/N) ");
                scanf(" %c", &choice);
                getchar();

                if (choice == 'y' || choice == 'Y')
                {
                    city_struct_to_csv(citys, cntr);
                }
                else
                {
                    printf("\nStaedteliste wurden geloescht.\n");

                }


                break;
            }

            case 2:                                  // kürzeste Route ermitteln
            {

                citys = cityInput(&cntr, citys);

                citys = nearestNeighbor(&cntr, citys);

                printShortesRoute(&cntr, citys);

                printf("\n\nWollen Sie diese Staedteliste in einer .csv Datei abpseichern? (Y/N) ");
                scanf(" %c", &choice);
                getchar();

                if (choice == 'y' || choice == 'Y')
                {
                    city_struct_to_csv(citys, cntr);
                }
                else
                {
                    printf("\nStaedteliste wurden geloescht.\n");

                }

                break;
            }
            case 3:                                  // Städte zur .csv hinzufügen
            {

                citys = user_input_to_city_Struct(&cntr4new);

                for(int i = 0; i < cntr4new; i++)                             // test ob die Daten eingelesen werden
                    {
                        printf("\n\ncity: %s\n",citys[i].city);
                        printf("cityAscii: %s\n",citys[i].city_ascii);
                        printf("lat: %f\n",citys[i].lat);
                        printf("lng: %f\n",citys[i].lng);
                        printf("country: %s\n",citys[i].country);
                        printf("iso2: %s\n",citys[i].iso2);
                        printf("iso3: %s\n",citys[i].iso3);
                        printf("adminName: %s\n",citys[i].admin_name);
                        printf("capital: %s\n",citys[i].capital);
                        printf("population: %ld\n",citys[i].population);
                        printf("id: %ld\n\n",citys[i].id);

                        printf("---------------------------------------------\n\n");

                    }

                printf("\n\nWollen Sie diese Staedteliste in einer .csv Datei abpseichern? (Y/N) ");
                scanf(" %c", &choice);
                getchar();

                if (choice == 'y' || choice == 'Y')
                {
                    city_struct_to_csv(citys, cntr4new);
                }
                else
                {
                    printf("\nStaedteliste wurden geloescht.\n");

                }
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


    free(citys);

    return 0;

}

