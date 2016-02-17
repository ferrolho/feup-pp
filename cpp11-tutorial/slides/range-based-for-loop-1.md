<h2>range-based for loop</h2>

<h4>accessing a vector</h4>

C++ 03
```c++
for (unsigned int i = 0; i < vec.size(); i++)
	cout << vec[i] << endl;
```

C++ 11
```c++
for (unsigned int x : vec)
	cout << x << endl;
```

```c++
for (auto x : vec)
	cout << x << endl;
```

<aside class="notes">
</aside>
