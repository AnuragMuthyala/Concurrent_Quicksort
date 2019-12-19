concurrent quicksort

normal quicksort():

The above function performs a normal quicksort i.e
->Consider an array of integers of size n.
->We call the function with array(s),lower(low) and upper(high) bounds as parameters.
->We consider the median as the pivot.
->From the left(i),we search for a number that is greater than the pivot.
->From the right(j),we search for a number which is less than pivot.
->We do this until i > j. Incase i < j,swap elements at i and j ad continue the above steps.
->At the end when i > j, swap pivot and j, return j.
->then we recursively call normal_quicksort() for the parameters,
---array(s),low,j - 1,
---array(s),j + 1,high,

quicksort():

The above function performs the following
->We perform the steps described above.
->During the recursive call,we call two child processes and call the function quicksort()..
