# Hazel

Hazel Eigen

# watching Thought
## 11 Window Abstraction and GLFW

编译时GLFW出现了问题，原因是Hazel被编译为动态库，而GLFW也被编译为动态库，要把GLFW修改为静态库。深层次的原因需要我继续探索。
## 12 Layers

对于这节课在prenake5.lua添加的buildoption "/MDd"不是很了解，也因为没有添加全而产生了debug assert failed错误。

## 15 ImGui

这节弄的很乱，我改了许多代码可能以后会出现BUG，出现的错误有以下:

- GLFW和Glad出现了重复的opengl header，用'GLFW_INCLUDE_NONE'宏可禁用GLFW的opengl header

- ImGui 需要用宏'IMGUI_IMPL_OPENGL_LOADER_CUSTOM'告诉他使用自定义的loader(glad)

- 没有使用'gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)'正确初始化glad（在'glfwMakeContextCurrentz'之后）。