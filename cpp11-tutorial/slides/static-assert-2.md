<h2>static_assert</h2>

C++11
```c++
static_assert(sizeof(void *) == 4, "64-bit code generation is not supported.");

```

```text
A static assert declaration may appear at block
scope (as a block declaration) and inside a class
body (as a member declaration).
```

<aside class="notes">
Is good for testing logic in your code at compilation time.
</aside>
