# Lab 36: Closed Hash Table

In this lab, you are to implement a "closed" hash table. It should handle collisions by linear probing for an available bucket. It should provide the following map ADT methods:

* `exists(k)`: Returns true if a value exists for the given key, false otherwise.
* `find(k)`: Returns the value for the given key, or throws an exception if there is no mapping for the key.
* `put(k,v)`: Adds a mapping of the given key to the given value, or replaces the current mapping with the given value if one already exists. An exception should be thrown if adding a new entry would cause the number of slots to exceed the number of buckets.
* `erase(k)`: Removes the mapping for the given key, or throws an exception if no such mapping exists.
* `getSize()`: Returns the current number of mappings in the hashtable.

You can assume that all keys are unique.

When you have implemented all of these methods, run the unit tests and make sure they all pass.

## Requirements

When implementing the hash table, you must:

* Fill in the methods of the provided `ClosedHashMap` class.
* Define each bucket as a `HashtableEntry` struct. This struct has an enum for tracking the used, unused, and available state of the bucket.

## Hints

* Watch out for copy assignment! For example, `HashtableEntry entry = hashtable[i]` creates a copy of the entry. Any modifications then apply to the _copy_ of it, not the one in the hashtable. Instead, try `HashtableEntry& entry = hashtable[i]`.
* To convert a key to an integer, create a [`std::hash`](https://en.cppreference.com/w/cpp/utility/hash) and invoke its function object. For example: `std::hash<K>()(key)`.
