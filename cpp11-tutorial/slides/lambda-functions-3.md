<h2>lambda functions</h2>

<h4>variable capture</h4>

```text
[]           capture nothing

[&]          capture any referenced variable by reference

[=]          capture any referenced variable by making a copy

[=, &foo]    capture any referenced variable by making a copy,
             *but* capture variable foo by reference

[bar]        capture bar by making a copy; don't copy anything else

[this]       capture the this pointer of the enclosing class
```

<aside class="notes">
</aside>
