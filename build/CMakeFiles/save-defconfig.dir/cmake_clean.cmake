file(REMOVE_RECURSE
  "bootloader/bootloader.bin"
  "bootloader/bootloader.elf"
  "bootloader/bootloader.map"
  "config/sdkconfig.cmake"
  "config/sdkconfig.h"
  "flash_project_args"
  "hyper.bin"
  "hyper.map"
  "project_elf_src_esp32.c"
  "CMakeFiles/save-defconfig"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/save-defconfig.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
