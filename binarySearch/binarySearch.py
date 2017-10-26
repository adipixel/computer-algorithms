def binarysearch(arr, value):
    arrLen = len(arr)
    
    if arrLen !=0:
        mid = arrLen //2
        if arr[mid] == value:
            return arr[mid]
        elif value < arr[mid]:
            return binarysearch(arr[:mid], value)
        elif value > arr[mid]:
            return binarysearch(arr[mid+1:], value)
        
    else:
        return None

def main():
    arr = [4,3,6,7,2,8,1,5]
    arr.sort()
    
    searchElement = 2
    
    res = binarysearch(arr, searchElement)
    
    if res != None:
        print "Found:",
        print res
    else:
        print "Not Found"


main()
