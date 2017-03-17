from collections import defaultdict
import timeit

 
class Graph:
 
    def __init__(self,vertices):
        self.V= vertices 
        self.graph = [] 
        
    def addEdge(self,u,v,w):
        self.graph.append([u, v, w])
         
    def printArr(self, dist):
        print("Vertex   Distance from Source")
        for i in range(self.V):
            print("%d \t\t %d" % (i, dist[i]))

    def BellmanFord(self, src):
 
  
        dist = [float("Inf")] * self.V
        dist[src] = 0
 
 
        for i in range(self.V - 1):
        
            for u, v, w in self.graph:
                if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                        dist[v] = dist[u] + w
 
 
        for u, v, w in self.graph:
                if dist[u] != float("Inf") and dist[u] + w < dist[v]:
                        print "Graph contains negative weight cycle"
                        return
                         
        self.printArr(dist)


v = input("Number of vertices:")
e = input("Number of edges:")
g = Graph(v)
for i in range (e):
    new_edge = raw_input()
    new_edge = new_edge.split()
    src=int(new_edge[0])
    dest=int(new_edge[1])
    cost=int(new_edge[2])
    #dest = input()
    #cost = input()
    g.addEdge(src,dest,cost)
start = timeit.default_timer() 

g.BellmanFord(0)
stop = timeit.default_timer()

print stop - start