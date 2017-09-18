revtime <- read.table('allsyncyctime.csv', sep = ",")
colnames(revtime) <- paste("",seq(5,50), sep = "")
allrevtime <- revtime[, seq(1, 46, 5)]
allrevtime$k=seq(1,6)
melted = melt(allrevtime, id.vars = "k")
colnames(melted) <- c("k", "n", "time")
melted$k <- as.factor(melted$k)
g<-ggplot(data=melted, aes(x=n, y=time))+geom_line(aes(color=k, group=k))+
geom_point(size=2, aes(group=k))+
scale_y_log10(limits=c(0.01, 1e4)) + ylab("Time (s)") + xlab("Network size (n)")+
  theme(axis.text=element_text(size=12),
        axis.title=element_text(size=14,face="bold"))
print(g)


