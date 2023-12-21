#include "Statistics.h"
#include <iostream>

int main(int argc, char* argv[])
{
    Statistics st;
    st.Initialize();
    auto result = st.Count("2023-09-01", "2023-09-30");
    
    for(const auto& it : result) {
        std::cout << "key:" << it.first << " value:" << it.second << std::endl;
    }
    
    //st.Append("2023-09-19 11:03:51", "Wrench", 0.87, "P8765.jpg");
    return 0;
}