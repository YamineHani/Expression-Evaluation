# Stack Implementation using LinkedList and Expression Evaluation

## Overview

This project aims to implement a stack using a linked list and perform expression evaluation using infix-to-postfix conversion and postfix expression evaluation. The stack follows the last-in, first-out (LIFO) principle and supports operations such as push, pop, peek, isEmpty, infix-to-postfix conversion, and postfix expression evaluation.

## Part 1: Stack Implementation

### Functions

1. **Initialize**
    - Prototype: `Stack* initialize();`
    - Description: Initializes an empty stack.

2. **Pop**
    - Prototype: `float pop(Stack *s);`
    - Description: Removes the last inserted element from the stack and returns its value.

3. **Push**
    - Prototype: `void push(Stack *s, float value);`
    - Description: Inserts an element at the top of the stack.

4. **Peek**
    - Prototype: `float peek(Stack *s);`
    - Description: Returns the value of the last inserted element in the stack without removing it.

5. **isEmpty**
    - Prototype: `int isEmpty(Stack *s);`
    - Description: Returns 1 if the stack is empty or 0 otherwise.

## Part 2: Infix to Postfix Conversion

### Function

1. **Infix to Postfix**
    - Prototype: `char* infixToPostfix(char *infix);`
    - Description: Takes an infix expression as input and converts it to postfix. The result is returned as a character array.

## Part 3: Postfix Expression Evaluation

### Function

1. **Evaluate Postfix**
    - Prototype: `float evaluatePostfix(char* postfix);`
    - Description: Takes a postfix expression as input and uses the stack implementation to evaluate the expression. The result is returned as a floating-point number.

## Part 4: Main Program

The main program should take a string as input from the user, convert it to postfix notation using `infixToPostfix()`, and then call `evaluatePostfix()`.

### Cases Handled

- Power operation using '^' with higher priority than other operators.
- Handling single-digit and multi-digit numbers.
- Handling brackets.
- Handling floating-point numbers.
- Handling negative numbers.

## Usage

Compile and run the program. Enter an infix expression when prompted, and the program will output the result of the evaluated expression.

```bash
./expression_evaluation
Enter an infix expression: 3 + (5 * 2) - 7
Result: 6.000000
```

