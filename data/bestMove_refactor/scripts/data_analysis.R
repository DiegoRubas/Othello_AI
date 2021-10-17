library(iterators)
library(Matrix)
files <- list.files("measurements/")
nmin = 8
nmax = 32 
num = nmax-nmin
sort(files)
files_it = iter(files)
i=10
N <- matrix(0, 1, num)
M <- matrix(0, 1, num)

res = read.csv("measurements/time_data8.csv")
M[1]=max(res[1], res[2])
res = read.csv("measurements/time_data9.csv")
M[2] = max(res[1], res[2])
n=3
while( i<=nmax){
  N[n]=i
  res=read.csv(paste("measurements/",nextElem(files_it), sep=""))
  size=length(res[,1])
  size = size-2
  res = res[1:size,]
  
  M[n]=max(res[1], res[2])
  n=n+1
  i = i +1
}



library(ggplot2)
plot(N,M)
data_array <- matrix(0, 25, 2)
data_array[,1]<-N
data_array[,2]<-M

res = read.csv("final_results.csv")
res$N <- N
res$t <- M

N = res$N
t = res$t

plot(res$N, res$t)
p <- ggplot(data=res, aes(x=N, y=t)) + geom_line()
p
