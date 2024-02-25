 
# List source files
file(GLOB SOURCES "*.cpp")

# Exports the cpp files to the parent Cmake list
set(SOURCES ${SOURCES} PARENT_SCOPE)
