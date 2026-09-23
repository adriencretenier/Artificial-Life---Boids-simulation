#include <iostream>
#include "Game.hpp"

int main(int argc, char** argv) {
    (void)argc; (void)argv;

    try {
        // Tout le code du jeu est protégé par ce bloc try
        Game boidsGame;
        boidsGame.run();
    }
    catch (const std::exception& e) {
        // Si une exception est lancée (ex: erreur SDL), on l'affiche ici
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return -1;
    }
    catch (...) {
        // Capture "tout le reste" (sécurité)
        std::cerr << "UNKNOWN ERROR OCCURRED." << std::endl;
        return -1;
    }

    return 0;
}