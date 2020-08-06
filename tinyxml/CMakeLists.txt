
SET(TargetName tinyxml_STL)

file(GLOB XmlCpps "*.cpp")
file(GLOB_RECURSE XmlHeaders "*.h")

add_library(${TargetName} ${XmlCpps} ${XmlHeaders})

# Add preprocessor definition for STL usage
target_compile_definitions(${TargetName} PUBLIC -DTIXML_USE_STL)
