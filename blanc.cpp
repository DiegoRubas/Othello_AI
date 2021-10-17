#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::getline;

int main()
{
	string nom_fichier_noir("./noir.txt");
	string nom_fichier_blanc("./blanc.txt");
	string repliques_blanc[]={
"What?",
"I have no quarrel with you, good Sir knight, but I must cross this bridge.",
"I command you as King of the Britons to stand aside!",
"So be it! [ARTHUR chops the BLACK KNIGHT's left arm off] Now stand aside, worthy adversary.",
"A scratch? Your arm's off!",
"Well, what's that then?",
"You liar!",
"[ARTHUR chops the BLACK KNIGHT's right arm off] Victory is mine! [kneeling] We thank thee Lord, that in thy merc-",
"What?",
"You are indeed brave, Sir knight, but the fight is mine.",
"Look, you stupid bastard, you've got no arms left.",
"Look!",
"Look, stop that.",
"Look, I'll have your leg. Right! [whop]",
"You'll what?",
"What are you going to do, bleed on me?",
"You're a loony.",
"[ARTHUR chops the BLACK KNIGHT's other leg off]",
"Come, Patsy.",
"[THE END]"
};

    ofstream fichier_blanc(nom_fichier_blanc);
	ifstream fichier_noir(nom_fichier_noir);
	while (!fichier_noir.is_open())
	{
		cout << "Attente du joueur noir (fichier noir indisponible)" << endl;
		// Ajout d'une temporisation avant de réessayer
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		fichier_noir.open(nom_fichier_noir);
	}
	
	string replique;
	int i = 0;
	bool joueur_courant = true; // false = 0 = "blanc"; true = 1 = "noir"
	string nom_joueurs[] = {"ARTHUR","BLACK KNIGHT"};

	// Premiere réplique: pas de réplique précédente donc on attend juste que le joueur noir commence en indiquant sa réplique dans fichier_noir
	while (!(getline(fichier_noir, replique)))
	{
		// Echec de la lecture - Effacement des flags d'erreur	
		fichier_noir.clear();
		fichier_noir.sync();
		
		// Ajout d'une temporisation avant de réessayer
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	}
	// On passe au joueur suivant
	joueur_courant = !joueur_courant;
	
	// Le dialogue s'arrête lorsqu'une réplique est "[THE END]"
	while (replique != "[THE END]")
	{
		// Affichage de la dernière réplique
		cout << nom_joueurs[!joueur_courant] << " : " << replique << endl;
		// Ajout d'une temporisation
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		
		if (joueur_courant)
		{
			// Le joueur courant est le noir, le programme lui indique la dernière réplique du joueur blanc dans fichier_blanc.txt
			fichier_blanc << replique << endl;
			// Le programme attend que le joueur noir indique sa réplique dans fichier_noir.txt
			while ( !(getline(fichier_noir, replique)) )
			{
				// Echec de la lecture - Effacement des flags d'erreur		
				fichier_noir.clear();
				fichier_noir.sync();
				// Ajout d'une temporisation avant de réessayer
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
		}
		else
		{
			// Le joueur courant est le blanc, lecture de la nouvelle réplique
			replique = repliques_blanc[i++];
		}

		// On passe au joueur suivant
		joueur_courant = !joueur_courant;
	}

	// Affichage de la dernière réplique ("[THE END]")
	cout << nom_joueurs[!joueur_courant] << " : " << replique << endl;
	// Ajout d'une temporisation
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));

	// Si le joueur courant est l'autre (le noir) on lui indique la dernière réplique ("[THE END]")
	if (joueur_courant)
		fichier_blanc << replique << endl;
	return 0;
}
