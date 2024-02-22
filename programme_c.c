
/* TP language C:  Transformation d'une expression de la notation infixée à la notation postfixée(polonaise)  */

/* préparé par Hassane TAIRI */


/* inclusion des bibliotheque necessaire a la compilation du programme */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define taille_max_pile 50

typedef struct{char tab_pile[taille_max_pile];int indice_pile;}pile; /* on definie une nouvelle structure pile composée d'un tableau de char et d'un indice de pile  */

/* déclaration des prototypes des fonctions */
void init_pile(pile*);
void empile(pile*,char);
char depile(pile*);
char* infixed_to_postfixed(pile*,pile*,char*);
int test_expression(char*);
int est_signe(char);
void message_erreur(char*,int,int);

int main()
{
    char tab_buff[2*taille_max_pile]; /* tableau qui contiendra l'expression à entrer */
    char *infixed,*postfixed; /* deux pointeur de chaine */
    char choix;
    pile p_expr,p_oper; /* declaration de deux pile */
    do
    {

        init_pile(&p_expr); /* initialisation de la pile d'expression */
        init_pile(&p_oper); /* initialisation de la pile d'operateur */
        printf("\n\n\n\t\t--- transformation expresion infixee en polonaise ---\n\n\n\tentrez l'expression infixee : ");
        infixed=gets(tab_buff); /* capturer l'expression entrée au clavier et envoyé l'adresse du premier caractère au pointeur infixed */

        if(test_expression(infixed)==1)/* si l'expression entrée ne comporte pas d'erreur alors */
        {
            postfixed = infixed_to_postfixed(&p_expr,&p_oper,infixed); /* on mets l'expression sous forme polonaise et on récupère la chaine statique génerée grace au pointeur postfixed */
            printf("\n\texpresion polonaise : %s\n\n",postfixed); /* et on l'affiche à l'écran */
        }

        printf("\n\ttapez r pour une nouvelle espression ou tapez q pour quitter !!\n");
        do
            choix=getch(); /* attendre jusqu'a ce que l'utilisateur tape sur 'r' ou 'q' */
        while(choix!='q'&&choix!='r');
    }while(choix!='q'); /* si l'utilisateur tape 'r' recommencer s'il tape 'q' quitter le programme */
    return 0;
}


/*  fonction dinitialisation de pile
    elle prend en parametre l'adresse de la pile à initialiser*/
void init_pile(pile *une_pile)
{
    int i;
    une_pile->indice_pile=0; /* mise a 0 de l'indice de pile */
    for(i=0;i<taille_max_pile;i++)
        une_pile->tab_pile[i]='\0'; /* remplir la pile avec les caractères de fin de chaine */
}


/*  fonction d'empilement dans la pile
    cette fonction empile un caractère en tete de pile
    elle prend en parametres l'adresse de la pile et le caractère à empiler */
void empile(pile *une_pile,char car)
{
    if(une_pile->indice_pile<taille_max_pile) /* si la pile n'est pas pleine */
    {
        une_pile->tab_pile[une_pile->indice_pile]=car; /* on stock le caractère a l'endroit de l'indice de pile */
        une_pile->indice_pile++; /* on incrémente l'indice de pile */
    }
    else
        printf("\nerreur pile pleine!!\n"); /* sinon on affiche un message d'erreur */
}


/*  fonction de dépilement dans la pile
    cette fonction dépile le caractère de tete de pile
    elle prend en parametre l'adresse de la pile et elle retourne le caractère de tete de pile
    si la pile est vide la fonction retourne un point d'exclamation comme caractère d'erreur */
char depile(pile *une_pile)
{
    char car; /* variable qui va stocker le caractère a dépiler */
    if(une_pile->indice_pile>0) /* si la pile n'est pas vide */
    {
        une_pile->indice_pile--; /* on décrémente l'indice de pile */
        car=une_pile->tab_pile[une_pile->indice_pile]; /* on stock le caractère de l'indice de pile dans car */
        une_pile->tab_pile[une_pile->indice_pile]='\0'; /* on efface le caractère de l'indice de pile */
    }
    else /* sinon */
    {
        printf("\nerreur pile vide\n"); /* on affiche un message d'erreur */
        car='!'; /* on affecte à car le caractère d'erreur */
    }
    return(car); /* la fonction retournera car */

}



