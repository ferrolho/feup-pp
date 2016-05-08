<h3>override</h3>

C++11
```c++
class Old {
	virtual void A(int i);
	virtual void B() const;
	void C();
};

class New : public Old{
	virtual void A(float) override; // error: no function to override
	virtual void B() override; // error: no function to override
	void C() override; // error: no function to override
};
```

<p class="fragment">compile-time errors </p>

<aside class="notes">
	In this example the function A is wrong because the signature of function A of the class New is different from the parent Old.
	The function B of class New is missing the const word so it's impossible to recognize the function of the parent class.
	The function C is not virtual so we cannot use override type to override a function like that.
</aside>