
#include <iostream>
#include <string>


int main(int argc, char* argv[])
{
    std::string path = "/home/wxxz/workspace/weights/nxray.onnx";


    std::string name;
    for(int idx = path.size() - 1; idx >= 0; --idx)
    {
        if(path[idx] == '/' || path[idx] == '\\'){
            name = path.substr(idx + 1, path.size());
            break;
        }
    }
    
    std::cout << "name: " << name.c_str() << "\n";

    return 0;
}