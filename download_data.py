import os
import json
import requests
import gzip
from os import path as path

WD = os.getcwd()
DATA = 'data.json'
GZ_FILE = 'out.gz'
EDGES_FILE = 'edges.txt'
TRIANGLE_FILE = 'triangle.txt'
NODE_FILE = 'nodes.txt'

def main():

    # Read json
    data_json = path.join(WD, DATA)
    file_ = open(data_json)
    data = json.load(file_)
    file_.close()

    # Download data
    for name, info in data.items():
    
        url, n_nodes, n_triangles = info

        # Create directory

        data_dir = path.join(WD, name)

        if not os.path.exists(data_dir):
            os.makedirs(data_dir)

        # Download data and  

        gz_file = path.join(data_dir, GZ_FILE)
        edges_file = path.join(data_dir, EDGES_FILE)
        triangle_file = path.join(data_dir, TRIANGLE_FILE)
        node_file = path.join(data_dir, NODE_FILE)

        response = requests.get(url)
        open(gz_file, "wb").write(response.content)

        op = open(edges_file, "w") 
        with gzip.open(gz_file, "rb") as ip_byte:
            op.write(ip_byte.read().decode("utf-8"))
            op.close()

        os.remove(gz_file)

        with open(triangle_file, "w") as text_file:
            text_file.write(str(n_triangles))
            text_file.close()
            
        with open(node_file, "w") as text_file:
            text_file.write(str(n_nodes))
            text_file.close()    

if __name__ == '__main__':
    main()