import itertools
from math import comb
import os
from sys import argv

import numpy as np


def main():
    
    if len(argv)!=4:
        print("parameter should be 3: graph_name, n_nodes, n_edges")
        return
    
    _,graph_name,n_nodes, n_edges=argv
    
    if int(n_edges)>comb(int(n_nodes),2):
        print("n_edges should be <="+str(comb(int(n_nodes),2)))
        return
    
    print("generating full graph...")
    
    pairs=itertools.combinations(range(int(n_nodes)),2)
    
    l=np.array([str(pair[0])+" "+str(pair[1])+"\n" for pair in pairs])
    
    print("removing edges...")
    indexes=np.random.randint(0, comb(int(n_nodes),2), comb(int(n_nodes),2)-int(n_edges) )
    l=np.delete(l,indexes)
    
    PATH = os.getcwd()+"/"+graph_name
    
    if not os.path.exists(PATH):
        os.mkdir(PATH)

    print("generating files...")
    with open(graph_name+"/edges.txt", "w") as edges:
        edges.writelines(l)
        
    with open(graph_name+"/nodes.txt", "w") as nodes:
        nodes.write(n_nodes)
    
    print("END")
if __name__ == '__main__':
    main()