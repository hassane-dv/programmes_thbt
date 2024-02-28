import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

class Carte {
    private String valeur;
    private String couleur;

    public Carte(String valeur, String couleur) {
        this.valeur = valeur;
        this.couleur = couleur;
    }

    public String toString() {
        return valeur + " de " + couleur;
    }

    public String getValeur() {
        return valeur;
    }

    public String getCouleur() {
        return couleur;
    }
}

public class JeuDeCartes {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Carte> jeuDeCartes = creerJeuDeCartes();
        boolean continuer = true;

        while (continuer) {
            System.out.println("Choisissez une option :");
            System.out.println("1. Afficher les cartes");
            System.out.println("2. Distribuer les cartes");
            System.out.println("3. Comparer deux cartes");
            System.out.println("4. Jouer au jeu de plis");
            System.out.println("5. Quitter");

            int choix = scanner.nextInt();
            switch (choix) {
                case 1:
                    afficherCartes(jeuDeCartes);
                    break;
                case 2:
                    distribuerCartes(jeuDeCartes);
                    break;
                case 3:
                    System.out.println("Choisissez la valeur de deux cartes :");

                    System.out.print("Entrez la valeur de la carte 1: ");
                    String valeur1 = scanner.next();
                    String couleur1 = "Coeur";
                    Carte carte1 = new Carte(valeur1, couleur1);

                    System.out.print("Entrez la valeur de la carte 2: ");
                    String valeur2 = scanner.next();
                    String couleur2 = "Coeur";
                    Carte carte2 = new Carte(valeur2, couleur2);


                    comparerCartes(carte1, carte2);
                    break;
                case 4:
                    jouerAuJeuDePlis(jeuDeCartes);
                    break;
                case 5:
                    continuer = false;
                    System.out.println("Au revoir !");
                    break;
                default:
                    System.out.println("Choix invalide !");
            }
        }
        scanner.close();
    }

    // Créer un jeu de cartes
    public static ArrayList<Carte> creerJeuDeCartes() {
        String[] valeurs = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As"};
        String[] couleurs = {"Coeur", "Carreau", "Trefle", "Pique"};
        ArrayList<Carte> jeuDeCartes = new ArrayList<>();

        for (String couleur : couleurs) {
            for (String valeur : valeurs) {
                jeuDeCartes.add(new Carte(valeur, couleur));
            }
        }
        return jeuDeCartes;
    }

    // Afficher les cartes
    public static void afficherCartes(ArrayList<Carte> jeuDeCartes) {
        for (Carte carte : jeuDeCartes) {
            System.out.println(carte);
        }
    }

    // Distribuer les cartes
    public static void distribuerCartes(ArrayList<Carte> jeuDeCartes) {
        Collections.shuffle(jeuDeCartes);
        int nbJoueurs = 4;
        ArrayList<ArrayList<Carte>> mainsJoueurs = new ArrayList<>();

        for (int i = 0; i < nbJoueurs; i++) {
            mainsJoueurs.add(new ArrayList<>());
        }

        int joueurIndex = 0;
        for (Carte carte : jeuDeCartes) {
            mainsJoueurs.get(joueurIndex).add(carte);
            joueurIndex = (joueurIndex + 1) % nbJoueurs;
        }

        for (int i = 0; i < nbJoueurs; i++) {
            System.out.println("Main du Joueur " + (i + 1) + ":");
            for (Carte carte : mainsJoueurs.get(i)) {
                System.out.println(carte);
            }
            System.out.println();
        }
    }



    // Comparer deux cartes
    public static int comparerCartes(Carte carte1, Carte carte2) {
        String[] valeurs = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Valet", "Dame", "Roi", "As"};
        int valeurIndex1 = 0;
        int valeurIndex2 = 0;

        for (int i = 0; i < valeurs.length; i++) {
            if (carte1.getValeur().equals(valeurs[i])) {
                valeurIndex1 = i;
            }
            if (carte2.getValeur().equals(valeurs[i])) {
                valeurIndex2 = i;
            }
        }
        if (valeurIndex1 > valeurIndex2){
            System.out.println("la carte 1: " + valeurs[valeurIndex1] + " est la plus forte");
        } else if (valeurIndex1 < valeurIndex2) {
            System.out.println("la carte 2: " + valeurs[valeurIndex2] + " est la plus forte");
        } else  {
            System.out.println("la carte 1 et 2 sont ex-aequo");
        }
        return Integer.compare(valeurIndex1, valeurIndex2);
    }

    // Jouer au jeu de plis
    public static void jouerAuJeuDePlis(ArrayList<Carte> jeuDeCartes) {
        Scanner scanner = new Scanner(System.in);
        int nbJoueurs = 4;
        ArrayList<ArrayList<Carte>> mainsJoueurs = new ArrayList<>();
        for (int i = 0; i < nbJoueurs; i++) {
            mainsJoueurs.add(new ArrayList<>());
        }

        ArrayList<ArrayList<Carte>> plis = new ArrayList<>(); // Tableau pour stocker les cartes de chaque pli

        // Distribuer les cartes
        Collections.shuffle(jeuDeCartes);
        int joueurIndex = 0;
        for (Carte carte : jeuDeCartes) {
            mainsJoueurs.get(joueurIndex).add(carte);
            joueurIndex = (joueurIndex + 1) % nbJoueurs;
        }

        int indexJoueurGagnant = -1; // Déclaration de l'indice du joueur gagnant

        // Jouer au jeu de plis
        for (int i = 0; i < 13; i++) {
            Carte carteLaPlusHaute = null;

            // Déclaration de la liste pliActuel pour chaque pli
            ArrayList<Carte> pliActuel = new ArrayList<>();

            for (int j = 0; j < nbJoueurs; j++) {
                System.out.println("Joueur " + (j + 1) + ", veuillez jouer une carte (entrez l'index de la carte):");
                afficherCartesAvecIndex(mainsJoueurs.get(j));
                int indexCarteJouee = scanner.nextInt();
                Carte carteJouee = mainsJoueurs.get(j).remove(indexCarteJouee);
                pliActuel.add(carteJouee); // Ajouter la carte jouée au pli

                if (carteLaPlusHaute == null || comparerCartes(carteJouee, carteLaPlusHaute) > 0) {
                    carteLaPlusHaute = carteJouee;
                    indexJoueurGagnant = j;
                }
            }

            System.out.println("Le joueur " + (indexJoueurGagnant + 1) + " remporte le pli avec la carte " + carteLaPlusHaute);
            plis.add(pliActuel); // Ajouter le pli au tableau des plis
        }

        // Ajouter les cartes des plis au joueur gagnant
        for (ArrayList<Carte> pli : plis) {
            mainsJoueurs.get(indexJoueurGagnant).addAll(pli);
        }

        // Afficher les mains des joueurs après le jeu de plis
        for (int i = 0; i < nbJoueurs; i++) {
            System.out.println("Main du Joueur " + (i + 1) + ":");
            for (Carte carte : mainsJoueurs.get(i)) {
                System.out.println(carte);
            }
            System.out.println();
        }

        //scanner.close();
    }




    // Fonction pour afficher les cartes avec leurs index
    public static void afficherCartesAvecIndex(ArrayList<Carte> cartes) {
        for (int i = 0; i < cartes.size(); i++) {
            System.out.println(i + ": " + cartes.get(i));
        }
    }



}
