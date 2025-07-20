# Hazel

Hazel Eigen

# watching Thought
## 11 Window Abstraction and GLFW

编译时GLFW出现了问题，原因是Hazel被编译为动态库，而GLFW也被编译为动态库，要把GLFW修改为静态库。深层次的原因需要我继续探索。

## 12 Layers

对于这节课在prenake5.lua添加的buildoption "/MDd"不是很了解，也因为没有添加全而产生了debug assert failed错误。

这篇[文章](https://www.programmersought.com/article/14857274108/)解释了为什么。buildoption "/MD" 和 "/MT"是针对 [Runtime library](https://cppscripts.com/cpp-runtime-library)的,这是一个包含程序运行的库。

## 15 ImGui

这节弄的很乱，我改了许多代码可能以后会出现BUG，出现的错误有以下:

- GLFW和Glad出现了重复的opengl header，用`GLFW_INCLUDE_NONE`宏可禁用GLFW的opengl header

- ImGui 需要用宏`IMGUI_IMPL_OPENGL_LOADER_CUSTOM`告诉他使用自定义的loader(glad)

- 没有使用`gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)`正确初始化glad（在'glfwMakeContextCurrentz'之后）。

## 16 ImGui Events

ImGui的输入过时了，被替换为新的API，这篇[文章](https://github.com/ocornut/imgui/issues/4921)介绍了API变化。

他带着我们实现了事件，但这已经在imgui_impl_glfw.h文件实现并声明了，并且我还而外声明了从GLFW键码到ImGui的转换的方法声明。

## 17 Github and Hazel

- 改变buildoption为可以直接设置项目的/MDD和/MD，这更加方便且不会出现警告。参考这篇[文章](https://github.com/TheCherno/Hazel/issues/15)

- 设置startproject 和 define HZ_DEBUG

## 18 pull request

对postcommand进行了修改，了解了一些不曾知道的事，但premake的API发生了改变，有些不同，这篇(文章)[https://github.com/TheCherno/Hazel/issues/9]有相应的讨论。

## 19 input poll

它的代码有点错误，并且不会及时返回错误，但也不错。这个错误是对GLFW的state返回的值不是很清楚，他是在凭感觉。