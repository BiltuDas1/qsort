print("Input number one: ")
try:
	a=int(input())
except ValueError:
	print("Invalid input, please enter a numeric value")
	exit(1)
print("Input number two: ")
try:
	b=int(input())
except ValueError:
	print("Invalid input, please enter a numeric value")
	exit(1)
result=a+b
print("Addition of two numbers are: {}".format(result))
