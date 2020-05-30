k = int(input())
for i in range(k):
	expr = input()
	max_expr = expr.replace('*',')*(')
	max_expr = '(' + max_expr + ')'
	# print(expr)
	print(eval(expr))
	print(eval(max_expr))