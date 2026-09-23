#include "Boid.hpp"
#include "Game.hpp" // Nécessaire pour voir la définition complète de Game

Boid::Boid(float x, float y) : Entity(x, y) {}

void Boid::draw(SDL_Renderer* renderer) const {
    // Dessin simple : un carré rouge
    SDL_SetRenderDrawColor(renderer, 255u, 0u, 0u, SDL_ALPHA_OPAQUE);
    SDL_FRect r = { position.x - 3, position.y - 3, 6.0f, 6.0f };
    SDL_RenderFillRect(renderer, &r);
}

void Boid::wrapAround() {
    // Téléportation de l'autre côté de l'écran si on dépasse les limites
    if (position.x < 0.f) position.x += Config::WIDTH;
    if (position.x >= Config::WIDTH) position.x -= Config::WIDTH;
    if (position.y < 0.f) position.y += Config::HEIGHT;
    if (position.y >= Config::HEIGHT) position.y -= Config::HEIGHT;
}

void Boid::update(float dt, const Game& game) {
    const auto& entities = game.getEntities();
    const auto& cfg = game.getConfig();

    // Accumulateurs pour les 3 règles
    Vec2f force_cohesion(0, 0);      // Règle 1: Aller vers le centre de masse
    Vec2f force_separation(0, 0);    // Règle 2: Éviter les collisions
    Vec2f force_alignment(0, 0);     // Règle 3: S'aligner avec la vitesse moyenne

    Vec2f avg_pos(0, 0); // Position moyenne des voisins
    Vec2f avg_vel(0, 0); // Vitesse moyenne des voisins
    int count = 0;      // Nombre de voisins perçus

    // Parcours de toutes les entités pour trouver les voisins
    for (const auto& other_ptr : entities) {
        const Entity* other = other_ptr.get(); // Accès au pointeur brut

        if (other == this) continue; // On s'ignore soi-même

        Vec2f diff = other->getPosition() - position;
        float dist2 = diff.norm2();

        // Si l'entité est dans le rayon de vision
        if (dist2 > 0 && dist2 < cfg.neighbor_radius * cfg.neighbor_radius) {
            avg_pos += other->getPosition();
            avg_vel += other->getVelocity();
            count++;

            // Si l'entité est TROP proche (zone de séparation)
            if (dist2 < cfg.separation_radius * cfg.separation_radius) {
                // Vecteur répulsif inversement proportionnel à la distance
                force_separation += (diff.normalized() * (1.0f / std::sqrt(dist2))) * -1.0f;
            }
        }
    }

    Vec2f accel(0, 0);

    // Si on a des voisins, on applique les forces
    if (count > 0) {
        // 1. Cohésion : vecteur vers le centre moyen
        avg_pos = avg_pos / (float)count;
        force_cohesion = (avg_pos - position) * cfg.k_cohesion;

        // 3. Alignement : vecteur vers la vitesse moyenne
        avg_vel = avg_vel / (float)count;
        force_alignment = (avg_vel - velocity) * cfg.k_alignment;

        // 2. Séparation
        force_separation = force_separation * cfg.k_separation;


        accel = force_cohesion + force_alignment + force_separation;

        // On limite la force pour ne pas avoir de virages instantanés irréalistes
        accel.limit(cfg.max_accel);
    }

    // Intégration
    velocity += accel * dt;
    velocity.limit(cfg.max_speed);
    position += velocity * dt;

    wrapAround();
}