
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, říjen 2017
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu, 
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek, 
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku, 
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu, 
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem, 
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu, 
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam 
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList(tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/
    L->Act = L->First = L->Last = NULL;

}

void DLDisposeList(tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free. 
**/

    tDLElemPtr actualItem = L->First;

    while (actualItem != NULL) {
        tDLElemPtr next = actualItem->rptr;
        free(actualItem);
        actualItem = next;
    }

    L->First = L->Last = L->Act = NULL;

}

void DLInsertFirst(tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

    // Mallocujeme paměť pro nový rvek
    tDLElemPtr new = (tDLElemPtr) malloc(sizeof(struct tDLElem));

    // Ověříme zda skutečně došlo k malokizaci, pokud ne tak skonči
    if (new == NULL) {
        DLError();
        return;
    }

    // Nastavíme novému prvku hodotu
    new->data = val;

    // Pokud je seznam prázdný, vložíme prvek na začátek a ukážeme posledním na první
    if (L->First == NULL) {
        L->First = L->Last = new;
        L->First->lptr = L->First->rptr = NULL;
        return;
    }

    // Pokud není první, tak na levý ukazatel prvního připneme nový prvek

    L->First->lptr = new;

    // levý ukazatel nového prvku nastavíme na NULL
    L->First->lptr->lptr = NULL;

    // Pravý ukazatel nastavíme na ten co byl předtám první
    L->First->lptr->rptr = L->First;

    // A nastavíme nový jako první
    L->First = L->First->lptr;


}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

    // Mallocujeme paměť pro nový prvek
    tDLElemPtr new = (tDLElemPtr) malloc(sizeof(struct tDLElem));

    // Pokud se malokace nepovedla, tak vypiš chybu a skonči
    if (new == NULL) {
        DLError();
        return;
    }

    // Nastavíme novému prvku hodotu
    new->data = val;

    // Pokud je seznam prázdný, tak nový bude první a poslední
    if (L->First == NULL) {
        L->First = L->Last = new;
        L->First->lptr = L->First->rptr = NULL;
        return;
    }

    // Pokud není seznam prázdný, tak nový umístíme na pravý ukazatel posledního
    L->Last->rptr = new;

    // pravý ukazatel nového nastavíme ne NULL
    L->Last->rptr->rptr = NULL;

    // Levý nastavíme na ten co byl poslední
    L->Last->rptr->lptr = L->Last;

    // Poslední nastavíme na nový
    L->Last = L->Last->rptr;

}

void DLFirst(tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/

    // Do ukazatele aktivního prvku nastavíme ukazatel prvního prvku
    L->Act = L->First;

}

void DLLast(tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/

    // Do ukazatele aktivního prvku nastavíme ukazatel posledního prvku
    L->Act = L->Last;

}

void DLCopyFirst(tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    // Pokud je seznam prázdný, vypiš error
    if (L->First == NULL)
        DLError();

        // Pokud prázdný není, dej tam kam ukazuje val datovou hodnotu z prvního prvku
    else
        *val = L->First->data;
}

void DLCopyLast(tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

    // Pokud je seznam prázdný, vypiš error
    if (L->First == NULL)
        DLError();

        // Pokud prázdný není, dej tam kam ukazuje val datovou hodnotu z prvního prvku
    else
        *val = L->Last->data;
}

void DLDeleteFirst(tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita 
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/

    // Pokud byl seznam prázdný, nedělej nic
    if (L->First == NULL)
        return;

    // Pokud je první prvek aktivní, aktivitu ztrať
    if (L->First == L->Act)
        L->Act = NULL;

    // Pokud je seznam jednoprvkový, zruš ho a nastav seznam do počátečního stavu
    if (L->First == L->Last) {
        free(L->First);
        L->First = L->Last = NULL;
        return;
    }

    // Pokud není prvníjednoprvkový
    L->First = L->First->rptr;
    free(L->First->lptr);
    L->First->lptr = NULL;
}

void DLDeleteLast(tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/

    // Pokud byl seznam prázdný, neděje se nic
    if (L->First == NULL)
        return;

    // Pokud byl poslední prvek aktivní, zruš aktivitu
    if (L->Last == L->Act)
        L->Act = NULL;

    // Pokud je poslední prvek první prvek, zruš ho a uveď seznam do počátečního stavu
    if (L->First == L->Last) {
        free(L->First);
        L->First = L->Last = NULL;
        return;
    }

    // Pokud není první prvek poslední
    L->Last = L->Last->lptr;
    free(L->Last->rptr);
    L->Last->rptr = NULL;

}

