/*
 * Course: COEN 2220 - Programming 2
 * Name: Eduardo D. Vega Rodriguez
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic queue of tutoring requests
 * Due date: 10/24/2026
 */

#include <iostream>
#include <string>
using namespace std;

class TutoringQueue
{
private:
    struct Node
    {
        string studentId; // Store one student waiting for tutoring.
        Node *next;       // Point to the student immediately behind this one.
    };

    Node *front; // Point to the student who must be served next.
    Node *rear;  // Point to the student most recently added.

public:
    TutoringQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~TutoringQueue()
    {
        while (front != nullptr)
        {
            Node *nodeToDelete = front;
            front = front->next; // Advance before releasing the current node.
            delete nodeToDelete;
        }

        rear = nullptr;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    // ===== Part E: Dynamic Queue Operations =====

    // Adds a new student to the end of the queue.
    void enqueue(const string& newStudentId)
    {
        // Create a new node.
        Node *newNode = new Node;

        // Store the student ID.
        newNode->studentId = newStudentId;

        // The new node does not point to another node yet.
        newNode->next = nullptr;

        // Check if the queue is empty.
        if (rear == nullptr)
        {
            // The new student becomes the first and last student.
            front = newNode;
            rear = newNode;
            return;
        }

        // Connect the last node to the new node.
        rear->next = newNode;

        // Update rear to point to the new last student.
        rear = newNode;
    }

    // Removes the first student from the queue.
    bool dequeue(string& servedStudentId)
    {
        // Check if the queue is empty.
        if (isEmpty())
        {
            return false;
        }

        // Save the first node before removing it.
        Node *nodeToDelete = front;

        // Save the ID of the student being served.
        servedStudentId = front->studentId;

        // Move front to the next student.
        front = front->next;

        // If the queue becomes empty, reset rear.
        if (front == nullptr)
        {
            rear = nullptr;
        }

        // Delete the old first node.
        delete nodeToDelete;

        return true;
    }
};

int main()
{
    cout << boolalpha;

    // Create a tutoring queue.
    TutoringQueue tutoringQueue;

    // Variable to store the served student ID.
    string servedStudentId;

    // Add students in arrival order.
    tutoringQueue.enqueue("TU-301");
    tutoringQueue.enqueue("TU-318");
    tutoringQueue.enqueue("TU-327");

    // Serve the first student.
    if (tutoringQueue.dequeue(servedStudentId))
    {
        cout << "Served student: "
             << servedStudentId << endl;
    }

    // Serve the second student.
    if (tutoringQueue.dequeue(servedStudentId))
    {
        cout << "Served student: "
             << servedStudentId << endl;
    }

    // Serve the last student.
    if (tutoringQueue.dequeue(servedStudentId))
    {
        cout << "Served student: "
             << servedStudentId << endl;
    }

    // Check if the queue is empty.
    cout << "Queue empty: "
         << tutoringQueue.isEmpty() << endl;

    // Add another student after the queue becomes empty.
    tutoringQueue.enqueue("TU-340");

    // Serve the new student.
    if (tutoringQueue.dequeue(servedStudentId))
    {
        cout << "Served student after empty queue: "
             << servedStudentId << endl;
    }

    return 0;
}

/*
 * Analysis Answers
 *
 * E1 — First arrival
 * Why must the first call to enqueue assign newNode to both front and rear?
 * Answer:
 * The first call to enqueue must assign newNode to both front and rear because the queue is empty.
 * The new node becomes the first and last student in the queue.
 * Both pointers need to point to the same node.
 *
 * E2 — Last departure
 * After dequeue removes the only remaining node, what must happen to rear and why?
 * Answer:
 * After removing the last node rear must be set to nullptr.
 * This is because the queue is now empty and there are no more students waiting. 
 * If rear is not nullptr it could point to a node that was already deleted.
 *
 * E3 — FIFO evidence
 * List the expected service order for TU-301, TU-318, and TU-327. Explain why this
 * differs from the return order of the function-call stack in Part D.
 * Answer:
 * The students are served in this order: TU-301 TU-318 and TU-327. 
 * This happens because the queue uses FIFO meaning the first student added is the first one served.
 * In Part D the stack uses LIFO meaning the last function added is the first one removed.
 */