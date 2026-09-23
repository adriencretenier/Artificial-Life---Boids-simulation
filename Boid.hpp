#pragma once
#include "Entity.hpp"
#include "Config.hpp"

/**
 * @brief Représente un "oiseau" spécifique.
 * Hérite de la classe Entity.
 */
class Boid : public Entity {
public:
    Boid(float x, float y);

    // Override indique qu'on réimplémente une méthode virtuelle parente
    void update(float dt, const class Game& game) override;
    void draw(SDL_Renderer* renderer) const override;

private:
    // Gère le passage d'un bord de l'écran à l'autre (tore)
    void wrapAround();
};
