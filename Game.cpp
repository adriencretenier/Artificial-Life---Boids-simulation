#include "Game.hpp"
#include "Boid.hpp"
#include <iostream>
#include <stdexcept> 

Game::Game() {
    // Initialisation SDL
    initSDL();

    // Peuplement initial du monde
    for (int i = 0; i < Config::N0; ++i) {
        float x = 100.0f + i * 10.0f;
        float y = 100.0f;

        // make_unique pour créer un objet dynamique
        auto b = std::make_unique<Boid>(x, y);

        // Initialisation vitesse aléatoire
        float a = rand01(rng) * 6.28f;
        float s = 0.4f * config.max_speed;

        // std::move est nécessaire car unique_ptr ne peut pas être copié, seulement déplacé
        entities.push_back(std::move(b));
    }
}

Game::~Game() {
    // Nettoyage manuel de la SDL
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
    // Rq: Le vecteur 'entities' se nettoie tout seul grâce aux unique_ptr
}

void Game::initSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        // On lance une erreur explicite pour être attrapée dans le main
        throw std::runtime_error(std::string("SDL Init Failed: ") + SDL_GetError());
    }

    window = SDL_CreateWindow("Boids OOP & CPP", Config::WIDTH, Config::HEIGHT, 0);
    if (!window) throw std::runtime_error("Window creation failed");

    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) throw std::runtime_error("Renderer creation failed");
}

void Game::addBoid(float x, float y) {
    entities.push_back(std::make_unique<Boid>(x, y));
}

void Game::update(float dt) {
    if (dt > config.dt_max) dt = config.dt_max;

    // Boucle polymorphique : appelle b->update() pour chaque entité
    for (auto& e : entities) {
        e->update(dt, *this);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (const auto& e : entities) {
        e->draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::run() {
    uint64_t last_time = SDL_GetTicks();

    while (isRunning) {
        // Gestion des événements SDL (clavier/souris)
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) isRunning = false;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) isRunning = false;
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                addBoid(event.button.x, event.button.y);
            }
        }

        // Calcul du Delta Time
        uint64_t current = SDL_GetTicks();
        float dt = (float)(current - last_time) / 1000.0f;
        last_time = current;

        update(dt);
        render();

        SDL_Delay(1); // Petite pause pour soulager le CPU
    }
}