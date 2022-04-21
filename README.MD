this project is a 2D grid simulation where "ants" fight for resosurces


```
                                                   ┌────────┐
                                                   │        │
                                                   │ projet │
                                                   │        │
                                                   └───┬────┘
                                                       │
                                                       │
                                                   ┌───┴───────────────┐
                                                   ▼                   ▼
                          ┌─────────────┐    ┌────────────┐         ┌─────┐
                          │             │    │            │         │     │
                          │ textstorage │◄───┤ simulation │◄────────┤ gui │
                          │             │    │            │         │     │
                          └─────┬───────┘    └─────┬─────┬┘         └──┬──┘
                                │                  │     │             │
                                └─────────┬────────┘     │             │
                                          │              │             │
   ┌────────────┬───────────────┬─────────┴─────┐        │             │
   │            │               │               │        │             │
   │            │               │               │        │             │
   │            ▼               ▼               ▼        │             │
   │     ┌──────────────┐     ┌────────┐  ┌────────────┐ │             │
   │     │              │     │        │  │            │ │             │
   │     │ fourmilliere ├────►│ fourmi │  │ nourriture │ │             │
   │     │              │     │        │  │            │ │             │
   │     └─────┬────────┘     └─┬──────┘  └──────┬─────┘ │             │
   │           │                │                │       │             │
   │           └────────────────┼────────────────┘       │             │
   │                            │                        │             ├────────┐
   │ ┌───────────────┬──────────┴──────┬───────────┐     │             │        │
   │ │               │                 │           │     │             │        │
   ▼ ▼               ▼                 │           ▼     ▼             ▼        │
┌─────────┐     ┌────────────┐         │          ┌─────────┐     ┌─────────┐   │
│         │     │            │         │          │         │     │         │   │
│ entity  │     │ squarecell │         │          │ message │     │ graphic │   │
│         │     │            │         │          │         │     │         │   │
└─────────┘     └────┬───┬───┘         │          └─────────┘     └─┬──────┬┘   │
                     │   │             │                            │      │    │
                     │   │             │                            │      │    │
                     │   └───────┐     │  ┌─────────────────────────┘      │    │
                     ▼           ▼     ▼  ▼                                ▼    ▼
          ┌──────────────────┐  ┌───────────┐                              ┌───────┐
          │                  │  │           │                              │       │
          │ error_squarecell │  │ constante │                              │ GTKmm │
          │                  │  │           │                              │       │
          └──────────────────┘  └───────────┘                              └───────┘
```


Projet : Main file, process command line argument, call the gui and the simulation

gui : display a windows, link the button with the simulation fonction,

graphics : display the physical grid read from squarecell

simulation : iterrate over every fourmiliere for refresh, generate food, read and write simulation to file

fourmillièere : fonction relative to fourmiliere, update les fourmis qui lui sont propre keep track of food and such

fourmi : classe hérité de fourmi pour chaque type de fourmis, methode update pour les faire bouger, pathplanning for food, etc

nourriture : fonction pour update la bouffe sur le plateau

squarecell : methode générique pour les test de collission et distance

message : message to display

error_squarecell : error to display

entity : generic class that all entity inherit from to share some common interface

textstorage : function to export the simulation state to a file and import it back

GTKmm : graphic library for the GUI

constante : global constante to projet