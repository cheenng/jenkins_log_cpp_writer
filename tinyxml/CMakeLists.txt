
SET(TargetName tinyxml_STL)

#Headerdateien die zur Lib gehoeren definieren (falls dies nicht geschieht sind diese auch nicht im Visual Studio Solution zu sehen)

#Alle cpp Dateien dieses Verzeichnisses fuers target holen
#Anmerkung: Dies stellt nicht den empfohlenen Weg dar Src-Files zu holen, da jede Menge ungewollte Dateien mit eingebunden werden koennen
file(GLOB XmlCpps "*.cpp")
file(GLOB_RECURSE XmlHeaders "*.h")

add_library(${TargetName} ${XmlCpps} ${XmlHeaders})

# Add preprocessor definition for STL usage
target_compile_definitions(${TargetName} PUBLIC -DTIXML_USE_STL)