/*  fonction qui transforme une expression sous la forme infixée en une expression sous forme polonaise
    elle prend en parametres l'adresses de deux pile ainsi que l'adresse du premier caractère de l'expression sous forme infixée
    une pile sera utilisée pour stocker l'expression postfixée finale et l'autre pour stocker temporairement les opérateur de l'expression
    elle retourne l'adresse du premier caractère de l'expression transformée*/
char* infixed_to_postfixed(pile *pile_expr,pile *pile_oper,char *expr)
{
    int i,taille_expr;
    char car;
    taille_expr=strlen(expr); /* on stock la taille de l'expression dans taille_expr */
    for(i=1;i<taille_expr;i++) /* on parcours l'expression caractère par caractère à partir du deuxième caractère puisque une expression
                                  completement parenthèsée comence forcément par une parenthèse*/
    {
        car = *(expr+i); /* a chaque fois car recevra le prochain caractère de l'expression */
        if(isalpha(car))
            empile(pile_expr,car); /* si le caractère actuel est alphabétique on l'empile dans la pile_expr */
        else if(est_signe(car))
            empile(pile_oper,car); /* sinon si le caractère actuel est un opérateur on l'empile dans la pile_oper */
        else if(car==')')
            empile(pile_expr,depile(pile_oper)); /* sinon si le caractère actuel est une parenthèse fermante on dépile un caractère dans la pile_oper
                                                    pour l'empiler dans la pile_expr */
    }
    return(pile_expr->tab_pile); /* on retourne l'adresse du premier caractère de l'expression transformée */

}



/*  fonction qui test si une expression sous la forme infixée est correcte
    elle prend en parametre l'adresse du premier caractère de l'expression
    cette fonction va parcourir l'expression caractère par caractère et s'arretera à la première erreur rencontrée
    en indiquant la position de l'erreur rencontrée et la nature de celle-ci
    elle retourne un entier, 1 si l'expression est correcte ou 0 sinon*/
