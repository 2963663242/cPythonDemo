#include <string>
#include <locale>
#include <codecvt>
#include "utils.h"
#include <CoreFoundation/CFBundle.h>

std::string get_executable_dir()
{

  CFURLRef resourceURL = CFBundleCopyExecutableURL(CFBundleGetMainBundle());
    std::string bunddlePath;
    char resourcePath[PATH_MAX];
  if (CFURLGetFileSystemRepresentation(resourceURL, true,
                                       (UInt8 *)resourcePath,
                                       PATH_MAX))
  {
    if (resourceURL != NULL)
    {
      CFRelease(resourceURL);
    }
      bunddlePath = resourcePath;
      bunddlePath = bunddlePath.substr(0,bunddlePath.find_last_of("/"));
      
    return std::string(bunddlePath);
  }
    return "";
}


  // convert wstring to string 
   std::string wstring2string(const std::wstring& input)
  {
    //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(input);
  }

    // convert string to wstring
   std::wstring string2wstring(const std::string& input)
  {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
  }

