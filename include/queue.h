#ifndef QUEUE_H
#define QUEUE_H

#include <Arduino.h>

#define QUEUE_SIZE 10

// Définir une structure pour les éléments de la file d'attente
struct QueueElement
{
    String msg;
    int dl;
    int priority;

    // Constructeur par défaut
    QueueElement() : msg(""), dl(0), priority(0) {}

    // Constructeur avec paramètres
    QueueElement(String m, int d, int p) : msg(m), dl(d), priority(p) {}
};

// Définir la file d'attente avec priorité
class PriorityQueue
{
private:
    QueueElement queue[QUEUE_SIZE];
    int count;

public:
    // Initialiser la file d'attente
    PriorityQueue() : count(0) {}

    // Ajouter un élément à la file d'attente
    bool enqueue(String msg, int dl, int priority);

    // Retirer l'élément avec la plus haute priorité
    bool dequeue(String &msg, int &dl);

    // Vérifier si la file d'attente est vide
    bool isEmpty() const;

private:
    // Trier la file d'attente par priorité décroissante
    void sortQueue();
};

#endif // QUEUE_H