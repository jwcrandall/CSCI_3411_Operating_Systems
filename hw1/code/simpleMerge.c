void simpleMerge (Comparable[] data, int left, int middle, int right)
  {
    // 1. Create the space and initialize the cursors:
    Comparable[] mergeSpace = new Comparable [right-left+1];
    int leftCursor = left;
    int rightCursor = middle+1;

    // 2. Fill the merge space by one by one, selecting from the correct partition
    for (int i=0; i < mergeSpace.length; i++) {

      if (leftCursor > middle) {
        // 2.1  If left side is done, merge only from right:
        mergeSpace[i] = data[rightCursor];
        rightCursor++;
      }
      else if (rightCursor > right) {
        // 2.2  If right side is done, merge only from left:
        mergeSpace[i] = data[leftCursor];
        leftCursor++;
      }
      else if (data[leftCursor].compareTo (data[rightCursor]) <= 0) {
        // 2.3 Otherwise, if the leftCursor element is less, move it:
        mergeSpace[i] = data[leftCursor];
        leftCursor++;
      }
      else {
        // 2.4 Move from right:
        mergeSpace[i] = data[rightCursor];
        rightCursor++;
      }
    }

    // 3. Copy back into original array:
    for (int i=0; i < mergeSpace.length; i++)
      data[left+i] = mergeSpace[i];
  }