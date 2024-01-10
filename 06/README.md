### Task

Create a consumer and producer threads, the former accepting
a `std::future` and the latter accepting and setting a `std::promise`.

### Example result

```
starting
printer boots up
adder computes the result for "6" and "7"
printer awaits
adder sets the promised value
printer got "13"
```
