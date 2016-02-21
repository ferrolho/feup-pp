<h2>delegating constructor</h2>

C++03
```c++
class person {
	init() { ... };
	public:
	person() { init(); }
	person(int age) { init();  doOtherThings(age); }
}
```

<p class="fragment">Cumbersome code! </p>

C++11
```c++
class person {
	public:
	person() { ... }
	person(int age) : person() { doOtherThings(age); }
}
```

<p class="fragment">Now it's possible! :D</p>

<aside class="notes">
C++03
So we need an auxiliar function to do that, and that function is represented in the init function, where we call the function in the constructor and we can use the same code.
Cumbersome = pouco prático.

C++11
The first constructor just need to be invoked before the second constructor and we can now use what the first one provides.
We cannot invoke the first constructor at the scope of the second constructor or in its end.
</aside>
