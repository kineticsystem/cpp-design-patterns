# cpp-design-patterns

An ongoing implementation of common Design Patterns in C++.

**Factory1**

An abstract class Animal and a few concrete implementation Dog and Cat, an abstract AnimalFactory and a few concrete implementations DogFactory and CatFactory which return smart pointers.

**StepBuilder1-3**

A step builder which constructs an Animal object with mandatory parameters, implemented using a chain of classes extending each others.

A more readable step builder which constructs an Animal object with mandatory parameters, implemented using a set of classes and reinterpret_cast.

A step builder using reinterpret_cast and unique smart pointers.

**Injection1-6**

Different examples of dependency injection: Pure (or Poor Man's), Bastard, Optional and Builder-Based Dependency Injection.