int test_expression(char *expr)
{
    /*  ici pour quelque variables on va les précédés du mots clé statique ça signifie que ces variables ne seront pas éffacées
        entre deux appel de la fonction et garderont leur valeurs à la sortie de la fonction */

    static int pos; /* variable en mode static qui va stocker la position dans l'expression */
    static int tour=0; /* variable en mode static qui va stocker l'ordre d'appel de la fonction elle sera initialiser à 0 pour la première fois*/
    int save_pos,save_tour; /* variables qui vont stocker la position dans l'expression et l'ordre d'appel de la fonction
                                pour pouvoir les récuperés entre deux appel de la fonction */

    int retour; /* variable qui va stocker la valeur a retourner par la fonction */
    static int code_erreur; /* variable en mode static qui va stocker la nature de l'erreur rencontrée si une erreur est trouvée */
    pos=0; /* mise à 0 de la variable pos */
    tour++; /* incrémenter la variable tour */

    if(*expr=='(') /* si le premier caractère de l'expression est une parenthèse ouvrante alors */
    {
        pos++; /* incrémenter pos */
        if(isalpha(*(expr+pos))) /* si le deuxième caractère est alphabétique alors */
        {
            pos++; /* incrémenter pos */
            if(est_signe(*(expr+pos))) /* si le troisième caractère est un opérateur alors */
            {
                pos++; /* incrémenter pos */
                if(isalpha(*(expr+pos))) /* si le quatrième le caractère est alphabétique alors */
                {
                    pos++; /* incrémenter pos */
                    if(*(expr+pos)==')') /* si le cinquième caractère est une parenthèse fermante alors */
                        retour=1; /* retour reçoit 1 */
                    else /* sinon si le cinquième caractère n'est pas une parenthèse fermante alors */
                    {
                       retour=0; /* retour reçoit 0 */
                       code_erreur=3; /* code erreur reçoit 3 */
                    }

                }
                else if(*(expr+pos)=='(') /* sinon si le quatrième caractère est une parenthèse ouvrante */
                {
                    /*  dans ce cas on a peut etre un nouveau therme sous forme d'expression donc il faut vérifier si ce nouveau therme est correcte ou pas
                        pour ça on ferra un autre appel à la fonction test_expression pour le vérifier sauf que l'expression qu'on va lui envoyé cette fois
                        sera a partir du nouveau therme détecté donc ici à partir du 4eme caractère */

                    save_pos=pos; /* on sauvgarde la position actuel dans save_pos */
                    save_tour=tour; /* on sauvgarde le rang d'appel actuel dans save_tour */
                    if(test_expression(expr+pos)) /* si le nouveau theme est sous une forme correcte alors */
                    {
                        pos=pos+save_pos+1; /*  on calcule la nouvelle position dans l'expression à partir de la position sauvgardée (save_pos)
                                                et de la dernière position connu par la fonction test_expression (pos) en effet grace au mots clé
                                                static la variable pos n'est pas supprimée à la sortie de la fonction, on pourra donc en avoir accées ici */
                        tour=save_tour; /* on récupère le rang d'appel de la fonction en cours */
                        if(*(expr+pos)==')') /* si le caractère suivant est une parenthèse fermante alors */
                            retour=1; /* retour reçoit 1 */
                        else /* sinon si le caractère suivant n'est pas une parenthèse fermante alors */
                        {
                            retour=0; /* retour reçoit 0 */
                            code_erreur=3; /* code_erreur reçoit 3 */
                        }

                    }
                    else /* sinon si le nouveau therme n'est pas sous une forme correcte alors */
                    {
                        pos=pos+save_pos; /* on calcule la nouvelle position dans l'expression c'est à dire l'endroit ou est survenue l'erreur */
                        tour=save_tour; /* on récupère le rang d'appel de la fonction en cours */
                        retour=0; /* retour reçoit 0 */
                    }

                }
                else /* sinon si le quatrième caractère n'est pas une parenthèse ouvrante */
                {
                    retour=0; /* retour reçoit 0 */
                    code_erreur=0; /* code_erreur reçoit 0 */
                }
            }
            else /* sinon si le troisième caractère n'est pas un opérateur alors */
            {
                retour=0; /* retour reçoit 0 */
                code_erreur=1; /* code_erreur reçoit 1 */
            }
        }
        else if(*(expr+pos)=='(') /* sinon si le deuxième caractère est une parenthèse ouvrante alors */
        {
            /*  dans ce cas on a peut etre un nouveau therme sous forme d'expression donc il faut vérifier si ce nouveau therme est correcte ou pas
                pour ça on ferra un autre appel à la fonction test_expression pour le vérifier sauf que l'expression qu'on va lui envoyé cette fois
                sera a partir du nouveau therme détecté donc ici à partir du 2eme caractère */

            save_pos=pos; /* on sauvgarde la position actuel dans save_pos */
            save_tour=tour; /* on sauvgarde le rang d'appel actuel dans save_tour */
            if(test_expression(expr+pos)) /* si le nouveau theme est sous une forme correcte alors */
            {
                pos=pos+save_pos+1; /*  on calcule la nouvelle position dans l'expression à partir de la position sauvgardée (save_pos)
                                        et de la dernière position connu par la fonction test_expression (pos) en effet grace au mots clé
                                        static la variable pos n'est pas supprimée à la sortie de la fonction, on pourra donc en avoir accées ici */
                tour=save_tour; /* on récupère le rang d'appel de la fonction en cours */
                if(est_signe(*(expr+pos))) /* si le caractère suivant est un opérateur alors */
                {
                    pos++; /* incrémenter pos */
                    if(isalpha(*(expr+pos))) /* si le caractère suivant est alphabétique alors */
                    {
                        pos++; /* incrémenter pos */
                        if(*(expr+pos)==')') /* si le caractère suivant est une parenthèse fermante alors */
                            retour=1; /* retour reçoit 1 */
                        else /* sinon si le caractère suivant n'est pas une parenthèse fermante alors */
                        {
                            retour=0; /* retour reçoit 0 */
                            code_erreur=3; /* code_erreur reçoit 3 */
                        }

                    }
                    else if(*(expr+pos)=='(') /* sinon si le caractère suivant est une parenthèse ouvrante alors */
                    {
                        /*  dans ce cas on a peut etre un nouveau therme sous forme d'expression donc il faut vérifier si ce nouveau therme est correcte ou pas
                            pour ça on ferra un autre appel à la fonction test_expression pour le vérifier sauf que l'expression qu'on va lui envoyé cette fois
                            sera a partir du nouveau therme détecté */

                        save_pos=pos; /* on sauvgarde la position actuel dans save_pos */
                        save_tour=tour; /* on sauvgarde le rang d'appel actuel dans save_tour */
                        if(test_expression(expr+pos)) /* si le nouveau theme est sous une forme correcte alors */
                        {
                            pos=pos+save_pos+1; /*  on calcule la nouvelle position dans l'expression à partir de la position sauvgardée (save_pos)
                                                    et de la dernière position connu par la fonction test_expression (pos) en effet grace au mots clé
                                                    static la variable pos n'est pas supprimée à la sortie de la fonction, on pourra donc en avoir accées ici */
                            tour=save_tour; /* on récupère le rang d'appel de la fonction en cours */
                            if(*(expr+pos)==')') /* si le caractère suivant est une parenthèse fermante alors */
                                retour=1; /* retour reçoit 1 */
                            else /* sinon si le caractère suivant n'est pas une parenthèse fermante alors */
                            {
                                retour=0; /* retour reçoit 0 */
                                code_erreur=3; /* code_erreur reçoit 3 */
                            }

                        }
                        else /* sinon si le nouveau therme n'est pas sous une forme correcte alors */
                        {
                            pos=pos+save_pos;/* on calcule la nouvelle position dans l'expression c'est à dire l'endroit ou est survenue l'erreur */
                            tour=save_tour; /* on récupère le rang d'appel de la fonction en cours */
                            retour=0; /* retour reçoit 0 */
                        }


                    }
                    else /* sinon si le caractère suivant n'est pas une parenthèse ouvrante alors */
                    {
                        retour=0; /* retour reçoit 0 */
                        code_erreur=0; /* code_erreur reçoit 0 */
                    }
                }
                else /* sinon si le caractère suivant n'est pas un opérateur alors */
                {
                    retour=0; /* retour reçoit 0 */
                    code_erreur=1; /* code_erreur reçoit 1 */
                }
            }
            else /* sinon si le nouveau theme n'est pas sous une forme correcte alors */
            {
                pos=pos+save_pos; /* on calcule la nouvelle position dans l'expression c'est à dire l'endroit ou est survenue l'erreur */
                tour=save_tour; /* on récupère le rang d'appel de la fonction en cours */
                retour=0; /* retour reçoit 0 */
            }


        }
        else /* sinon si le deuxième caractère n'est pas une parenthèse ouvrante alors */
        {
            retour=0; /* retour reçoit 0 */
            code_erreur=0; /* code_erreur reçoit 0 */
        }
    }
    else /* sinon si le premier caractère de l'expression n'est pas une parenthèse ouvrante alors */
    {
        retour=0; /* retour reçoit 0 */
        code_erreur=2; /* code_erreur reçoit 2 */
    }


    if(tour==1) /* si tour=1 autrement dit si c'est le premier appel de la fonction et donc l'expresion principale alors */
    {
        if(retour==0) /* si retour=0 alors */
            message_erreur(expr,pos,code_erreur); /* appel de la fonction message_erreur */
        else if(pos+1!=strlen(expr)) /* sinon si l'expression est correcte mais pas completement parcourue alors */
        {
            retour=0; /* retour reçoit 0 */
            code_erreur=4; /* code_erreur reçoit 4 */
            message_erreur(expr,pos+1,code_erreur); /* appel de la fonction message_erreur */

        }
        tour=0; /* réinisialitation de tour pour un prochaine appel de la fonction pour une nouvelle expression */
    }

    return(retour); /* retourner la valeur de retour */
}