void DLPostDelete(tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/

    // Pokud není aktivní, nic se neděje
    if (!DLActive(L))
        return;

    // Pokud za aktivním je pouze NULL, nic se neděje
    if (L->Act->rptr == NULL)
        return;

    // Najdeme si ukazatel na rušený prvek
    tDLElemPtr remove_item = L->Act->rptr;

    // Pokud jsou v seznamu pouze dva prvky, tak seznam uvedu do stavu jednoprvkového
    if (L->Act->lptr == NULL && remove_item->rptr == NULL) {
        L->First = L->Last = L->Act;
        L->First->lptr = L->Last->rptr = NULL;
    } else {

        // Za itemem který chceme mazat už nic není
        if (remove_item->rptr == NULL) {
            L->Act->rptr = NULL;
            L->Last = L->Act;
        }

            // Za itemem který chceme mazat ještě něco je
        else {

            L->Act->rptr = remove_item->rptr;
            remove_item->rptr->lptr = L->Act;

        }
    }

    // Uvolníme prvek
    free(remove_item);


}

void DLPreDelete(tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/

    // Pokud není seznam aktivní, nedělej nic
    if (!DLActive(L))
        return;

    // Pokud nemáš co mazat, nedělej nic
    if (L->Act->lptr == NULL)
        return;

    // Označ si smaazaná element
    tDLElemPtr remove_item = L->Act->lptr;

    // Pokud má seznam pouze dva prvky, udělej z něj jednoprvkový
    if (L->Act->rptr == NULL && remove_item->lptr == NULL) {
        L->First = L->Last = L->Act;
        L->First->lptr = L->Last->rptr = NULL;
    } else {

        // Pokud nalevo od mazaného už jakože nic není
        if (remove_item->lptr == NULL) {
            L->Act->lptr = NULL;
            L->First = L->Act;
        }

            // Pokud nalevo od mazaného ještě něco je, tak přeukážeme
        else {
            L->Act->lptr = remove_item->lptr;
            remove_item->lptr->rptr = L->Act;

        }
    }

    // Uvolníme prvek
    free(remove_item);

}

void DLPostInsert(tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

    // Pokud nebyl aktivní, nedělej nic
    if (!DLActive(L))
        return;

    // Mallocuj si nový prvek
    tDLElemPtr new = malloc(sizeof(tDLElemPtr));

    // Pokud se malokizování nepovedlo, chybuj a skonči
    if (new == NULL) {
        DLError();
        return;
    }

    // Dej do něj data
    new->data = val;

    // Pokud za aktivním ještě jakože nic není
    if (L->Act->rptr == NULL) {
        L->Act->rptr = new;
        new->rptr = NULL;
        new->lptr = L->Act;
        L->Last = new;
    }

        // Pokud za aktivním už něco je, tka přeukaž
    else {
        L->Act->rptr->lptr = new;
        new->rptr = L->Act->rptr;
        new->lptr = L->Act;
        L->Act->rptr = new;
    }

}

void DLPreInsert(tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

    // Pokud seznam není aktivní, nedělej nic
    if (!DLActive(L))
        return;

    // Malokizuj nový prvek
    tDLElemPtr new = malloc(sizeof(tDLElemPtr));

    // Pokud se to nepovedlo, vypiš chybu, skonči
    if (new == NULL) {
        DLError();
        return;
    }

    // Přiřaď do něj hodnotu
    new->data = val;


    // Pokud před ním nic není, přidej to tam  přeukaž
    if (L->Act->lptr == NULL) {
        L->Act->lptr = new;
        new->lptr = NULL;
        new->rptr = L->Act;
        L->First = new;
    }

        // Pokud tam už něco je tak změň ukazatele
    else {
        L->Act->lptr->rptr = new;
        new->lptr = L->Act->lptr;
        new->rptr = L->Act;
        L->Act->lptr = new;
    }


}

void DLCopy(tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/

    // Pokud seznam není aktivní, chybuj
    if (!DLActive(L))
        DLError();

        // Pokud je aktivní tak tam kam ukazuje val nahraj hodnotu z aktivního prvku
    else
        *val = L->Act->data;
}

void DLActualize(tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/
    // Pokud je seznam aktivní, tak na aktivní prvek do dat nahraj hodnotu val
    if (DLActive(L))
        L->Act->data = val;

}

void DLSucc(tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/

    // Pokud je seznam aktivní, tak posuň aktivitu na následující prvek
    if (DLActive(L))
        L->Act = L->Act->rptr;
}


void DLPred(tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/

    // Pokud je seznam aktivní, tak posuň aktivitu na předcházející prvek
    if (DLActive(L))
        L->Act = L->Act->lptr;

}

int DLActive(tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/
    // Vrať jestli je sznam aktivní
    return (L->Act != NULL);
}

/* Konec c206.c*/
