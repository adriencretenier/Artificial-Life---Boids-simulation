#pragma once

/**
 * @brief Conteneur de constantes et de paramètres de configuration.
 * Regroupe toutes les "magic values" pour faciliter l'équilibrage du jeu.
 */
struct Config {
    // Dimensions de la fenêtre
    static constexpr int WIDTH = 900;
    static constexpr int HEIGHT = 700;

    // Nombre d'agents au démarrage
    static constexpr int N0 = 50;

    // --- Paramètres physiques des Boids ---
    float dt_max = 0.05f;       // Pas de temps maximum (pour éviter les sauts en cas de lag)

    // Coefficients des forces (Pondération des 3 règles de Reynolds)
    float k_cohesion = 0.01f;   // Tendance à aller vers le centre du groupe
    float k_separation = 0.50f; // Tendance à éviter la collision
    float k_alignment = 0.20f;  // Tendance à aller dans la même direction

    float max_speed = 200.f;    // Vitesse max (pixels/sec)
    float max_accel = 400.f;    // Force de direction max

    // Rayons de perception
    float neighbor_radius = 90.f;   // Distance de vue
    float separation_radius = 22.f; // Distance de "bulle" personnelle

    // Affichage
    int boid_draw_radius = 3;
};
