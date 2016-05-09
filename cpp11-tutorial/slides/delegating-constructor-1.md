<h2>delegating constructor</h2>

JAVA
```java
class Person {
	Person();
	Person(int age) { Person(); doOtherThings(age); }
}
```

<p class="fragment">It'd be great if we could use something like this in C++, right?</p>

<aside class="notes">
Very common constructors share the same code, but this is not possible in CPP unless we create two different objects first.
</aside>