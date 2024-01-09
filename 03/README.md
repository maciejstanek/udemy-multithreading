### Questions

 1. Are there any possible scenarios in which neither thread is able to exit the loop? If so, how could this happen.
    * It is possible that both threads enter the loop, "invert" the value and pause. This would result in the `x` variable value being reset to zero, therefore forcing another run of the `while` loop. To better illustrate the problem, I added `sleep_for` into the loop.
    * In the ideal scenario, I would expect the loop to run only once.
 2. If so, suggest a way to fix the problem.
    * Data races are expected when accessing `x`. Since `x` is used both inside the loop (modification) and in the loop condition (reading), I propose to add a lock right before the loop start.
    * This solution could potentially hurt the performance if we were to introduce some more time-intensive work into the `while` loop, since we essentially eliminate the possibility of running this loop in parallel.

### Result with synchronization

```
0
1
```

### Typical result with no synchronization

```
0
1
0
0
00

1
0
00

1
0
00

1
0
```
