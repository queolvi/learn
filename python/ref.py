def change_arr(arr, size):
    for i in range(size) :
         arr[i] += 1

print("enter size")
sizeMain = int(input())

if sizeMain > 10:
    print("size > 10")
elif sizeMain < 10: 
    print("size < 10")
else:
    print("size == 10")

    arrMain = [0] * sizeMain

for i in range(sizeMain):
    arrMain[i] = int(input(f"Enter element {i + 1}: "))

print ("\norig arr:")
for n in arrMain:
    print(n, end=" ")
print()

change_arr(arrMain, sizeMain)

print ("\nchanged arr:")
for n in arrMain:
    print(n, end=" ")
print()


