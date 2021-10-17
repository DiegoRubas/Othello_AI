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
	string repliques_noir[]={
"None shall pass.",
"None shall pass.",
"Then you shall die.",
"I move for no man.",
"'Tis but a scratch.",
"No, it isn't.",
"I've had worse.",
"Come on you pansy!",
"Come on then.",
"Have at you!",
"Oh, had enough, eh?",
"Yes I have.",
"Just a flesh wound.",
"Chicken! Chicken!",
"Right, I'll do you for that!",
"Come 'ere!",
"I'm invincible!",
"The Black Knight always triumphs! Have at you! Come on then.",
"All right; we'll call it a draw.",
"Oh, oh, I see, running away then. You yellow bastards! Come back here and take what's coming to you. I'll bite your legs off!",
"[THE END]"
	};

    ofstream fichier_noir(nom_fichier_noir);
	ifstream fichier_blanc(nom_fichier_blanc);
	while (!fichier_blanc.is_open())
	{
		cout << "Attente du joueur blanc (fichier blanc indisponible)" << endl;
		// Ajout d'une temporisation avant de réessayer
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		fichier_blanc.open(nom_fichier_blanc);
	}
	
	string replique;
	int i = 0;
	bool joueur_courant = true; // false = 0 = "blanc"; true = 1 = "noir"
	string nom_joueurs[] = {"ARTHUR","BLACK KNIGHT"};


	// Premiere réplique: pas de réplique précédente donc le joueur noir choisit directement sa réplique
	replique = repliques_noir[i++];
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
			// Le joueur courant est le noir, lecture de la nouvelle réplique
			replique = repliques_noir[i++];
		}
		else
		{
			// Le joueur courant est le blanc, le programme lui indique la dernière réplique du joueur noir dans fichier_noir.txt
			fichier_noir << replique << endl;
			// Le programme attend que le joueur blanc indique sa réplique dans fichier_blanc.txt
			while (!(getline(fichier_blanc, replique)))
			{
				// Echec de la lecture - Effacement des flags d'erreur			
				fichier_blanc.clear();
				fichier_blanc.sync();
				// Ajout d'une temporisation avant de réessayer
				std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			}
		}

		// On passe au joueur suivant
		joueur_courant = !joueur_courant;
	}
	
	// Affichage de la dernière réplique ("[THE END]")
	cout << nom_joueurs[!joueur_courant] << " : " << replique << endl;
	// Ajout d'une temporisation
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	
	// Si le joueur courant est l'autre (le blanc) on lui indique la dernière réplique ("[THE END]")
	if (!joueur_courant)
		fichier_noir << replique << endl;
	return 0;
}
