
/* c016.c: **********************************************************}
{* Téma:  Tabulka s Rozptýlenými Položkami
**                      První implementace: Petr Přikryl, prosinec 1994
**                      Do jazyka C prepsal a upravil: Vaclav Topinka, 2005
**                      Úpravy: Karel Masařík, říjen 2014
**                              Radek Hranický, říjen 2014
**                              Radek Hranický, listopad 2015
**                              Radek Hranický, říjen 2016
**
** Vytvořete abstraktní datový typ
** TRP (Tabulka s Rozptýlenými Položkami = Hash table)
** s explicitně řetězenými synonymy. Tabulka je implementována polem
** lineárních seznamů synonym.
**
** Implementujte následující procedury a funkce.
**
**  HTInit ....... inicializuje tabulku před prvním použitím
**  HTInsert ..... vložení prvku
**  HTSearch ..... zjištění přítomnosti prvku v tabulce
**  HTDelete ..... zrušení prvku
**  HTRead ....... přečtení hodnoty prvku
**  HTClearAll ... zrušení obsahu celé tabulky (inicializace tabulky
**                 poté, co již byla použita)
**
** Definici typů naleznete v souboru c016.h.
**
** Tabulka je reprezentována datovou strukturou typu tHTable,
** která se skládá z ukazatelů na položky, jež obsahují složky
** klíče 'key', obsahu 'data' (pro jednoduchost typu float), a
** ukazatele na další synonymum 'ptrnext'. Při implementaci funkcí
** uvažujte maximální rozměr pole HTSIZE.
**
** U všech procedur využívejte rozptylovou funkci hashCode.  Povšimněte si
** způsobu předávání parametrů a zamyslete se nad tím, zda je možné parametry
** předávat jiným způsobem (hodnotou/odkazem) a v případě, že jsou obě
** možnosti funkčně přípustné, jaké jsou výhody či nevýhody toho či onoho
** způsobu.
**
** V příkladech jsou použity položky, kde klíčem je řetězec, ke kterému
** je přidán obsah - reálné číslo.
*/

#include <stdio.h>
#include "c016.h"

int HTSIZE = MAX_HTSIZE;
int solved;

/*          -------
** Rozptylovací funkce - jejím úkolem je zpracovat zadaný klíč a přidělit
** mu index v rozmezí 0..HTSize-1.  V ideálním případě by mělo dojít
** k rovnoměrnému rozptýlení těchto klíčů po celé tabulce.  V rámci
** pokusů se můžete zamyslet nad kvalitou této funkce.  (Funkce nebyla
** volena s ohledem na maximální kvalitu výsledku). }
*/

int hashCode(tKey key) {
    int retval = 1;
    int keylen = strlen(key);
    for (int i = 0; i < keylen; i++)
        retval += key[i];
    return (retval % HTSIZE);
}

/*
** Inicializace tabulky s explicitně zřetězenými synonymy.  Tato procedura
** se volá pouze před prvním použitím tabulky.
*/

void htInit(tHTable *ptrht) {

    if (*ptrht != NULL) {

        // Nastavíme všechny položky na NULL
        for (int i = 0; i < MAX_HTSIZE; i++) {
            (*ptrht)[i] = NULL;
        }
    }

}

/* TRP s explicitně zřetězenými synonymy.
** Vyhledání prvku v TRP ptrht podle zadaného klíče key.  Pokud je
** daný prvek nalezen, vrací se ukazatel na daný prvek. Pokud prvek nalezen není, 
** vrací se hodnota NULL.
**
*/

tHTItem *htSearch(tHTable *ptrht, tKey key) {


    if ((*ptrht) != NULL) {

        tHTItem *item = NULL;

        item = (*ptrht)[hashCode(key)];


        while (item != NULL) {

            if (item->key == key)
                return item;
            else
                item = item->ptrnext;

        }

    }

    return NULL;
}

/* 
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vkládá do tabulky ptrht položku s klíčem key a s daty
** data.  Protože jde o vyhledávací tabulku, nemůže být prvek se stejným
** klíčem uložen v tabulce více než jedenkrát.  Pokud se vkládá prvek,
** jehož klíč se již v tabulce nachází, aktualizujte jeho datovou část.
**
** Využijte dříve vytvořenou funkci htSearch.  Při vkládání nového
** prvku do seznamu synonym použijte co nejefektivnější způsob,
** tedy proveďte.vložení prvku na začátek seznamu.
**/

