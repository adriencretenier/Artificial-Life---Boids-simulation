#pragma once
#include <cmath>

/**
 * @brief Structure vecteur générique.
 * Permet d'utiliser des vecteurs de float, double, ou int sans réécrire le code.
 * @tparam T Le type de données (ex: float, double).
 */
template <typename T>
struct Vec2 {
    T x, y;

    // Constructeur par défaut et paramétré
    Vec2(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}

    // --- Surcharge d'opérateurs pour simplifier la syntaxe mathématique ---

    Vec2 operator+(const Vec2& o) const { return { x + o.x, y + o.y }; }
    Vec2 operator-(const Vec2& o) const { return { x - o.x, y - o.y }; }
    Vec2 operator*(T s) const { return { x * s, y * s }; }

    // Division sécurisée (le code appelant doit éviter la division par zéro)
    Vec2 operator/(T s) const { return { x / s, y / s }; }

    // Opérateur d'assignation composée
    Vec2& operator+=(const Vec2& o) { x += o.x; y += o.y; return *this; }

    // --- Méthodes utilitaires géométriques ---

    // Retourne la norme au carré (plus rapide, évite la racine carrée)
    float norm2() const { return (float)(x * x + y * y); }

    // Retourne la longueur du vecteur
    float norm() const { return std::sqrt(norm2()); }

    // Retourne un vecteur de longueur 1 (direction pure)
    Vec2 normalized() const {
        float n = norm();
        if (n <= 1e-8f) return { 0, 0 }; // Protection contre division par zéro
        return { x / n, y / n };
    }

    // Limite la longueur du vecteur à une valeur maximale (utile pour la vitesse max)
    void limit(float maxLen) {
        float n2 = norm2();
        if (n2 > maxLen * maxLen) {
            float n = std::sqrt(n2);
            if (n > 1e-8f) {
                x = (T)(x * maxLen / n);
                y = (T)(y * maxLen / n);
            }
        }
    }
};

// Alias de type pour une utilisation facile avec des floats
using Vec2f = Vec2<float>;