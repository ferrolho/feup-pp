<h2>range-based for loop</h2>

<h4>modifying a vector</h4>

C++ 03
```c++
for (unsigned int i = 0; i < vec.size(); i++)
	vec[i]++;
```

C++ 11
```c++
for (auto& x : vec) // notice the & in `auto&`
	x++;
```

<aside class="notes">
</aside>
