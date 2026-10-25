/*
 * Course: COEN 2220 - Programming 2
 * Name: Eduardo D. Vega Rodriguez
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic stack of active function calls
 * Due date: 10/24/2026
 */

#include <iostream>
#include <string>
using namespace std;

class FunctionCallStack
{
private:
    // ===== Resolve these TODOs now (Part C) =====

    // Define a Node to store each function call.
    struct Node
    {
        string functionName; // Stores the name of the function.
        Node *next;          // Points to the next node in the stack.
    };

    // Points to the node at the top of the stack.
    Node *top;

public:
    // Constructor that starts with an empty stack.
    FunctionCallStack()
    {
        top = nullptr; // No function calls are stored yet.
    }

    // ===== Resolve these TODOs later (Part D) =====

    // Checks if the stack is empty.
    bool isEmpty() const
    {
        return top == nullptr;
    }

    // Adds a new function call to the top of the stack.
    void push(const string& newFunctionName)
    {
        // Create a new node.
        Node *newNode = new Node;

        // Store the function name.
        newNode->functionName = newFunctionName;

        // Connect the new node to the previous top.
        newNode->next = top;

        // Make the new node the top of the stack.
        top = newNode;
    }

    // Removes the function at the top of the stack.
    bool pop(string& removedFunctionName)
    {
        // Check if the stack is empty.
        if (isEmpty())
        {
            return false;
        }

        // Save the current top node.
        Node *nodeToDelete = top;

        // Save the name of the function being removed.
        removedFunctionName = top->functionName;

        // Move top to the next node.
        top = top->next;

        // Delete the old top node.
        delete nodeToDelete;

        return true;
    }

    // Gets the top function without removing it.
    bool peek(string& topFunctionName) const
    {
        // Check if the stack is empty.
        if (isEmpty())
        {
            return false;
        }

        // Copy the name of the top function.
        topFunctionName = top->functionName;

        return true;
    }

    // Destructor deletes all remaining nodes.
    ~FunctionCallStack()
    {
        // Continue until the stack is empty.
        while (top != nullptr)
        {
            // Save the current top node.
            Node *nodeToDelete = top;

            // Move top before deleting the node.
            top = top->next;

            // Free the memory.
            delete nodeToDelete;
        }
    }
};

int main()
{
    cout << boolalpha;

    // ===== Resolve these TODOs later (Part D) =====

    // Create a FunctionCallStack object.
    FunctionCallStack callStack;

    // Add the function calls in order.
    callStack.push("main");
    callStack.push("loadSchedule");
    callStack.push("formatSchedule");

    // Variables to store function names.
    string topFunctionName;
    string removedFunctionName;

    // Show the function currently at the top.
    if (callStack.peek(topFunctionName))
    {
        cout << "Current function: "
             << topFunctionName << endl;
    }

    // Remove the first function.
    if (callStack.pop(removedFunctionName))
    {
        cout << "Returned from function: "
             << removedFunctionName << endl;
    }

    // Remove the second function.
    if (callStack.pop(removedFunctionName))
    {
        cout << "Returned from function: "
             << removedFunctionName << endl;
    }

    // Remove the third function.
    if (callStack.pop(removedFunctionName))
    {
        cout << "Returned from function: "
             << removedFunctionName << endl;
    }

    // Check if the stack is empty.
    cout << "Stack empty: "
         << callStack.isEmpty() << endl;

    // Try to remove a function from an empty stack.
    cout << "Pop from empty stack succeeded: "
         << callStack.pop(removedFunctionName) << endl;

    return 0;
}

/*
 * Analysis Answers
 *
 * D1 — Adding formatSchedule
 * When push("formatSchedule") executes, what must newNode->next receive before top
 * changes? Explain why reversing those two assignments would lose the previous top.
 * Answer:
 * newNode->next must receive the address stored in top before top changes.
 * This connects the new node to the previous top node.
 * If top changes first, we lose the address of the previous top
 * and the new node cannot connect to the rest of the stack.
 *
 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer:
 * The functions are removed in this order: formatSchedule,
 * loadSchedule, and main. This happens because the stack uses
 * LIFO, meaning the last function added is the first one removed.
 * Each pop removes the top node and moves top to the next node.
 *
 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer:
 * The destructor must save the next node address before deleting
 * the current node because deleting it removes access to its data.
 * If we do not save the next address, we could lose access to the
 * remaining nodes and cannot delete them correctly.
 */