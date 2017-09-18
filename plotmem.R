revmem <- read.table('allsyncycmem.csv', sep = ",")
colnames(revmem) <- paste("",seq(5,50), sep = "")
allrevmem <- revmem[, seq(1, 46, 5)]
allrevmem <- allrevmem/1024 # For KB to MB conversion
allrevmem$k=seq(1,6)
melted = melt(allrevmem, id.vars = "k")
colnames(melted) <- c("k", "n", "mem")
melted$k <- as.factor(melted$k)
g<-ggplot(data=melted, aes(x=n, y=mem))+geom_line(aes(color=k, group=k))+
  geom_point(size=2, aes(group=k))+
  scale_y_log10(limits=c(1e0, 3e4)) + ylab("Memory (MB)") + xlab("Network size (n)")+
  theme(axis.text=element_text(size=12),
        axis.title=element_text(size=14,face="bold"))
print(g)


