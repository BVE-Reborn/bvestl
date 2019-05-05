include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO BVE-Reborn/eastl-polyalloc
    REF v0.3
    SHA512 c34dece4b45837ffae3625569b9547504efe54e87decfa399977799832fcd3ed589d72c19d07a05f61c392e50c3249be8a5b9d9fa018fcf8f74fbe867cb971fc
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
)

vcpkg_install_cmake()

vcpkg_fixup_cmake_targets()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug)

# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/eastl-polyalloc RENAME copyright)
