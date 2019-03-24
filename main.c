#include <stdio.h>
#include <stdlib.h>

/*   Cift yonlu listede

    ,basaEkle, sonaEkle, oncesineEkle, sonrasinaEkle, Ekle
    ,bastanSil, sondanSil, aradanSil, sil
    ,yazdir, bubbleSort
*/

// Eklencek node icin alan alicak fonksiyon eklenebilir
// Scanf vs kullanilabilir

typedef struct node{
    int data;
    struct node* prev;
    struct node* next;
}node;

node * head; // global degisken - pointer to head node
             // head node dedigimiz sey listedeki ilk node

void basaEkle(int veri)
{
    node * yeniNode = malloc(sizeof(node));      // Eklenecek node icin heapte alan
    yeniNode->data = veri;
    yeniNode->prev = NULL;
    yeniNode->next = NULL;

    if(head == NULL)
    {
        head = yeniNode;
        return;
    }

    head->prev = yeniNode;                     // basa ekleme algoritmasi
    yeniNode->next = head;
    head = yeniNode;
}

void sonaEkle(int veri)
{
    node * yeniNode = malloc(sizeof(node)); //Eklenecek node icin heapte alan
    yeniNode->data = veri;
    yeniNode->prev = NULL;
    yeniNode->next = NULL;


    node *trav = head; //traverse
    while(trav->next!=NULL)
    {
        trav = trav->next;
    }

    trav->next = yeniNode;           // sona ekleme algoritmasi
    yeniNode->prev = trav;
}

void oncesineEkle(int veri_ref, int veri)
{
    node * yeniNode = malloc(sizeof(node));
    yeniNode->data = veri;

    if (head==NULL)
    {
        printf("LISTE BOS\n");
        return;
    }

    node *trav = head;
    while(trav->data != veri_ref)    // arama algoritmasi
    {
        trav= trav->next;
    }

    yeniNode->next = trav;          // oncesine ekleme algoritmasi
    yeniNode->prev = trav->prev;
    trav->prev->next = yeniNode;
    trav->prev = yeniNode;
}

void sonrasinaEkle(int veri_ref, int veri)
{
    node * yeniNode = malloc(sizeof(node));
    yeniNode->data = veri;

    if(head==NULL)
    {
        printf("LISTE BOS\n");
        return;
    }

    node *trav = head;              // arama algoritmasi
    while(trav->data != veri_ref)
    {
        trav = trav->next;
    }

    yeniNode->prev = trav;       // sonrasina ekleme algoritmasi
    yeniNode->next = trav->next;
    trav->next->prev = yeniNode;
    trav->next = yeniNode;
}

void Ekle(int veri)         // duruma gore basa veya sona ekleme fonksiyonu
{
    if(head == NULL)
    {
       basaEkle(veri);
       return;
    }
    sonaEkle(veri);
}

void bastanSil()
{
    node *silinecek = head; // Free() kullanmak icin silinecek node adresini tutuyoruz

    if(head==NULL)
    {
        printf("LISTE BOS\n");
        return;
    }

    if(head->next == NULL)
    {
        free(silinecek);
        printf("LISTE BOSALTILDI\n");
        head = NULL;
        return;
    }

    head = head->next;
    head->prev = NULL;
    free(silinecek);
}

void sondanSil()
{
    node *silinecek = head;    // Free() kullanmak icin silinecek node'un adresini tutuyoruz
    if(head==NULL)
    {
        printf("LISTE BOS\n");
        return;
    }

    if(head->next == NULL) // Eger bir tek head node varsa
    {
        free(silinecek);
        printf("LISTE BOSALTILDI\n");
        head = NULL;
        return;
    }

    node *trav = head;      // Listenin sonuna gitme algoritmasi
    while(trav->next != NULL)
    {
        trav = trav->next;
    }

    silinecek = trav;

    trav = trav->prev;  // sondanSilme algoritmasi
    trav->next = NULL;

    free(silinecek);
}

void secimSil(int veri_ref)
{
    if(head==NULL)
    {
        printf("LISTE BOS\n");
        return;
    }

        node *silinecek = head;
       if(head->next == NULL) // Eger bir tek head node varsa
    {
        free(silinecek);
        printf("LISTE BOSALTILDI\n");
        head = NULL;
        return;
    }

    node *trav = head;                  // arama algoritmasi
    while(trav->data != veri_ref)
    {
        trav = trav->next;
    }
    silinecek = trav;

    trav->prev->next = trav->next;  // Aradan silme algoritmasi
    trav->next->prev = trav->prev;

    free(silinecek);
}

void sil(int veri_ref)
{
    if(head==NULL)
    {
        printf("Silinecek bir sey yok\n");
        return;
    }

     if(veri_ref == head->data)
    {
        bastanSil();
        return;
    }

    node *trav = head;              // arama algoritmasi
    while(trav->data != veri_ref)
    {
        trav = trav->next;
    }

                                    //arada mi sonda mi kontrolleri
    if(trav->next != NULL && trav->prev != NULL)
    {
        secimSil(veri_ref);
    }

    if(trav->next == NULL && trav->prev != NULL)
    {
        sondanSil();
    }
}



void yazdir()
{
    node * trav = head;

    if(head == NULL)
    {
        printf("Yazdirilacak bir sey yok, liste bos\n");
        return;
    }

    printf("\nDuz : ");
    while (trav != NULL)
    {
        printf("%d ------>", trav->data);
        trav = trav->next;
    }
}

void bubbleSort()
{
    int swapped,i;
    node *trav;
    node *lptr = NULL;
    //liste bos ise
    if (head==NULL)
    {
        return;
    }

    do
    {
        swapped = 0;
        trav = head;

        while (trav->next != lptr)
        {
            if (trav->data > trav->next->data)
            {
                degistir(trav, trav->next); // iki node datasini degistiren fonksiyonu cagirir
                swapped = 1;
            }
            trav = trav->next;
        }
        lptr = trav;
    }while (swapped);

    printf("\nListe siralandi\n");
}

void degistir(struct node* a, struct node *b)   // iki node'un datasini degistiren fonksiyon
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void tersYazdir()
{
    node * trav = head;
        if(trav == NULL)
    {
        printf("Yazdirilacak bir sey yok, liste bos.");
        return;
    }

    //Son node'a git
    while(trav->next != NULL)
    {
        trav = trav->next;
    }

    //Tersten yazdir
    printf("\nTersten : ");
    while(trav != NULL )
    {
        printf("%d------>", trav->data);
        trav = trav->prev;
    }
    printf("\n");
}


int main()
{
    Ekle(3);                 //test
    Ekle(2);

    yazdir();
    tersYazdir();           // next,prev baglantilarinin dogru kurulup kurulmadigini tersten yazdirarak görebiliriz

    return 0;
}
