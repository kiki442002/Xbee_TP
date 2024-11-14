#include "queue.h"

// Ajouter un élément à la file d'attente
bool PriorityQueue::enqueue(String msg, int dl, char ack_to_receive, int priority)
{
    if (count >= QUEUE_SIZE)
    {
        return false; // La file d'attente est pleine
    }
    queue[count] = QueueElement(msg, dl, ack_to_receive, priority);
    count++;
    sortQueue();
    return true;
}

// Retirer l'élément avec la plus haute priorité
bool PriorityQueue::dequeue(QueueElement &msg)
{
    if (count == 0)
    {
        return false; // La file d'attente est vide
    }
    msg = queue[0];
    for (int i = 1; i < count; i++)
    {
        queue[i - 1] = queue[i];
    }
    count--;
    return true;
}

// Vérifier si la file d'attente est vide
bool PriorityQueue::isEmpty() const
{
    return count == 0;
}

// Trier la file d'attente par priorité décroissante
void PriorityQueue::sortQueue()
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