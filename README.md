# Hazel
Hazel Eigen
# watching Thought
## 11 Window Abstraction and GLFW
编译时GLFW出现了问题，原因是Hazel被编译为动态库，而GLFW也被编译为动态库，要把GLFW修改为静态库。深层次的原因需要我继续探索。
## 12 Layers
对于这节课在prenake5.lua添加的buildoption "/MDd"不是很了解，也因为没有添加全而产生了debug assert failed错误。