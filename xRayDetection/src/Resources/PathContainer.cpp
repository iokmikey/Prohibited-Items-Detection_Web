#include "Resources/PathContainer.h"
#include "Common/Filesystem.h"

namespace Resources
{
    
    
   void PathContainer::InsertPath(const std::string& fullPath) 
   {
        std::string filename = Common::IFilesystem::GetFilename(fullPath);
        Insert(filename, fullPath);
   }
   
   
   void PathContainer::InsertPaths(const std::vector<std::string>& paths)
   {
      for(const auto& path : paths) {
         InsertPath(path);
      }
   }

   
}