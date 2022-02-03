# Surface-Integral-Computer
   Living in 3D, everything has surfaces. So, surface integrals are fundamental part of electromagnetics. Even though we are familiar with analytical form of electromagnetism, it is not useful when we try to use a computer. On contrary analytical form of equations can be created on paper then once it created, it can be easily computed, complex shaped objects require very large amounts of analytical calculations and it is hard to be done. Discretezation is the key part of the sollution of complexity. No matter how complex is the object, it is represented by finite amounts of points and regardless the shape or the size of the object, operation is always the same. This is why discretization method is used in serface integral computer.
## Docs
### 1.Tree
<pre>
SurfaceIntegralComputer(obj_path,resolution=7500)--|
                                                   |--field(function)
                                                   |--render()
</pre>
### 2.Methods
- <code>**SurfaceIntegralComputer(obj_path,resolution=7500)**</code>. It is an class. <code>obj_path</code> is file path of the **.ply** object. <code> resolution</code> is number of points representing the object
- <code>**field(function)**</code> Imports the field function. <code>function</code> parameter is used to indicate the field function. Its format is <code>[A,B,C]</code> where A, B and C are functions that are valid in C/C++. Additionally, only x,y and z can be parameter of these functions. For example:
 <span style="background-color: #FF0"> **[4x*5y , 6z , sin(x*z+y) ]** </span>
- <code>render()</code> computes the final result of the surface integral

### 3.Example
<pre>
from SurfaceIntegralCumputer import Reality
ball=Reality("ball.ply")
ball.field("[x,y,z]")
print(ball.render())
</pre>
