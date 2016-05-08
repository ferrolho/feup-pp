<h3>delete</h3>

C++11
```c++
class Person {
	public:
		Person(int age) {};
		Person(double) = delete;
		Person& operator= (const Person&) = delete;
};

Person joao(2);
Person henrique(4.0); // error: use of deleted function ‘Person::Person(double)’
joao = henrique; // error: use of deleted function ‘Person& Person::operator=(const Person&)’
```

<p class="fragment">compile-time errors </p>

<aside class="notes">
</aside>