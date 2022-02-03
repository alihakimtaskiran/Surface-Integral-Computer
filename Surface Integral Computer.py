import open3d as o3d
import numpy as np
import os




pcd = o3d.io.read_triangle_mesh("ball.ply")
pcd = pcd.sample_points_poisson_disk(5000)
pcd.normals = o3d.utility.Vector3dVector(np.zeros((1, 3))) 
pcd.estimate_normals()
pcd.orient_normals_consistent_tangent_plane(100)
points=np.asarray(pcd.points)
pcd_normals=np.asarray(pcd.normals)
np.savetxt("points.csv", points, delimiter=",")
np.savetxt("normals.csv", pcd_normals, delimiter=",")

del points, pcd_normals
__=os.listdir()
if not "out.txt" in __:
    file=open("out.txt","w")
    file.close()


os.system("./backend")
val=0

with open("out.txt") as file:
    val=float(file.read())
    file.close()
    
print(val)
o3d.visualization.draw_geometries([pcd], point_show_normal=True)
