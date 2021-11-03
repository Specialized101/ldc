// liste_doublement_chainee_v1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ldc.h"
#include "client.h"

int main()
{
    struct Ldc* list;
    struct Client* client1, * client2, * client3, * client4, * client5;

    list = ldc_new();

    client1 = client_new("Einstein", "Albert", 1);
    client2 = client_new("Newton", "Isaac", 2);
    client3 = client_new("Turing", "Alan", 3);
    client4 = client_new("Fares", "Raja", 4);
    client5 = client_new("Fares", "Yassine", 5);

    ldc_insert_client(list, client1, -100);
    ldc_insert_client(list, client2, -50); 
    ldc_insert_client(list, client3, 300);
    ldc_insert_client(list, client5, 500);
    ldc_insert_client(list, client4, 400);

    ldc_display_asc(list);
    //ldc_display_desc(list);

    ldc_remove_client(list, client1);

    ldc_display_asc(list);

    ldc_del(list);
    
    // test 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
