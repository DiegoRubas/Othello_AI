data5_1 = read.csv('5vs5_normal.csv')
data5_2 = read.csv('6vs6_pruning_basic.csv')
data5_3 = read.csv('6vs6_pruning_advanced.csv')

mean5_2_1 = data5_2$a1
mean5_2_2 = data5_2$a2
m521 = mean(mean5_2_1)
m522 = mean(mean5_2_2)

mean5_3_1 = data5_3$a1
mean5_3_2 = data5_3$a2
m531 = mean(mean5_3_1)
m532 = mean(mean5_3_2)


max(mean5_2_1)
max(mean5_2_2)



max(mean5_3_1)
max(mean5_3_2)



