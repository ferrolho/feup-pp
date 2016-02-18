<h2>rvalue reference</h2>

<h4>the usual copy constructor</h4>

```c++
class GiantVector {
	int size;
	double* elems;

public:
	// *COPY* constructor
	GiantVector(const GiantVector& vec) {
		size = vec.size;

		elems = new double[size];

		for (auto i = 0; i < size; i++)
			elems[i] = vec.elems[i];
	}

	~GiantVector() { delete elems; }
}
```

<aside class="notes">
</aside>
