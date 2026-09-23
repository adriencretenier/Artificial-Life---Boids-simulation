#pragma once
#include <vector>
#include <memory> 
#include <random>
#include <SDL3/SDL.h>

#include "Config.hpp"
#include "Entity.hpp"

/**
 * @brief Moteur principal du jeu.
 * Gère le cycle de vie de la SDL et des entités.
 */
class Game {
public:
    Game();
    ~Game();

    // Boucle principale
    void run();

    // Accesseurs en lecture seule (const ref) pour les entités
    const std::vector<std::unique_ptr<Entity>>& getEntities() const { return entities; }
    const Config& getConfig() const { return config; }

private:
    void initSDL(); // Peut lancer une exception
    void update(float dt);
    void render();
    void addBoid(float x, float y);

    Config config;

    // Ressources SDL (pointeurs bruts car gérés manuellement dans constructeur/destructeur)
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    bool isRunning = true;

    /**
     * @brief Liste des entités du jeu.
     * unique_ptr assure que la mémoire est libérée automatiquement quand le vecteur est détruit.
     * Le type de base est "Entity" (polymorphisme).
     */
    std::vector<std::unique_ptr<Entity>> entities;

    // Générateur de nombres aléatoires
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<float> rand01{ 0.f, 1.f };
};
