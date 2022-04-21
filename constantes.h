#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

enum Etat_fourmiliere{FREE, CONSTRAINED};
enum Etat_collector{EMPTY, LOADED};

constexpr short unsigned g_dim(7);
constexpr short unsigned g_max(128);
constexpr short unsigned maxF(25);
constexpr short unsigned sizeG(5);
constexpr short unsigned sizeC(3);
constexpr short unsigned sizeD(3);
constexpr short unsigned sizeP(1);
constexpr short unsigned resolution(8);

constexpr short unsigned bug_life(300);

constexpr short unsigned val_food(50);

constexpr double food_rate(0.1);
constexpr double max_food_trial(10);
constexpr double birth_rate(0.00005);
constexpr double prop_free_collector(0.85);
constexpr double prop_free_defensor(0.10);
constexpr double prop_constrained_collector(0.6);
constexpr double prop_constrained_defensor(0.1);

constexpr int errorCode(-1);

constexpr char emptyCST(static_cast<char>(0x00));
constexpr char nourritureCST(static_cast<char>(0x01));
constexpr char fourmilliereCST(static_cast<char>(0x02));
constexpr char fourmiCST(static_cast<char>(0x04));
constexpr char fourmiGeneratorCST(static_cast<char>(0x08));
constexpr char fourmiDefensorCST(static_cast<char>(0x10));
constexpr char fourmiPredatorCST(static_cast<char>(0x20));
constexpr char fourmiCollectorCST(static_cast<char>(0x40));
constexpr char anyCST(static_cast<char>(0xFD)); // match anything execpt anthills
constexpr char allCST(static_cast<char>(0xFF)); // match anything

#endif // CONSTANTES_H_INCLUDED
