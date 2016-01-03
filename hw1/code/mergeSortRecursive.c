void mergeSortRecursive (Comparable[] data, int left, int right)
  {
    // 1. We will allow left cursor to go past right as one way
    //    to bottom out of recursion.
    if (left >= right)
      return;

    // 2. Handle 2-element case directly:
    if (left+1 == right) {
      if (data[left].compareTo (data[right]) > 0)
        swap (data, left, right);
      return;
    }

    // 3. Find the middle point:
    int middle = (left+right) / 2;

    // 4. Sort the left side, including the middle:
    mergeSortRecursive (data, left, middle);

    // 5. Sort the right side:
    mergeSortRecursive (data, middle+1, right);

    // 6. Merge:
    simpleMerge (data, left, middle, right);
  }