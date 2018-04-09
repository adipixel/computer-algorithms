def insertionSort(arr):
  for i in range(1, len(arr)):
    j = i
    for x in range(i-1, -1, -1):
      if arr[j] < arr[x]:
        temp = arr[j]
        arr[j] = arr[x]
        arr[x] = temp
        j -= 1
  
  return arr


def main():
  arr = [12, 11, 13, 5, -2, 6]
  print(insertionSort(arr))
main()
