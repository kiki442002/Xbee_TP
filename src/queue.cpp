#include "queue.h"

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
    bool enqueue(String msg, int dl, int priority)
    {
        if (count >= QUEUE_SIZE)
        {
            return false; // La file d'attente est pleine
        }
        queue[count] = QueueElement(msg, dl, priority);
        count++;
        sortQueue();
        return true;
    }

    // Retirer l'élément avec la plus haute priorité
    bool dequeue(String &msg, int &dl)
    {
        if (count == 0)
        {
            return false; // La file d'attente est vide
        }
        msg = queue[0].msg;
        dl = queue[0].dl;
        for (int i = 1; i < count; i++)
        {
            queue[i - 1] = queue[i];
        }
        count--;
        return true;
    }

    // Vérifier si la file d'attente est vide
    bool isEmpty() const
    {
        return count == 0;
    }

private:
    // Trier la file d'attente par priorité décroissante
    void sortQueue()
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                if (queue[i].priority < queue[j].priority)
                {
                    QueueElement temp = queue[i];
                    queue[i] = queue[j];
                    queue[j] = temp;
                }
            }
        }
    }
};
