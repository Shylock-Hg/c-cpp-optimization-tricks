The c/c++ optimization tricks
=================================

Introduction
--------------------

This is the note about my tricks to optimize c/c++ program.On the top,the
software optimization often follow the path as below:

+----------+-----------+-------------+
|          | order     | coefficient |
+----------+-----------+-------------+
| time     | Algorithm | Tricks      |
+----------+-----------+-------------+
| space    | Algorithm | Tricks      |
+----------+-----------+-------------+

So in this book we concern the Optimization Tricks in c/c++ program.

Tricks List
----------------------

000. Memory Padding

001. Restrict Modifier

002. Inline or Macro Function

003. Tail Function Optimization

004. Noexcept

005. Continuous Memory

006. Conditional Branch Prediction

007. Bit Operator

008. Constexpr

009. Emplace API

010. Empty Array In Struct

011. Function calling

