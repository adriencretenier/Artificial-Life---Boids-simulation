#pragma once
#include <SDL3/SDL.h>
#include "Vec2.hpp"

// Forward declaration pour éviter les inclusions circulaires avec Game
class Game;

/**
 * @brief Classe de base abstraite représentant tout objet du jeu.
 */
class Entity {
protected:
    Vec2f position;
    Vec2f velocity;

public:
    Entity(float x, float y) : position(x, y), velocity(0, 0) {}

    /**
     * @brief Destructeur virtuel.
     * CRUCIAL : Assure que le destructeur de la classe fille (Boid) est bien appelé
     * quand on supprime un objet via un pointeur Entity*.
     */
    virtual ~Entity() = default;

    /**
     * @brief Met à jour la logique de l'entité.
     * Méthode VIRTUELLE PURE (= 0) : rend la classe abstraite.
     * Chaque entité doit définir sa propre façon de bouger.
     * @param dt Temps écoulé depuis la dernière frame (delta time).
     * @param game Référence vers le jeu pour accéder aux voisins/config.
     */
    virtual void update(float dt, const Game& game) = 0;

    /**
     * @brief Dessine l'entité.
     * Méthode virtuelle pure.
     */
    virtual void draw(SDL_Renderer* renderer) const = 0;

    // Getters
    Vec2f getPosition() const { return position; }
    Vec2f getVelocity() const { return velocity; }
};
