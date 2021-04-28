count = 0
Arr = []
idealLst = []
lst = []

n = int(input("Enter number of elements : "))
str1 = input("Enter 1's and 0's without any space : ")
for i in range(n):
    Arr.append(int(str1[i]))
    if(int(str1[i]) == 1):
        lst.append(i)
        idealLst.append(count)
        count += 1

prevNetDiff = 100000000000
currNetDiff = 0
idealNetDiff = 0

for i in range(n - count + 1):
    for j in range(count):
        currNetDiff += abs(lst[j] - idealLst[j])
    
    if currNetDiff < prevNetDiff:
        idealNetDiff = currNetDiff
        prevNetDiff = currNetDiff
    else:
        break
    print(idealLst)
    currNetDiff = 0
    for k in range(count):
        idealLst[k] += 1
        
print("Least no. of steps is : ", idealNetDiff)