void htInsert(tHTable *ptrht, tKey key, tData data) {

    if (*ptrht != NULL) {

        if ((*ptrht)[hashCode(key)] == NULL) {

            (*ptrht)[hashCode(key)] = malloc(sizeof(tHTable));
            ((*ptrht)[hashCode(key)])->key = key;
            ((*ptrht)[hashCode(key)])->data = data;
            ((*ptrht)[hashCode(key)])->ptrnext = NULL;
        }

        else {
            tHTItem *item = (*ptrht)[hashCode(key)];

            if (item != NULL) {
                do {
                    if (item->key == key) {
                        item->data = data;
                        return;
                    }

                } while ((item = item->ptrnext) != NULL);
            }

            item = ((*ptrht)[hashCode(key)]);

            ((*ptrht)[hashCode(key)]) = malloc(sizeof(tHTable));
            ((*ptrht)[hashCode(key)])->key = key;
            ((*ptrht)[hashCode(key)])->data = data;
            ((*ptrht)[hashCode(key)])->ptrnext = item;

        }


    }

}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato funkce zjišťuje hodnotu datové části položky zadané klíčem.
** Pokud je položka nalezena, vrací funkce ukazatel na položku
** Pokud položka nalezena nebyla, vrací se funkční hodnota NULL
**
** Využijte dříve vytvořenou funkci HTSearch.
*/

tData *htRead(tHTable *ptrht, tKey key) {

    if (*ptrht != NULL) {

        tHTItem *item = NULL;
        if ((item = (*ptrht)[hashCode(key)]) != NULL) {

            do {

                if (item->key == key) {
                    return &(item->data);
                }

            } while ((item = item->ptrnext) != NULL);


        }

    }

    return NULL;

}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vyjme položku s klíčem key z tabulkye
** ptrht.  Uvolněnou položku korektně zrušte.  Pokud položka s uvedeným
** klíčem neexistuje, dělejte, jako kdyby se nic nestalo (tj. nedělejte
** nic).
**
** V tomto případě NEVYUŽÍVEJTE dříve vytvořenou funkci HTSearch.
*/

void htDelete(tHTable *ptrht, tKey key) {

    // Pokud to vubec je alokovaná tabulka
    if (*ptrht != NULL) {

        tHTItem *item = NULL;

        // Zjistím si jestli po hashi na indexu vubec něco je
        if ((item = (*ptrht)[hashCode(key)]) != NULL) {

            // Pokud je tam jediná položka, uvolním ji
            if (item->ptrnext == NULL) {
                free((*ptrht)[hashCode(key)]);
                (*ptrht)[hashCode(key)] = NULL;
                return;
            }

            // Pokud to není jediná položka
            else {


                tHTItem *item_delete = (*ptrht)[hashCode(key)];

                // Pokud je mazaná položka seznamu první položka seznamu
                if (item_delete->key == key) {

                    // Zjistíme si následující položku
                    tHTItem *item_next = item_delete->ptrnext;
                    // Uvolníme první položku
                    free(item_delete);
                    // A první položku nahradíme následující
                    (*ptrht)[hashCode(key)] = item_next;
                    return;
                }

                // Pokud mazadná položka není první položka seznamu
                else {

                    tHTItem *item = item_delete;
                    tHTItem *item_last = item_delete->ptrnext;

                    do {
                        if(item_last != NULL && item_last->key == key) {
                            item->ptrnext = item_last->ptrnext;
                            free(item_last);
                            return;
                        }
                        item = item_last;
                        item_last = item_last->ptrnext;

                    } while(item_last != NULL);

                }

            }
            return;

        }


    }

}

/* TRP s explicitně zřetězenými synonymy.
** Tato procedura zruší všechny položky tabulky, korektně uvolní prostor,
** který tyto položky zabíraly, a uvede tabulku do počátečního stavu.
*/

void htClearAll(tHTable *ptrht) {

    // Pro každou položku tabulky
    for (int i = 0; i < MAX_HTSIZE; i++) {

        // Pokud v ní něco je
        if ((*ptrht)[i] != NULL) {

            // Vezmeme si ukazatel na první prvek a dáme jej do item
            tHTItem **item = &((*ptrht)[i]);
            tHTItem **buffer = NULL;

            // Pokud za prvkem v item něco je
            while ((*item)->ptrnext != NULL) {

                // Do bufferu dáme item
                *buffer = *item;
                // itemem ukážeme na následující
                *item = (*item)->ptrnext;
                // Buffer uvolníme
                free(*buffer);
            }

            // Pokud za aktuálním prvek už nic není, tak jej uvolníme
            free(*item);
            *item = NULL;
        }
    }

}