/*  fonction qui test si un caractère est un pérateur ou pas
    cette fonction prend en parametre un caractère sur qui faire le test
    et renvoie un entier 1 si c'est un opérateur 0 sinon */
int est_signe(char car)
{
    if(car=='-'||car=='+'||car=='*'||car=='/')
        return(1);
    else
        return(0);
}



/*  fonction qui affiche une expression erronée et la nature de l'erreur selon le code d'erreur
    elle prend en parametres l'adresse du premier caractère de l'expression à affichée,
    le nombre de caractères à affichée et le code de l'erreur */
void message_erreur(char *expr,int stop,int erreur)
{
    int i;
    printf("\n\terreur expression : ");
    for(i=0;i<stop;i++)
        printf("%c",*(expr+i)); /* afficher l'expression jusqu'au marqueur stop */
    switch(erreur) /* selon le code d'erreur afficher la nature de l'erreur */
    {
        case 0:
            printf("_  \"nouveau therme attendu !!\"\n");
            break;
        case 1:
            printf("_  \"operateur attendu !!\"\n");
            break;
        case 2:
            printf("_  \"parenthese ouvrante attendu !!\"\n");
            break;
        case 3:
            printf("_  \"paranthese fermante attendu !!\"\n");
            break;
        case 4:
            printf("_  \"fin d'expression attendu !!\"\n");
            break;
    }
}
