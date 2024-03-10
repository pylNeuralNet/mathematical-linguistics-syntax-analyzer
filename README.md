# Introduction
Bluntly, the task is to create a program that checks if an expression follows a set of grammatical rules written in a specific notation (EBNF).

The grammar can contain rules for an arithmetic expression. If it also regulates the use of nested brackets, its more of a Context Free Grammar than a Regular Expression (see Chomsky's Hierarchy; btw there are people who dedvelop a Theory of Everything with elements of mathematical linguistics and metaphysics so it's kinda cool).

# Task
For example we have a grammar like below

```
S ::= W ; Z
Z ::= W ; Z | ε
W ::= P | POW
P ::= R | (W)
R ::= L | L.L
L ::= C | CL
C ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
O ::= * | : | + | - | ˆ
```

and we want to check if an expression like `(1.2*3)+5-(23.4+3)^3;8:3;` is written according to those rules, syntaxically.

# LL(1) Grammar
For a one-symbol look-ahead without backtracking algorithm to be applicable to analyse the syntax of grammar S, the grammar must be LL(1).

Grammar S is not LL(1). (I Grammar Rule, II Grammar Rule)

That's why it needs to be fixed first. After fixing (I won't show all the steps) by applying Factorization and Right-sided Recurrency, the grammar is as follows:

```
S ::= W; { W; }
W ::= P | W'
W' ::= OW | ε
P ::= R | (W)
R ::= LR’
R’ ::= .L | ε
L ::= C { C }
C ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
O ::= * | : | + | - | ^
```

# Algorithm design
Based on the fixed grammar and after reducing the recurrent calls in it, we could arrive at the following diagrams:
![grammar S diagram](https://github.com/pylNeuralNet/mathematical-linguistics-syntax-analyzer/Diagrams/S.png "S.png")
![production W diagram](https://github.com/pylNeuralNet/mathematical-linguistics-syntax-analyzer/Diagrams/W.png "W.png")
ISO-14977 EBNF

The code is written as the diagrams show.