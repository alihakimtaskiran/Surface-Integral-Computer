import open3d as o3d
import numpy as np
import os


class Reality(object):
    def __init__(self,obj_path,resolution=7500):
        if not obj_path[-4:]==".ply":
            raise IOError("Only .ply files supported")
        self.__pcd=o3d.io.read_triangle_mesh(obj_path)
        self.__pcd = self.__pcd.sample_points_poisson_disk(resolution)
        self.__pcd.normals = o3d.utility.Vector3dVector(np.zeros((1, 3))) 
        self.__pcd.estimate_normals()
        self.__pcd.orient_normals_consistent_tangent_plane(100)
        self.__points=np.asarray(self.__pcd.points)
        self.__pcd_normals=np.asarray(self.__pcd.normals)
        self.__res=resolution
    
    def field(self,function):
        function=function[function.index("[")+1:function.index("]")]
        if not function.count(",")==2:
            raise ValueError("Non 3D fields are NOT supported")
        function=function.split(",")
        c_out="#include<cmath> \nfloat fieldX(float x,float y, float z){return "
        c_out+=function[0]+";} float fieldY(float x,float y, float z){return "
        c_out+=function[1]+";}float fieldZ(float x,float y, float z){return "
        c_out+=function[2]+";} "
        file=open("field.c","w")
        file.write(c_out)
        file.close()
        os.system("g++ backend.cpp -o backend")
        file=open("metadata.txt","w")
        file.write(str(self.__res))
        file.close()
    
    def render(self):
        np.savetxt("points.csv", self.__points, delimiter=",")
        np.savetxt("normals.csv", self.__pcd_normals, delimiter=",")
        
        del self.__points, self.__pcd_normals
        __=os.listdir()
        if not "out.txt" in __:
            file=open("out.txt","w")
            file.close()
    
        
        os.system("./backend")
        val=0
        
        with open("out.txt") as file:
            val=float(file.read())
            file.close()
        
        os.remove("out.txt")
        os.remove("points.csv")
        os.remove("normals.csv")
        return val
